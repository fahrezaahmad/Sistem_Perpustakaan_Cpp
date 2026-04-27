#include <iostream>
//#include <string>
using namespace std;

int main() {
    string judulBuku, namaPeminjam, tanggalPinjam;

    string daftarBuku[5] = {
        "Algoritma",
        "Struktur Data",
        "Basis Data",
        "Belajar Hacking",
        "Pemrograman"
    };

    int jumlahBuku = 5;
    bool ditemukan = false;
    

    cout << "### Sistem Perpustakaan ###\n";
    cout << "Masukan nama peminjam : ";
    getline(cin, namaPeminjam);
    cout << "Masukan nama Buku : ";
    getline(cin, judulBuku);
    cout << "Masukan tanggal pinjam : ";
    cin  >> tanggalPinjam;

   
    for (int i = 0; i < jumlahBuku; i++) {
        if (daftarBuku[i] == judulBuku) {
            ditemukan = true;
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

    return 0;
}