
#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <string>
using namespace std;

class Bank {
protected:
    string nomorakun;
    int saldo;
    string no_pinword;

public:
    string namanasabah;
    string no_telp;
    string alamat;
    string email;
    string tanggal_lahir;
    string banks;
    string kelamin;

    Bank();
    Bank(string nomorakun, int saldo, string no_pinword,
         string namanasabah, string no_telp, string alamat,
         string email, string bank, string tanggal_lahir, string kelamin);

    virtual ~Bank();

    virtual string DataNasabah() = 0;
    virtual string InputDataNasabah() = 0;

    string getnomorakun();
    string getbank();
    int getsaldo();
    string getno_pinword();

    void kurangiSaldo(int jumlah);
    void tambahSaldo(int jumlah);

    string toFileString();
    string buatKartuATM(const string& nama, const string& akun, const string& bank);
    string getHariTanggal();

    void loading();
    void clear();
    void npc();
    void inputTidakValid();
    void jeda();
    void proses();
    void setWarna(int kodeWarna);
    void tampilATM();
    void printRupiah100();
    void printRupiah50();
};

#endif
