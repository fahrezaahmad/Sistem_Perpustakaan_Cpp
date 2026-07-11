#include <iostream>
#include <string>
using namespace std;

const int MAX_BUKU = 100;

string daftarBuku[MAX_BUKU] = {
    "Algoritma",
    "Struktur Data",
    "Basis Data",
    "Belajar Hacking",
    "Pemrograman",
    "C++",
    "Java",
    "Html",
    "Linux"
};
int jumlahBuku = 9;

struct Peminjaman {
    string namaPeminjam;
    string judulBuku;
    string tanggalPinjam;
    bool dipinjam;
};

Peminjaman daftarPinjam[100];
int jumlahPinjam = 0;

//Presentasi 22/06/2026
const int JUMLAH_RAK = 5;
const int KAPASITAS_RAK = 10;
string rakBuku[JUMLAH_RAK][KAPASITAS_RAK];
int jumlahPerRak[JUMLAH_RAK] = {0};

void tampilkanRak() {
    cout << "\n### DAFTAR RAK BUKU ###\n";
    for (int i = 0; i < JUMLAH_RAK; i++) {
        cout << "Rak " << i + 1 << " (" << jumlahPerRak[i] << "/" << KAPASITAS_RAK << ") : ";
        if (jumlahPerRak[i] == 0) {
            cout << "[Kosong]";
        } else {
            for (int j = 0; j < jumlahPerRak[i]; j++) {
                cout << rakBuku[i][j];
                if (j < jumlahPerRak[i] - 1) cout << ", ";
            }
        }
        cout << endl;
    }
}

void tempatkanBukuKeRak(string judul, int nomorRak) {
    int idx = nomorRak - 1;
    if (idx < 0 || idx >= JUMLAH_RAK) {
        cout << "Nomor rak tidak valid. Pilih antara 1 sampai " << JUMLAH_RAK << ".\n";
        return;
    }

    for (int i = 0; i < jumlahPerRak[idx]; i++) {
        if (rakBuku[idx][i] == judul) {
            cout << "Buku \"" << judul << "\" sudah ada di rak " << nomorRak << ".\n";
            return;
        }
    }

    for (int r = 0; r < JUMLAH_RAK; r++) {
        for (int k = 0; k < jumlahPerRak[r]; k++) {
            if (rakBuku[r][k] == judul) {
                cout << "Buku \"" << judul << "\" sudah ditempatkan di rak " << r + 1 << ".\n";
                return;
            }
        }
    }

    if (jumlahPerRak[idx] >= KAPASITAS_RAK) {
        cout << "Rak " << nomorRak << " sudah penuh.\n";
        return;
    }

    rakBuku[idx][jumlahPerRak[idx]] = judul;
    jumlahPerRak[idx]++;
    cout << "Buku \"" << judul << "\" berhasil ditempatkan di rak " << nomorRak << ".\n";
}

//fiturterbaru
void hapusBukuDariRak(string judul) {
    for (int i = 0; i < JUMLAH_RAK; i++) {
        for (int j = 0; j < jumlahPerRak[i]; j++) {
            if (rakBuku[i][j] == judul) {
                for (int k = j; k < jumlahPerRak[i] - 1; k++) {
                    rakBuku[i][k] = rakBuku[i][k + 1];
                }
                rakBuku[i][jumlahPerRak[i] - 1] = "";
                jumlahPerRak[i]--;
                cout << "Buku \"" << judul << "\" berhasil dikeluarkan dari rak " << i + 1 << ".\n";
                return;
            }
        }
    }
    cout << "Buku \"" << judul << "\" tidak ada di rak manapun.\n";
}


bool cariBuku(string arr[], int n, string judul){
    if (n == 0) return false;
    if (arr[n-1] == judul) return true;
    return cariBuku(arr, n-1, judul);
}
//akhir
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

void tambahBuku(string judul) {
    if (jumlahBuku >= MAX_BUKU) {
        cout << "Koleksi buku sudah penuh.\n";
        return;
    }
    if (cariBuku(daftarBuku, jumlahBuku, judul)) {
        cout << "Buku \"" << judul << "\" sudah ada dalam koleksi.\n";
        return;
    }
    daftarBuku[jumlahBuku] = judul;
    jumlahBuku++;
    cout << "Buku \"" << judul << "\" berhasil ditambahkan.\n";
}

