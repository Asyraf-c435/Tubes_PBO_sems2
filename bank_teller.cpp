#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

class User {
protected:
    string nama;
    string nomor_akun;
    double saldo;
    string nomor_PIN;
    
public:
    User(string nama, string nomor_akun, double saldo, string nomor_PIN)
        : nama(nama), nomor_akun(nomor_akun), saldo(saldo), nomor_PIN(nomor_PIN) {}

    string getnomor_akun() { return nomor_akun; }
    string getnama() { return nama; }
    double getsaldo() { return saldo; }
    string getnomor_PIN() { return nomor_PIN; }

    void deposit(double amount) {
        saldo += amount;
        cout << "Setor berhasil. Saldo saat ini: " << saldo << endl;
    }

    void withdraw(double amount) {
        saldo -= amount;
        cout << "Penarikan berhasil. Saldo tersisa: " << saldo << endl;
    }

    void showInfo() {
        cout << "Nama: " << nama << "\nNo Rekening: " << nomor_akun
             << "\nSaldo: " << saldo << endl;
    }

    string toFileString() {
        return nama + " " + nomor_akun + " " + to_string(saldo) + " " + nomor_PIN;
    }
};

class BankSystem {
private:
    vector<User> users;
    const string ADMIN_USER = "admin";
    const string ADMIN_no_pin = "admin123";
    const double MIN_SALDO = 50000;

public:
    BankSystem() { loadUsers(); }
    ~BankSystem() { saveUsers(); }

    void loadUsers() {
        ifstream file("data.txt");
        string nama, no_acc, no_pin;
        double jml_saldo;
        while (file >> nama >> no_acc >> jml_saldo >> no_pin) {
            users.emplace_back(nama, no_acc, jml_saldo, no_pin);
        }
        file.close();
    }

    void saveUsers() {
        ofstream file("data.txt");
        for (User& u : users) {
            file << u.toFileString() << endl;
        }
        file.close();
    }

    void loginMenu() {
        int pilihan;
        do {
            cout << "\n===== SELAMAT DATANG DI BANK =====\n";
            cout << "1. Login Admin\n";
            cout << "2. Login User\n";
            cout << "3. Registrasi User Baru\n";
            cout << "4. Keluar\n";
            cout << "Pilih: ";
            cin >> pilihan;

            switch (pilihan) {
                case 1: adminLogin(); break;
                case 2: userLogin(); break;
                case 3: registerUser(); break;
                case 4: cout << "Terima kasih.\n"; break;
                default: cout << "Pilihan tidak valid.\n";
            }
        } while (pilihan != 4);
    }

    void adminLogin() {
        string user, no_pin;
        cout << "Usernama Admin: "; cin >> user;
        cout << "PIN Admin: "; cin >> no_pin;

        if (user == ADMIN_USER && no_pin == ADMIN_no_pin) {
            adminMenu();
        } else {
            cout << "Login admin gagal!\n";
        }
    }

    void adminMenu() {
        int pilihan;
        do {
            cout << "\n--- MENU ADMIN ---\n";
            cout << "1. Lihat Semua User\n";
            cout << "2. Export Laporan User (TXT)\n";
            cout << "3. Hapus Akun User\n";
            cout << "4. Logout\n";
            cout << "Pilih: ";
            cin >> pilihan;

            switch (pilihan) {
                case 1: showAllUsers(); break;
                case 2: exportUserReport(); break;
                case 3: deleteUser(); break;
                case 4: cout << "Logout admin...\n"; break;
                default: cout << "Pilihan tidak valid.\n";
            }
        } while (pilihan != 4);
    }

    void showAllUsers() {
        cout << "\n--- DAFTAR USER ---\n";
        for (User& u : users) {
            u.showInfo();
            cout << "--------------------\n";
        }
    }

    void exportUserReport() {
        ofstream report("laporan_user.txt");
        report << "===== LAPORAN DATA USER =====\n";
        for (User& u : users) {
            report << "Nama         : " << u.getnama() << endl;
            report << "No Rekening  : " << u.getnomor_akun() << endl;
            report << "Saldo        : " << u.getsaldo() << endl;
            report << "------------------------------\n";
        }
        report.close();
        cout << "Laporan user berhasil diekspor ke 'laporan_user.txt'\n";
    }

    void deleteUser() {
        string no_acc;
        cout << "Masukkan No Rekening yang akan dihapus: ";
        cin >> no_acc;

        for (size_t i = 0; i < users.size(); ++i) {
            if (users[i].getnomor_akun() == no_acc) {
                cout << "User ditemukan: " << users[i].getnama() << endl;
                cout << "Apakah yakin ingin menghapus? (y/n): ";
                char konfirmasi;
                cin >> konfirmasi;
                if (konfirmasi == 'y' || konfirmasi == 'Y') {
                    users.erase(users.begin() + i);
                    cout << "Akun berhasil dihapus.\n";
                } else {
                    cout << "Penghapusan dibatalkan.\n";
                }
                return;
            }
        }
        cout << "No rekening tidak ditemukan.\n";
    }

