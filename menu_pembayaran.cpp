#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <limits>

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
    for (int i = 0; i < 12; i++) {
        nomor += to_string(rand() % 10);
    }
    nomor.insert(4, " ");
    nomor.insert(9, " ");
    return nomor;
}

bool pilihJenisSetoran() {
    int pilihan;
    cout << "=== PILIH JENIS SETORAN ANDA ===" << endl;
    cout << "1. Rekening Giro" << endl;
    cout << "2. Rekening Tabungan" << endl;
    cout << "3. Ke Menu Utama" << endl;
    cout << "Pilih (1-3): ";
    while (!(cin >> pilihan) || pilihan < 1 || pilihan > 3) {
        cout << "Input tidak valid. Masukkan angka 1-3: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch (pilihan) {
        case 1:
            cout << "\nAnda memilih Rekening Giro.\n";
            return true; // lanjutkan ke menu pembayaran
        case 2:
            cout << "\nAnda memilih Rekening Tabungan.\n";
            return true; // lanjutkan ke menu pembayaran
        case 3:
            cout << "\nKembali ke menu utama.\n";
            return false; // tidak lanjutkan
    }
    return false;
}

void tampilkanMenu() {
    cout << fixed << setprecision(2);

    bool lanjut = true;
    while (lanjut) {
        int pilihan;
        string layanan;
        double nominal;
        string nama;
        const int biayaAdmin = 2500;
        double total;

        cout << "\n=== MENU PEMBAYARAN ===" << endl;
        cout << "1. PLN" << endl;
        cout << "2. PDAM" << endl;
        cout << "3. Pendidikan" << endl;
        cout << "Pilih layanan (1-3): ";
        while (!(cin >> pilihan) || pilihan < 1 || pilihan > 3) {
            cout << "Input tidak valid. Masukkan angka 1-3: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(); // bersihkan newline

        switch (pilihan) {
            case 1: layanan = "PLN"; break;
            case 2: layanan = "PDAM"; break;
            case 3: layanan = "Pendidikan"; break;
        }

        cout << "Masukkan nama : ";
        getline(cin, nama);

        cout << "Masukkan nominal pembayaran untuk " << layanan << " (Rp): ";
        while (!(cin >> nominal) || nominal <= 0) {
            cout << "Nominal tidak valid. Masukkan angka positif: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        total = nominal + biayaAdmin;
        string nomor = generateNomor();

        ofstream outfile("pembayaran.txt", ios::app);
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

        char ulang;
        cout << "\nIngin melakukan pembayaran lagi? (y/n): ";
        cin >> ulang;
        cin.ignore();
        lanjut = (ulang == 'y' || ulang == 'Y');
    }

    cout << "\nTerima kasih telah menggunakan layanan kami.\n";
}

int main() {
    std::ofstream file("Pembayaran.txt", std::ios::trunc); 
    file.close();
    srand(time(0));
    if (login()) {
        if (pilihJenisSetoran()) {
            tampilkanMenu();
        } else {
            cout << "Menu utama belum tersedia." << endl;
        }
    }
    return 0;
}