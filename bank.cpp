#include "Bank.h"
#include <windows.h>
#include <sstream>
#include <ctime>
#include <iomanip>

Bank::Bank() : saldo(0) {}

Bank::Bank(string nomorakun, int saldo, string no_pinword, string namanasabah, string no_telp,
           string alamat, string email, string bank, string tanggal_lahir, string kelamin)
    : nomorakun(nomorakun), saldo(saldo), no_pinword(no_pinword), namanasabah(namanasabah),
      no_telp(no_telp), alamat(alamat), email(email), banks(bank), tanggal_lahir(tanggal_lahir),
      kelamin(kelamin) {}

Bank::~Bank() {}

string Bank::getnomorakun() { return nomorakun; }
string Bank::getbank() { return banks; }
int Bank::getsaldo() { return saldo; }
string Bank::getno_pinword() { return no_pinword; }

void Bank::kurangiSaldo(int jumlah) { saldo -= jumlah; }
void Bank::tambahSaldo(int jumlah) { saldo += jumlah; }

string Bank::toFileString() {
    return namanasabah + " " + nomorakun + " " + to_string(saldo) + " " + no_pinword;
}

void Bank::loading() {
    for (int i = 0; i < 3; i++) {
        cout << "."; Sleep(100);
    }
}

void Bank::clear() {
    system("cls");
}

void Bank::npc() {
    cout << "Tekan spasi untuk kembali...";
    cin.get();
}

void Bank::inputTidakValid() {
    cout << "\033[31mINPUTAN TIDAK VALID!!!\033[0m" << endl;
}

void Bank::jeda() {
    Sleep(2000);
}

void Bank::proses() {
    cout << setw(21) << "SILAHKAN TUNGGU" << endl;
    cout << "TRANSAKSI SEDANG DIPROSES\n\n\n\n" << endl;
    Sleep(3000);
}

void Bank::setWarna(int kodeWarna) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, kodeWarna);
}

void Bank::tampilATM() {
    cout << R"(
+========================================+
|           MASUKKAN PIN ANDA            |
+========================================+
| [ 1 ] [ 2 ] [ 3 ]   [ <- ]  Hapus      |
| [ 4 ] [ 5 ] [ 6 ]   [Enter]            |
| [ 7 ] [ 8 ] [ 9 ]   [  C  ]  Clear     |
|   [  0  ]   [ . ]   [ OK ]  Konfirmasi |
+========================================+
)";
}

void Bank::printRupiah100() {
    cout << "\033[91m+--------------------------------+\n"
         << "|        BANK INDONESIA          |\n"
         << "|                                |\n"
         << "|          Rp 100.000            |\n"
         << "|                                |\n"
         << "|         SERATUS RIBU           |\n"
         << "+--------------------------------+\033[0m\n";
}

void Bank::printRupiah50() {
    cout << "\033[94m+--------------------------------+\n"
         << "|        BANK INDONESIA          |\n"
         << "|                                |\n"
         << "|          Rp 50.000             |\n"
         << "|                                |\n"
         << "|       LIMA PULUH RIBU          |\n"
         << "+--------------------------------+\033[0m\n";
}

string Bank::buatKartuATM(const string& nama, const string& akun, const string& bank) {
    const int lebar_kartu = 50;
    const int lebar_konten = lebar_kartu - 4;

    auto potongTeks = [](const string& teks, int max_panjang) {
        return teks.substr(0, max_panjang);
    };

    const int max_field = lebar_konten - 13;
    string nama_terformat = potongTeks(nama, max_field);
    string akun_terformat = potongTeks(akun, max_field);
    string bank_terformat = potongTeks(bank, max_field);

    auto buatGaris = [lebar_kartu]() {
        return "+" + string(lebar_kartu - 2, '-') + "+\n";
    };

    auto buatBaris = [lebar_konten](const string& kiri, const string& kanan = "") {
        int spasi = lebar_konten - kiri.length() - kanan.length();
        return "| " + kiri + string(max(0, spasi), ' ') + kanan + " |\n";
    };

    stringstream ss;
    ss << buatGaris();
    ss << buatBaris("BANK " + bank_terformat);
    ss << buatBaris(string(lebar_konten, '-'));
    ss << buatBaris("Nama       : " + nama_terformat);
    ss << buatBaris("No. Akun   : " + akun_terformat);
    ss << buatBaris("Bank       : " + bank_terformat);
    ss << buatBaris("");
    ss << buatBaris("[CHIP]");
    ss << buatBaris("[##########################]");
    ss << buatBaris("");
    ss << buatBaris(string(lebar_konten, '='));
    ss << buatBaris("KARTU ATM - HANYA UNTUK PEMEGANG SAH");
    ss << buatGaris();
    return ss.str();
}

string Bank::getHariTanggal() {
    string namaHari[] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
    string namaBulan[] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni",
                          "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
    time_t now = time(0);
    tm* waktu = localtime(&now);

    return namaHari[waktu->tm_wday] + "_" + to_string(waktu->tm_mday) + "_" +
           namaBulan[waktu->tm_mon] + "_" + to_string(1900 + waktu->tm_year);
}
