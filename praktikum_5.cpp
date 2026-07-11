#include <iostream>
#include <string>
using namespace std;

string daftarBuku[5] = {
    "Algoritma",
    "Struktur Data",
    "Basis Data",
    "Belajar Hacking",
    "Pemrograman"
};
int jumlahBuku = 5;

struct Peminjaman {
    string namaPeminjam;
    string judulBuku;
    string tanggalPinjam;
    bool dipinjam;
};

Peminjaman daftarPinjam[100];
int jumlahPinjam = 0;


bool cariBuku(string arr[], int n, string judul){
    if (n == 0) return false;
    if (arr[n-1] == judul) return true;
    return cariBuku(arr, n-1, judul);
}

// Pertemuan 5
// Ahmad fahreza 2500018243
// Fitur Rekursif menampilakan riwayat orang dan buku yang dipinjam
void tampilkanRiwayatRekursif(int n) {
    if (n < 0) {
        if (jumlahPinjam == 0) cout << "Belum ada riwayat peminjaman.\n";
        return;
    }
    cout << "--------------------------" << endl;
    cout << "Nama Peminjam  : " << daftarPinjam[n].namaPeminjam << endl;
    cout << "Judul Buku     : " << daftarPinjam[n].judulBuku << endl;
    cout << "Tanggal Pinjam : " << daftarPinjam[n].tanggalPinjam << endl;
    cout << "Status         : " << (daftarPinjam[n].dipinjam ? "Masih Dipinjam" : "Sudah Kembali") << endl;
    tampilkanRiwayatRekursif(n - 1);
}

void tampilkanBuku() {
    cout << "\n### DAFTAR BUKU ###\n";
    for (int i = 0; i < jumlahBuku; i++) {
        cout << i+1 << ". " << daftarBuku[i] << endl;
    }
}

void kembalikanBuku(string judulBuku, string namaPeminjam) {
    int hariTerlambat;
    bool ditemukan = false;

    for (int i = 0; i < jumlahPinjam; i++) {
        if (daftarPinjam[i].judulBuku == judulBuku &&
            daftarPinjam[i].namaPeminjam == namaPeminjam &&
            daftarPinjam[i].dipinjam) {

            ditemukan = true;
            cout << "Masukkan jumlah hari keterlambatan: ";
            cin >> hariTerlambat;

            cout << "\n### DATA PENGEMBALIAN ###" << endl;
            cout << "Nama Peminjam : " << daftarPinjam[i].namaPeminjam << endl;
            cout << "Judul Buku    : " << daftarPinjam[i].judulBuku << endl;

            if (hariTerlambat > 0) {
                int denda = hariTerlambat * 1000;
                cout << "Terlambat     : " << hariTerlambat << " hari" << endl;
                cout << "Denda         : Rp" << denda << endl;
            } else {
                cout << "Tidak ada keterlambatan. Tidak ada denda.\n";
            }

            daftarPinjam[i].dipinjam = false;
            break;
        }
    }

    if (!ditemukan) {
        cout << "Data peminjaman tidak ditemukan atau buku sudah dikembalikan.\n";
    }
}

int main() {
    int pilihan;
    string judulBuku, namaPeminjam, tanggalPinjam;
    bool ditemukan;

    do {
        cout << "\n### Sistem Perpustakaan ###\n";
        cout << "1. Pinjam Buku\n";
        cout << "2. Kembalikan Buku\n";
        cout << "3. Lihat Daftar Buku\n";
        cout << "4. Lihat Riwayat Peminjam (Rekursif)\n";
        cout << "5. Cari Buku (Rekursif)\n";
        cout << "6. Keluar Program\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        switch(pilihan) {
            case 1: {
                ditemukan = false;
                cout << "Masukkan nama peminjam : ";
                getline(cin, namaPeminjam);
                cout << "Masukkan nama Buku : ";
                getline(cin, judulBuku);
                cout << "Masukkan tanggal pinjam : ";
                getline(cin, tanggalPinjam);

                // Menggunakan fungsi rekursif cariBuku untuk validasi
                if (cariBuku(daftarBuku, jumlahBuku, judulBuku)) {
                    ditemukan = true;
                    daftarPinjam[jumlahPinjam].namaPeminjam = namaPeminjam;
                    daftarPinjam[jumlahPinjam].judulBuku = judulBuku;
                    daftarPinjam[jumlahPinjam].tanggalPinjam = tanggalPinjam;
                    daftarPinjam[jumlahPinjam].dipinjam = true;
                    jumlahPinjam++;
                }

                cout << "\n### DATA PEMINJAMAN ###" << endl;
                if (ditemukan) {
                    cout << "Nama        : " << namaPeminjam << endl;
                    cout << "Buku        : " << judulBuku << endl;
                    cout << "Status      : Peminjaman berhasil dicatat" << endl;
                } else {
                    cout << "Buku \"" << judulBuku << "\" tidak tersedia." << endl;
                }
                break;
            }
            case 2:
                cout << "Masukkan nama peminjam: ";
                getline(cin, namaPeminjam);
                cout << "Masukkan judul buku: ";
                getline(cin, judulBuku);
                kembalikanBuku(judulBuku, namaPeminjam);
                break;
            case 3:
                tampilkanBuku();
                break;
            case 4:
                cout << "\n### RIWAYAT PEMINJAMAN (Terbaru -> Lama) ###\n";
                tampilkanRiwayatRekursif(jumlahPinjam - 1);
                break;
            case 5:
                cout << "Masukkan judul buku yang dicari: ";
                getline(cin, judulBuku);
                if (cariBuku(daftarBuku, jumlahBuku, judulBuku)) {
                    cout << "Buku tersedia.\n";
                } else {
                    cout << "Buku tidak ditemukan.\n";
                }
                break;
            case 6:
                cout << "Keluar...\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while(pilihan != 6);

    return 0;
}