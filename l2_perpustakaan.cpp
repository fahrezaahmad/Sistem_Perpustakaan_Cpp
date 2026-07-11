/*
 * ============================================================
 * Sistem Manajemen Perpustakaan - Versi Refactor + Array 1D
 * Praktikum 4 - Ahmad Fahreza
 *
 * Penambahan dari versi sebelumnya:
 * + Array 1D: riwayatNama[MAX_PINJAM] → menyimpan urutan nama
 *   peminjam secara kronologis (siapa pinjam duluan)
 * + Menu 7: Riwayat Peminjaman → tampil semua record (aktif+selesai)
 * + Menu 8: Cari Riwayat by Nama → filter history per orang
 * ============================================================
 */

#include <iostream>
#include <string>
#include <vector>     // dynamic array untuk daftarBuku & daftarPinjam
#include <algorithm>  // any_of untuk pencarian buku
#include <iomanip>    // setw, left untuk formatting tabel
using namespace std;

// ============================================================
// KONSTANTA
// Definisikan di satu tempat agar mudah diubah
// ============================================================

const int MAX_PINJAM    = 100;  // kapasitas maksimal array 1D
const int DENDA_PER_HARI = 1000;

// ============================================================
// STRUCT: Peminjaman
// Satu record = satu transaksi peminjaman
// dipinjam = true  → masih dipinjam
// dipinjam = false → sudah dikembalikan (history tetap ada)
// ============================================================

struct Peminjaman {
    string namaPeminjam;
    string judulBuku;
    string tanggalPinjam;
    bool   dipinjam;
};

// ============================================================
// CLASS: Perpustakaan
// ============================================================

class Perpustakaan {
private:
    vector<string>    daftarBuku;    // daftar judul buku
    vector<Peminjaman> daftarPinjam; // semua record peminjaman (history)

    // ----------------------------------------------------------
    // ARRAY 1 DIMENSI: riwayatNama
    // Menyimpan nama peminjam secara urut kronologis
    // Tujuan: menunjukkan SIAPA saja yang pernah meminjam
    //         dalam urutan waktu, tanpa perlu struct lengkap
    //
    // Kenapa array biasa bukan vector?
    // → Syarat tugas: wajib ada array 1D
    // → Akses O(1) by index, cocok untuk tampil urutan antrian
    //
    // jumlahRiwayat = pointer index berikutnya yang kosong
    // ----------------------------------------------------------
    string riwayatNama[MAX_PINJAM];
    int    jumlahRiwayat = 0;

    // Helper: cetak garis pemisah sepanjang n karakter
    void cetakGaris(int n) const {
        cout << string(n, '-') << "\n";
    }

public:
    // --------------------------------------------------------
    // CONSTRUCTOR
    // Inisialisasi daftar buku awal saat objek dibuat
    // --------------------------------------------------------
    Perpustakaan() {
        daftarBuku = {
            "Algoritma",
            "Struktur Data",
            "Basis Data",
            "Belajar Hacking",
            "Pemrograman"
        };
    }

    // --------------------------------------------------------
    // cariBuku()
    // Cek apakah judul buku ada di perpustakaan
    //
    // any_of(begin, end, lambda):
    //   → return true jika ada minimal 1 elemen yang cocok
    //   → [&judul] = lambda capture variabel judul by reference
    // const = method tidak mengubah state object
    // --------------------------------------------------------
    bool cariBuku(const string& judul) const {
        return any_of(
            daftarBuku.begin(), daftarBuku.end(),
            [&judul](const string& b) { return b == judul; }
        );
    }

    // --------------------------------------------------------
    // pinjamBuku()
    // Catat peminjaman baru ke daftarPinjam (vector)
    // Sekaligus catat nama ke riwayatNama (array 1D)
    //
    // Return: true  = berhasil
    //         false = buku tidak ditemukan / array penuh
    // --------------------------------------------------------
    bool pinjamBuku(const string& nama, const string& judul, const string& tanggal) {
        // Validasi 1: buku harus ada di perpustakaan
        if (!cariBuku(judul)) return false;

        // Validasi 2: array 1D riwayatNama tidak boleh overflow
        if (jumlahRiwayat >= MAX_PINJAM) {
            cout << "Kapasitas riwayat penuh!\n";
            return false;
        }

        // Tambah ke vector daftarPinjam (detail record)
        daftarPinjam.push_back({nama, judul, tanggal, true});

        // Tambah ke array 1D riwayatNama (hanya nama, urut kronologis)
        // Index jumlahRiwayat = slot kosong berikutnya
        riwayatNama[jumlahRiwayat] = nama;
        jumlahRiwayat++;  // geser pointer ke slot berikutnya

        return true;
    }

