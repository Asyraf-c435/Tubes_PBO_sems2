#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

bool login() {
    string username, password;
    cout << "=== LOGIN ===" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == "Bayar" && password == "12345") {
        cout << "Login berhasil!\n" << endl;
        return true;
    } else {
        cout << "Login gagal. Username atau password salah.\n" << endl;
        return false;
    }
}

string generateNomor() {
    string nomor = "";
    srand(time(0));
    for (int i = 0; i < 12; i++) {
        nomor += to_string(rand() % 10);
    }
    nomor.insert(4, " ");
    nomor.insert(9, " ");
    return nomor;
}

void tampilkanMenu() {
    int pilihan;
    string layanan;
    double nominal;
    string nama;
    const int biayaAdmin = 2500;
    double total;

    cout << "=== MENU PEMBAYARAN ===" << endl;
    cout << "1. PLN" << endl;
    cout << "2. PDAM" << endl;
    cout << "3. Pendidikan" << endl;
    cout << "Pilih layanan (1-3): ";
    cin >> pilihan;
    cin.ignore();

    switch (pilihan) {
        case 1: layanan = "PLN"; break;
        case 2: layanan = "PDAM"; break;
        case 3: layanan = "Pendidikan"; break;
        default:
            cout << "Pilihan tidak valid!" << endl;
            return;
    }

    cout << "Masukkan nama : ";
    getline(cin, nama);

    cout << "Masukkan nominal pembayaran untuk " << layanan << " (Rp): ";
    cin >> nominal;

    total = nominal + biayaAdmin;
    string nomor = generateNomor();

    ofstream outfile("pembayaran.txt", ios::app); // tambah data, bukan timpa
    if (outfile.is_open()) {
        outfile << "Pembayaran         : " << layanan << endl;
        outfile << "Nama               : " << nama << endl;
        outfile << "Biaya              : Rp " << nominal << endl;
        outfile << "Biaya Admin        : Rp " << biayaAdmin << endl;
        outfile << "Total Pembayaran   : Rp " << total << endl;
        outfile << "Nomor Pembayaran   : " << nomor << endl;
        outfile << "-------------------------------" << endl;
        outfile.close();
        cout << "\nData berhasil disimpan ke pembayaran.txt!" << endl;
    } else {
        cout << "Gagal membuka file!" << endl;
    }

    cout << "\n--- Data yang disimpan ---" << endl;
    cout << "Pembayaran         : " << layanan << endl;
    cout << "Nama               : " << nama << endl;
    cout << "Biaya              : Rp " << nominal << endl;
    cout << "Biaya Admin        : Rp " << biayaAdmin << endl;
    cout << "Total Pembayaran   : Rp " << total << endl;
    cout << "Nomor Pembayaran   : " << nomor << endl;
}

int main() {
    if (login()) {
        tampilkanMenu();
    }
    return 0;
}
