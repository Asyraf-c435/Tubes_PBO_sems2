#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class User {
protected:
    string nama;
    string nomorakun;
    double saldo;
    string no_pinword;
    
public:
    User(string nama, string nomorakun, double saldo, string no_pinword)
        : nama(nama), nomorakun(nomorakun), saldo(saldo), no_pinword(no_pinword) {}

    string getnomorakun() { return nomorakun; }
    string getnama() { return nama; }
    double getsaldo() { return saldo; }
    string getno_pinword() { return no_pinword; }

    void deposit(double amount) {
        saldo += amount;
        cout << "Setor berhasil. Saldo saat ini: " << saldo << endl;
    }

    void withdraw(double amount) {
        saldo -= amount;
        cout << "Penarikan berhasil. Saldo tersisa: " << saldo << endl;
    }

    void showInfo() {
        cout << "Nama: " << nama << "\nNo Rekening: " << nomorakun
             << "\nSaldo: " << saldo << endl;
    }

    string toFileString() {
        return nama + " " + nomorakun + " " + to_string(saldo) + " " + no_pinword;
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
            report << "No Rekening  : " << u.getnomorakun() << endl;
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
            if (users[i].getnomorakun() == no_acc) {
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
            if (u.getnomorakun() == no_acc && u.getno_pinword() == no_pin) {
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
            cout << "4. Logout\n";
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
                    logTransaction("[SETOR] " + user.getnomorakun() + " - " + user.getnama() + " setor " + to_string(amount));
                    break;
                case 3:
                    cout << "Jumlah tarik: ";
                    cin >> amount;
                    if (user.getsaldo() - amount < MIN_SALDO) {
                        cout << "Transaksi gagal. Saldo tidak boleh kurang dari " << MIN_SALDO << endl;
                        logTransaction("[GAGAL TARIK] " + user.getnomorakun() + " - " + user.getnama() + " gagal tarik " + to_string(amount));
                    } else {
                        user.withdraw(amount);
                        logTransaction("[TARIK] " + user.getnomorakun() + " - " + user.getnama() + " tarik " + to_string(amount));
                    }
                    break;
                case 4:
                    cout << "Logout...\n";
                    break;
                default:
                    cout << "Pilihan tidak valid.\n";
            }
        } while (pilihan != 4);
    }

    void registerUser() {
        string nama, no_acc, no_pin;
        double jml_saldo;

        cout << "=== REGISTRASI USER BARU ===\n";
        cout << "Nama: "; cin >> nama;
        cout << "No Rekening: "; cin >> no_acc;

        for (User& u : users) {
            if (u.getnomorakun() == no_acc) {
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