    // --------------------------------------------------------
    // kembalikanBuku()
    // Cari record aktif, hitung denda, set dipinjam=false
    // --------------------------------------------------------
    void kembalikanBuku(const string& judul, const string& nama) {
        // auto& = reference agar bisa modifikasi field dipinjam
        for (auto& p : daftarPinjam) {
            if (p.judulBuku == judul &&
                p.namaPeminjam == nama &&
                p.dipinjam) {

                int hariTerlambat;
                cout << "Masukkan jumlah hari keterlambatan: ";
                cin >> hariTerlambat;
                cin.ignore();

                cout << "\n### DATA PENGEMBALIAN ###\n";
                cetakGaris(40);
                cout << left << setw(18) << "Nama Peminjam" << ": " << p.namaPeminjam << "\n";
                cout << left << setw(18) << "Judul Buku"    << ": " << p.judulBuku    << "\n";

                if (hariTerlambat > 0) {
                    cout << left << setw(18) << "Terlambat" << ": " << hariTerlambat << " hari\n";
                    cout << left << setw(18) << "Denda"     << ": Rp" << hariTerlambat * DENDA_PER_HARI << "\n";
                } else {
                    cout << "Tidak ada keterlambatan. Tidak ada denda.\n";
                }

                // Set false = sudah dikembalikan
                // Record TIDAK dihapus → tetap tersimpan sebagai history
                p.dipinjam = false;
                return;
            }
        }
        cout << "Data peminjaman tidak ditemukan.\n";
    }

    // --------------------------------------------------------
    // tampilkanBuku()
    // List semua buku yang tersedia
    // --------------------------------------------------------
    void tampilkanBuku() const {
        cout << "\n### DAFTAR BUKU ###\n";
        cetakGaris(30);
        for (int i = 0; i < (int)daftarBuku.size(); i++) {
            cout << setw(3) << i + 1 << ". " << daftarBuku[i] << "\n";
        }
        cetakGaris(30);
    }

    // --------------------------------------------------------
    // tampilkanPeminjamAktif()
    // Hanya tampilkan yang dipinjam=true (sedang dipinjam)
    // const = tidak ada mutasi sama sekali (fix bug versi lama)
    // --------------------------------------------------------
    void tampilkanPeminjamAktif() const {
        cout << "\n### DAFTAR PEMINJAM AKTIF ###\n";
        cetakGaris(57);
        cout << left << setw(20) << "Nama"
                     << setw(20) << "Buku"
                     << setw(15) << "Tanggal" << "\n";
        cetakGaris(57);

        bool ada = false;
        // const auto& = read-only reference, tidak bisa modifikasi
        for (const auto& p : daftarPinjam) {
            if (p.dipinjam) {
                cout << left << setw(20) << p.namaPeminjam
                             << setw(20) << p.judulBuku
                             << setw(15) << p.tanggalPinjam << "\n";
                ada = true;
            }
        }

        if (!ada) cout << "Tidak ada peminjaman aktif.\n";
        cetakGaris(57);
    }

    // --------------------------------------------------------
    // tampilkanRiwayat()
    // FITUR BARU — memanfaatkan array 1D riwayatNama[]
    //
    // Menampilkan DUA hal:
    // 1. Urutan kronologis nama dari array 1D (siapa pinjam duluan)
    // 2. Detail lengkap semua record dari vector (aktif + selesai)
    //
    // Kenapa dua sumber data?
    // → Array 1D = urutan antrian/kronologi (sederhana, O(1) akses)
    // → Vector   = detail record lengkap dengan status
    // --------------------------------------------------------
    void tampilkanRiwayat() const {
        cout << "\n### RIWAYAT PEMINJAMAN ###\n";

        // --- Bagian 1: Urutan dari Array 1D ---
        // Loop biasa dengan index karena array 1D tidak punya iterator
        cout << "\n[Urutan Kronologis Peminjam - Array 1D]\n";
        cetakGaris(35);
        if (jumlahRiwayat == 0) {
            cout << "Belum ada riwayat.\n";
        } else {
            for (int i = 0; i < jumlahRiwayat; i++) {
                // i+1 = nomor urut, riwayatNama[i] = nama ke-i
                cout << setw(3) << i + 1 << ". " << riwayatNama[i] << "\n";
            }
        }
        cetakGaris(35);

        // --- Bagian 2: Detail lengkap dari Vector ---
        cout << "\n[Detail Semua Transaksi]\n";
        cetakGaris(65);
        cout << left << setw(20) << "Nama"
                     << setw(20) << "Buku"
                     << setw(15) << "Tanggal"
                     << setw(10) << "Status" << "\n";
        cetakGaris(65);

        if (daftarPinjam.empty()) {
            cout << "Belum ada transaksi.\n";
        } else {
            for (const auto& p : daftarPinjam) {
                // Ternary operator: kondisi ? nilai_true : nilai_false
                string status = p.dipinjam ? "Dipinjam" : "Kembali";
                cout << left << setw(20) << p.namaPeminjam
                             << setw(20) << p.judulBuku
                             << setw(15) << p.tanggalPinjam
                             << setw(10) << status << "\n";
            }
        }
        cetakGaris(65);
        cout << "Total transaksi: " << daftarPinjam.size() << "\n";
    }