void hapusBuku(string judul) {
    for (int i = 0; i < jumlahPinjam; i++) {
        if (daftarPinjam[i].judulBuku == judul && daftarPinjam[i].dipinjam) {
            cout << "Buku \"" << judul << "\" sedang dipinjam, tidak bisa dihapus.\n";
            return;
        }
    }

    int posisi = -1;
    for (int i = 0; i < jumlahBuku; i++) {
        if (daftarBuku[i] == judul) {
            posisi = i;
            break;
        }
    }

    if (posisi == -1) {
        cout << "Buku \"" << judul << "\" tidak ditemukan.\n";
        return;
    }

    for (int i = posisi; i < jumlahBuku - 1; i++) {
        daftarBuku[i] = daftarBuku[i + 1];
    }
    jumlahBuku--;
    cout << "Buku \"" << judul << "\" berhasil dihapus.\n";
}

void urutkanBuku() {
    for (int i = 0; i < jumlahBuku - 1; i++) {
        for (int j = 0; j < jumlahBuku - 1 - i; j++) {
            if (daftarBuku[j] > daftarBuku[j + 1]) {
                string temp = daftarBuku[j];
                daftarBuku[j] = daftarBuku[j + 1];
                daftarBuku[j + 1] = temp;
            }
        }
    }
    cout << "Daftar buku berhasil diurutkan secara alfabetis.\n";
    tampilkanBuku();
}

int main() {
    int pilihan;
    string judulBuku, namaPeminjam, tanggalPinjam;
    bool ditemukan;
    int nomorRak;

    do {
        cout << "\n### Sistem Perpustakaan ###\n";
        cout << "1. Pinjam Buku\n";
        cout << "2. Kembalikan Buku\n";
        cout << "3. Lihat Daftar Buku\n";
        cout << "4. Lihat Riwayat Peminjam (Rekursif)\n";
        cout << "5. Cari Buku (Rekursif)\n";
        cout << "6. Tambah Buku\n";
        cout << "7. Hapus Buku\n";
        cout << "8. Urutkan Buku (Bubble Sort)\n";
        cout << "9. Manajemen Rak Buku\n";
        cout << "10. Keluar Program\n";
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
                cout << "Masukkan judul buku yang ingin ditambahkan: ";
                getline(cin, judulBuku);
                tambahBuku(judulBuku);
                break;
            case 7:
                cout << "Masukkan judul buku yang ingin dihapus: ";
                getline(cin, judulBuku);
                hapusBuku(judulBuku);
                break;
            case 8:
                urutkanBuku();
                break;
            case 9: {
                int subPilihan;
                cout << "\n### MANAJEMEN RAK BUKU ###\n";
                cout << "1. Lihat Semua Rak\n";
                cout << "2. Tempatkan Buku ke Rak\n";
                cout << "3. Keluarkan Buku dari Rak\n";
                cout << "Pilihan: ";
                cin >> subPilihan;
                cin.ignore();

                switch(subPilihan) {
                    case 1:
                        tampilkanRak();
                        break;
                    case 2:
                        cout << "Masukkan judul buku: ";
                        getline(cin, judulBuku);
                        if (!cariBuku(daftarBuku, jumlahBuku, judulBuku)) {
                            cout << "Buku tidak ada dalam koleksi.\n";
                            break;
                        }
                        cout << "Masukkan nomor rak (1-" << JUMLAH_RAK << "): ";
                        cin >> nomorRak;
                        cin.ignore();
                        tempatkanBukuKeRak(judulBuku, nomorRak);
                        break;
                    case 3:
                        cout << "Masukkan judul buku: ";
                        getline(cin, judulBuku);
                        hapusBukuDariRak(judulBuku);
                        break;
                    
                    default:
                        cout << "Pilihan tidak valid.\n";
                }
                break;
            }
            case 10:
                cout << "Keluar...\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }

    } while(pilihan != 10);

    return 0;
}