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
        cout << "Data peminjaman tidak ditemukan.\n";
    }
}

void daftar_peminjam(){
    for(int q=0; q<jumlahPinjam; q++){
        cout << "### DAFTAR PEMINJAM ###" << endl;
        cout <<"Nama peminjam : " << daftarPinjam[q].namaPeminjam << endl;
        cout << "Judul Buku \t: " << daftarPinjam[q].judulBuku <<endl;
        cout << "Tanggal Pinjam \t: " << daftarPinjam[q].tanggalPinjam <<endl;
        cout <<endl;
        daftarPinjam[q].dipinjam= false;
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
        cout << "4. Lihat Daftar Peminjam\n";
        cout << "5. Keluar program\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        switch(pilihan) {
            case 1: {
                ditemukan = false;
                cout << "Masukan nama peminjam : ";
                getline(cin, namaPeminjam);
                cout << "Masukan nama Buku : ";
                getline(cin, judulBuku);
                cout << "Masukan tanggal pinjam : ";
                getline(cin, tanggalPinjam);

                for (int i = 0; i < jumlahBuku; i++) {
                    if (daftarBuku[i] == judulBuku) {
                        ditemukan = true;
                        daftarPinjam[jumlahPinjam].namaPeminjam = namaPeminjam;
                        daftarPinjam[jumlahPinjam].judulBuku = judulBuku;
                        daftarPinjam[jumlahPinjam].tanggalPinjam = tanggalPinjam;
                        daftarPinjam[jumlahPinjam].dipinjam = true;
                        jumlahPinjam++;
                        break;
                    }
                }

                cout << "\n### DATA PEMINJAMAN ###" << endl;
                if (ditemukan) {
                    cout << "Nama        : " << namaPeminjam << endl;
                    cout << "Buku        : " << judulBuku << endl;
                    cout << "Tanggal     : " << tanggalPinjam << endl;
                    cout << "\nStatus: Peminjaman berhasil dicatat" << endl;
                } else {
                    cout << "Buku tidak tersedia di perpustakaan" << endl;
                    cout << "Status: Gagal meminjam" << endl;
                }
                break;
            }
            case 2: {
                cout << "Masukkan nama peminjam: ";
                getline(cin, namaPeminjam);
                cout << "Masukkan judul buku yang dikembalikan: ";
                getline(cin, judulBuku);
                kembalikanBuku(judulBuku, namaPeminjam);
                break;
            }
            case 3:
                tampilkanBuku();
                break;
            case 4:
                daftar_peminjam();
                break;
            case 5:
                cout << "Keluar dari sistem...\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while(pilihan != 5);

    return 0;
}