    // --------------------------------------------------------
    // cariRiwayatByNama()
    // FITUR BARU — cari semua history peminjaman satu orang
    //
    // Langkah:
    // 1. Cek dulu di array 1D apakah nama pernah tercatat
    // 2. Jika ada, tampilkan detail dari vector
    //
    // Kenapa cek array 1D dulu?
    // → Demonstrasi penggunaan array 1D sebagai "index" sederhana
    // → Jika tidak ada di array → pasti tidak ada di vector
    // --------------------------------------------------------
    void cariRiwayatByNama(const string& nama) const {
        // Step 1: Cek di array 1D apakah nama pernah meminjam
        bool pernahPinjam = false;
        for (int i = 0; i < jumlahRiwayat; i++) {
            if (riwayatNama[i] == nama) {
                pernahPinjam = true;
                break;  // cukup satu yang cocok, tidak perlu lanjut
            }
        }

        if (!pernahPinjam) {
            cout << "\"" << nama << "\" tidak pernah meminjam buku.\n";
            return;
        }

        // Step 2: Tampilkan detail dari vector
        cout << "\n### RIWAYAT PEMINJAMAN: " << nama << " ###\n";
        cetakGaris(55);
        cout << left << setw(20) << "Buku"
                     << setw(15) << "Tanggal"
                     << setw(10) << "Status" << "\n";
        cetakGaris(55);

        for (const auto& p : daftarPinjam) {
            if (p.namaPeminjam == nama) {
                string status = p.dipinjam ? "Dipinjam" : "Kembali";
                cout << left << setw(20) << p.judulBuku
                             << setw(15) << p.tanggalPinjam
                             << setw(10) << status << "\n";
            }
        }
        cetakGaris(55);
    }
};

// ============================================================
// MAIN
// Hanya handle UI loop + routing ke method
// Zero business logic di sini
// ============================================================
int main() {
    Perpustakaan perpus;

    int    pilihan;
    string judulBuku, namaPeminjam, tanggalPinjam;

    do {
        cout << "\n=============================\n";
        cout << "   SISTEM PERPUSTAKAAN\n";
        cout << "=============================\n";
        cout << "1. Pinjam Buku\n";
        cout << "2. Kembalikan Buku\n";
        cout << "3. Lihat Daftar Buku\n";
        cout << "4. Lihat Peminjam Aktif\n";
        cout << "5. Cari Buku\n";
        cout << "6. Riwayat Semua Peminjaman\n";   // ← BARU (pakai array 1D)
        cout << "7. Cari Riwayat by Nama\n";        // ← BARU (pakai array 1D)
        cout << "8. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: {
                cout << "Masukkan nama peminjam : ";
                getline(cin, namaPeminjam);
                cout << "Masukkan judul buku    : ";
                getline(cin, judulBuku);
                cout << "Masukkan tanggal pinjam: ";
                getline(cin, tanggalPinjam);

                cout << "\n### DATA PEMINJAMAN ###\n";
                if (perpus.pinjamBuku(namaPeminjam, judulBuku, tanggalPinjam)) {
                    cout << left << setw(12) << "Nama"    << ": " << namaPeminjam  << "\n";
                    cout << left << setw(12) << "Buku"    << ": " << judulBuku     << "\n";
                    cout << left << setw(12) << "Tanggal" << ": " << tanggalPinjam << "\n";
                    cout << "Status: Peminjaman berhasil dicatat.\n";
                } else {
                    cout << "Buku tidak tersedia di perpustakaan.\n";
                    cout << "Status: Gagal meminjam.\n";
                }
                break;
            }

            case 2: {
                cout << "Masukkan nama peminjam          : ";
                getline(cin, namaPeminjam);
                cout << "Masukkan judul buku dikembalikan: ";
                getline(cin, judulBuku);
                perpus.kembalikanBuku(judulBuku, namaPeminjam);
                break;
            }

            case 3:
                perpus.tampilkanBuku();
                break;

            case 4:
                perpus.tampilkanPeminjamAktif();
                break;

            case 5: {
                cout << "Masukkan judul buku yang dicari: ";
                getline(cin, judulBuku);
                if (perpus.cariBuku(judulBuku)) {
                    cout << "Buku \"" << judulBuku << "\" tersedia.\n";
                } else {
                    cout << "Buku \"" << judulBuku << "\" tidak ditemukan.\n";
                }
                break;
            }

            case 6:
                // Tampilkan array 1D (urutan kronologis) + detail vector
                perpus.tampilkanRiwayat();
                break;

            case 7: {
                cout << "Masukkan nama yang dicari: ";
                getline(cin, namaPeminjam);
                // Cek array 1D dulu, baru detail dari vector
                perpus.cariRiwayatByNama(namaPeminjam);
                break;
            }

            case 8:
                cout << "Keluar dari sistem. Sampai jumpa!\n";
                break;

            default:
                cout << "Pilihan tidak valid. Masukkan angka 1-8.\n";
        }

    } while (pilihan != 8);

    return 0;
}