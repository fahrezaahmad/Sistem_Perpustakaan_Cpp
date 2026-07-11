#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Konfigurasi sistem
const int MAX_HISTORY = 100;
const int DENDA_PER_HARI = 1000;

struct Transaction {
    string borrower;
    string bookTitle;
    string date;
    bool isActive;
};

class Library {
private:
    vector<string> books = {"Algoritma", "Struktur Data", "Basis Data", "Belajar Hacking", "Pemrograman"};
    vector<Transaction> history;
    
    // Array 1D untuk memenuhi syarat praktikum
    string logNames[MAX_HISTORY];
    int logCount = 0;

    void printDivider(int n = 40) const {
        cout << string(n, '-') << endl;
    }

public:
    void showBooks() const {
        cout << "\n--- Daftar Buku Tersedia ---\n";
        for (size_t i = 0; i < books.size(); i++) {
            cout << i + 1 << ". " << books[i] << endl;
        }
    }

    bool isBookAvailable(const string& title) const {
        return any_of(books.begin(), books.end(), [&](const string& b) { return b == title; });
    }

    bool borrowBook(string name, string title, string date) {
        if (!isBookAvailable(title) || logCount >= MAX_HISTORY) return false;

        history.push_back({name, title, date, true});
        logNames[logCount++] = name;
        return true;
    }

    void returnBook(const string& name, const string& title) {
        for (auto& record : history) {
            if (record.borrower == name && record.bookTitle == title && record.isActive) {
                int lateDays;
                cout << "Lama keterlambatan (hari): ";
                cin >> lateDays;
                cin.ignore();

                cout << "\n--- Slip Pengembalian ---\n";
                cout << "Peminjam: " << record.borrower << "\nBuku: " << record.bookTitle << "\n";
                
                if (lateDays > 0) {
                    cout << "Denda: Rp" << lateDays * DENDA_PER_HARI << "\n";
                } else {
                    cout << "Status: Tanpa denda.\n";
                }

                record.isActive = false;
                return;
            }
        }
        cout << "Error: Data peminjaman tidak ditemukan.\n";
    }

    void showHistory() const {
        cout << "\n[Urutan Kronologis (Array 1D)]\n";
        for (int i = 0; i < logCount; i++) cout << i + 1 << ". " << logNames[i] << "\n";

        cout << "\n[Detail Semua Transaksi]\n";
        printDivider(60);
        for (const auto& r : history) {
            cout << setw(15) << r.borrower << " | " << setw(15) << r.bookTitle 
                 << " | " << (r.isActive ? "Dipinjam" : "Kembali") << "\n";
        }
    }

    void searchHistoryByName(const string& name) const {
        bool found = false;
        for (const auto& r : history) {
            if (r.borrower == name) {
                if (!found) {
                    cout << "\nRiwayat untuk: " << name << "\n";
                    found = true;
                }
                cout << "- " << r.bookTitle << " [" << (r.isActive ? "Aktif" : "Selesai") << "]\n";
            }
        }
        if (!found) cout << "Tidak ada data riwayat untuk nama tersebut.\n";
    }
};

int main() {
    Library lib;
    int choice;
    string name, title, date;

    do {
        cout << "\n==============================\n";
        cout << " SISTEM PERPUSTAKAAN v2.0\n";
        cout << "==============================\n";
        cout << "1. Pinjam Buku\n";
        cout << "2. Kembalikan Buku\n";
        cout << "3. Lihat Daftar Buku\n";
        cout << "4. Lihat Riwayat Lengkap\n";
        cout << "5. Cari Riwayat by Nama\n";
        cout << "6. Keluar\n";
        cout << "Pilih: ";
        cin >> choice;
        cin.ignore(); // Membersihkan buffer agar getline berjalan benar

        switch (choice) {
            case 1:
                cout << "Nama Peminjam: "; getline(cin, name);
                cout << "Judul Buku   : "; getline(cin, title);
                cout << "Tanggal      : "; getline(cin, date);
                if (lib.borrowBook(name, title, date)) cout << ">> Berhasil dicatat.\n";
                else cout << ">> Gagal: Buku tidak ditemukan atau limit penuh.\n";
                break;
            case 2:
                cout << "Nama Peminjam: "; getline(cin, name);
                cout << "Judul Buku   : "; getline(cin, title);
                lib.returnBook(name, title);
                break;
            case 3:
                lib.showBooks();
                break;
            case 4:
                lib.showHistory();
                break;
            case 5:
                cout << "Masukkan Nama: "; getline(cin, name);
                lib.searchHistoryByName(name);
                break;
            case 6:
                cout << "Keluar dari sistem.\n";
                break;
            default:
                cout << "Pilihan tidak tersedia.\n";
        }
    } while (choice != 6);

    return 0;
}