    void userLogin() {
        string no_acc, no_pin;
        cout << "No Rekening: "; cin >> no_acc;
        cout << "PIN: "; cin >> no_pin;

        for (User& u : users) {
            if (u.getnomor_akun() == no_acc && u.getnomor_PIN() == no_pin) {
                userMenu(u);
                return;
            }
        }
        cout << "Login user gagal.\n";
    }

    void userMenu(User& user) {
        int pilihan;
        do {
            cout << "\n--- MENU USER ---\n";
            cout << "1. Cek Saldo\n";
            cout << "2. Setor\n";
            cout << "3. Tarik\n";
            cout << "4. Pembayaran\n";
            cout << "5. Logout\n";
            cout << "Pilih: ";
            cin >> pilihan;
            double amount;

            switch (pilihan) {
                case 1:
                    cout << "Saldo Anda: " << user.getsaldo() << endl;
                    break;
                case 2:
                    cout << "Jumlah setor: ";
                    cin >> amount;
                    user.deposit(amount);
                    logTransaction("[SETOR] " + user.getnomor_akun() + " - " + user.getnama() + " setor " + to_string(amount));
                    break;
                case 3:
                    cout << "Jumlah tarik: ";
                    cin >> amount;
                    if (user.getsaldo() - amount < MIN_SALDO) {
                        cout << "Transaksi gagal. Saldo tidak boleh kurang dari " << MIN_SALDO << endl;
                        logTransaction("[GAGAL TARIK] " + user.getnomor_akun() + " - " + user.getnama() + " gagal tarik " + to_string(amount));
                    } else {
                        user.withdraw(amount);
                        logTransaction("[TARIK] " + user.getnomor_akun() + " - " + user.getnama() + " tarik " + to_string(amount));
                    }
                    break;
                case 4:
                    paymentMenu(user);
                    break;
                case 5:
                    cout << "Logout...\n";
                    break;
                default:
                    cout << "Pilihan tidak valid.\n";
            }
        } while (pilihan != 5);
    }

    void paymentMenu(User& user) {
        const int biayaAdmin = 2500;
        bool lanjut = true;

        while (lanjut) {
            int pilihan;
            string layanan;
            double nominal;

            cout << "\n=== MENU PEMBAYARAN ===" << endl;
            cout << "1. PLN\n2. PDAM\n3. Pendidikan\nPilih layanan (1-3): ";
            while (!(cin >> pilihan) || pilihan < 1 || pilihan > 3) {
                cout << "Input tidak valid. Masukkan angka 1-3: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore();

            switch (pilihan) {
                case 1: layanan = "PLN"; break;
                case 2: layanan = "PDAM"; break;
                case 3: layanan = "Pendidikan"; break;
            }

            cout << "Masukkan nominal pembayaran untuk " << layanan << " (Rp): ";
            while (!(cin >> nominal) || nominal <= 0) {
                cout << "Nominal tidak valid. Masukkan angka positif: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            double total = nominal + biayaAdmin;

            if (user.getsaldo() < total) {
                cout << "Saldo tidak mencukupi untuk pembayaran ini.\n";
                logTransaction("[GAGAL BAYAR] " + user.getnomor_akun() + " - " + user.getnama() + " gagal bayar " + layanan);
            } else {
                user.withdraw(total);
                logTransaction("[BAYAR] " + user.getnomor_akun() + " - " + user.getnama() + " bayar " + layanan + " sebesar Rp" + to_string(total));
                cout << "Pembayaran berhasil.\n";
            }

            char ulang;
            cout << "Lakukan pembayaran lain? (y/n): ";
            cin >> ulang;
            cin.ignore();
            lanjut = (ulang == 'y' || ulang == 'Y');
        }
    }

    void registerUser() {
        string nama, no_acc, no_pin;
        double jml_saldo;

        cout << "=== REGISTRASI USER BARU ===\n";
        cout << "Nama: "; cin >> nama;
        cout << "No Rekening: "; cin >> no_acc;

        for (User& u : users) {
            if (u.getnomor_akun() == no_acc) {
                cout << "No rekening sudah terdaftar!\n";
                return;
            }
        }

        cout << "PIN: "; cin >> no_pin;
        cout << "Saldo Awal: "; cin >> jml_saldo;

        if (jml_saldo < MIN_SALDO) {
            cout << "Saldo awal harus minimal " << MIN_SALDO << endl;
            return;
        }

        users.emplace_back(nama, no_acc, jml_saldo, no_pin);
        cout << "Registrasi berhasil! Silakan login.\n";
    }

    void logTransaction(const string& logData) {
        ofstream logFile("laporan.txt", ios::app);
        logFile << logData << endl;
        logFile.close();
    }
};

int main() {
    BankSystem bank;
    bank.loginMenu();
    return 0;
}
