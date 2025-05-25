#include <iostream>
#include <string>

using namespace std;

void tampilkanMenu() {
    int pilihan;
    string layanan;
    double nominal;

    cout << "=== MENU PEMBAYARAN ===" << endl;
    cout << "1. PLN" << endl;
    cout << "2. PDAM" << endl;
    cout << "3. Pendidikan" << endl;
    cout << "Pilih layanan (1-3): ";
    cin >> pilihan;

    cin.ignore(); 

    switch (pilihan) {
        case 1:
            layanan = "PLN";
            break;
        case 2:
            layanan = "PDAM";
            break;
        case 3:
            layanan = "Pendidikan";
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
            return;
    }

    cout << "Masukkan nominal pembayaran untuk " << layanan << " (Rp): ";
    cin >> nominal;

    cout << "\n--- Data yang dimasukkan ---" << endl;
    cout << "Layanan : " << layanan << endl;
    cout << "Nominal : Rp " << nominal << endl;
}

int main() {
    tampilkanMenu();
    return 0;
}
