#include <iostream> // Manual 
#include <fstream> // Print
#include <vector> // Masuin data
#include <string> //cin get() cin 
#include <windows.h> // Sleep()
#include <sstream> 
#include <cctype>
#include <cstdlib>
#include <algorithm> // Unutk buat kartu
#include <ctime> 
#include <iomanip> 
#include <conio.h> 
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
    string jenistabungan;
    string ModelTabungan;
  

    Bank() : saldo(0) {
        nomorakun = "";
        no_pinword = "";
        namanasabah = "";
        no_telp = "";
        alamat = "";
        email = "";
        tanggal_lahir = "";
        banks = "";
        kelamin = "";
        jenistabungan = "";
        ModelTabungan = "";
    }

  
    Bank(string nomorakun, int saldo, string no_pinword, 
     string namanasabah, string no_telp, string alamat, 
     string email, string bank ,string tanggal_lahir, string kelamin,string jenistabungan , string ModelTabungan ) 
    : nomorakun(nomorakun), saldo(saldo), no_pinword(no_pinword),
      namanasabah(namanasabah), no_telp(no_telp), alamat(alamat),
      email(email), tanggal_lahir(tanggal_lahir), banks(bank), kelamin(kelamin), jenistabungan(jenistabungan), ModelTabungan(ModelTabungan) {}


   
    virtual string DataNasabah() = 0;
    virtual string InputDataNasabah() = 0;
   

    virtual ~Bank() {}

    string getnomorakun() { return nomorakun; }
    string getjenistabungan(){return jenistabungan; }
    int getsaldo() { return saldo; }
    string getno_pinword() { return no_pinword; }


    void setno_pinword(string pinBaru) {
        no_pinword = pinBaru;
    }
    void kurangiSaldo(int jumlah) {saldo -= jumlah;}
    void tambahSaldo(int jumlah) {saldo += jumlah;}



    
    void loading(){
        for (int i = 0; i < 3; i++){
            cout << ".";
            Sleep(800);
        }
    }

    void clear(){
        system("cls");
    }

    void inputTidakValid() {
    cout << "\033[31mINPUTAN TIDAK VALID!!!\033[0m" << endl;
    }

    void jeda(){
        Sleep(2400);
    }

    void proses(){
        clear();
        cout << setw(33) << "SILAHKAN TUNGGU" << endl;
        cout << setw(38) <<"TRANSAKSI SEDANG DIPROSES" << endl << endl << endl << endl;
        cout << setw(30) << "\n\nDEMI KEAMANAN PASTIKAN KARTU BANK ANDA SUDAH DI AMBIL" << endl;
        Sleep(3800);
        

    }

    string getTanggalDanJam() {
    time_t now = time(0);
    tm* waktu = localtime(&now);

    char buffer[100];
    strftime(buffer, sizeof(buffer), "%A, %d-%m-%Y %H:%M:%S", waktu);
    return string(buffer);
}


    string buatKartuATM(const string& nama, const string& akun, const string& bank) {

    const int lebar_kartu = 50;
    const int lebar_konten = lebar_kartu - 4; 
    
   
    auto potongTeks = [](const string& teks, int max_panjang) {
        return teks.substr(0, max_panjang);
    };
    
    
    const int max_nama = lebar_konten - 13; 
    const int max_akun = lebar_konten - 13;   
    const int max_bank = lebar_konten - 13;   
    

    string nama_terformat = potongTeks(nama, max_nama);
    string akun_terformat = potongTeks(akun, max_akun);
    string bank_terformat = potongTeks(bank, max_bank);
    
    auto buatGaris = [lebar_kartu]() {
        return "+" + string(lebar_kartu - 2, '-') + "+\n";
    };
    
    auto buatBaris = [lebar_konten](const string& kiri, const string& kanan = "") {
        int spasi = lebar_konten - kiri.length() - kanan.length();
        if (spasi < 0) spasi = 0;
        return "| " + kiri + string(spasi, ' ') + kanan + " |\n";
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



    string getHariTanggal() {
    string namaHari[] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
    string namaBulan[] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni",
                          "Juli", "Agustus", "September", "Oktober", "November", "Desember"};


    time_t now = time(0);
    tm* waktu = localtime(&now);

    int hari = waktu->tm_mday;
    int bulan = waktu->tm_mon;
    int tahun = 1900 + waktu->tm_year;
    int indeksHari = waktu->tm_wday; 
    
    string hasil = namaHari[indeksHari] + "_" + to_string(hari) + "_" + namaBulan[bulan] + "_" + to_string(tahun);
    return hasil;
}


 

void tampilATM() {
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

const string RED = "\033[91m";
const string BLUE = "\033[94m";
const string RESET = "\033[0m";



void printRupiah100() {
    cout << RED << "+--------------------------------+" << endl;
    cout << "|        BANK INDONESIA          |" << endl;
    cout << "|                                |" << endl;
    cout << "|          Rp 100.000            |" << endl;
    cout << "|                                |" << endl;
    cout << "|         SERATUS RIBU           |" << endl;
    cout << "+--------------------------------+" << endl << RESET;
    Sleep(100);
}

void printRupiah50() {
    cout << BLUE << "+--------------------------------+" << endl;
    cout << "|        BANK INDONESIA          |" << endl;
    cout << "|                                |" << endl;
    cout << "|          Rp 50.000             |" << endl;
    cout << "|                                |" << endl;
    cout << "|       LIMA PULUH RIBU          |" << endl;
    cout << "+--------------------------------+" << endl << RESET;
    Sleep(100);
}

void InfoBank(string TittleTabungan, string Tittle2Tabungan, string Tittle3Tabungan){
    clear();
    cout << TittleTabungan;
    cout <<"\nAnda hanya dapat melakukan penarikan dan transfer Rp500.000 dalam sehari\n\n";

    cout << Tittle2Tabungan;
    cout <<"\nPenarikan dan transfer hanya maximal dibawah Rp40.000.000, cocok untuk pekerja kantoran, usaha kecil dan orang berkeluarga\n\n";

    cout << Tittle3Tabungan;
    cout <<"\nPenarikan dan transfer bisa dilakukan sampai Rp500.000.000, cocok untuk pembisnis\n\n";

    system("pause");
    return;
}

void thankyou(){
    void thankyou();
    clear();
    cout << "TERIMAKASIH SUDAH MENGGUNAKAN LAYANAN BANK KAMI" << endl;
    cout << setw(38) <<"SEMOGA HARI ANDA MENYENANGKAN" << endl << endl << endl;
    cout << setw(39) <<"JANGAN LUPA MENGAMBIL KARTU ANDA";
    Sleep(5000);

}

string formatRupiahDisplay(long value) {
    stringstream ss;
    ss << "Rp";
    
  
    if (value >= 1000000) {
        ss << value / 1000000 << ".";
        ss << setfill('0') << setw(3) << (value / 1000) % 1000 << ".";
        ss << setfill('0') << setw(3) << value % 1000;
    }
 
    else if (value >= 1000) {
        ss << value / 1000 << ".";
        ss << setfill('0') << setw(3) << value % 1000;
    }

    else {
        ss << value;
    }
    
    return ss.str();
}

};

vector<Bank*> nasabah;
 int pilihlah;

class Nasabah : public Bank {
public:

    Nasabah() : Bank() {}

    Nasabah(string nomorakun, int saldo, string no_pinword,string namanasabah, string no_telp, string alamat,string email, string banks, string tanggal_lahir,string kelamin, string jenistabungan, string ModelTabungan)  
    : Bank(nomorakun, saldo, no_pinword, namanasabah, no_telp, alamat, email, banks, tanggal_lahir, kelamin, jenistabungan, ModelTabungan) {}

    ~Nasabah() {}

     string DataNasabah() override{
        stringstream sm;
          sm << "Nomor Akun    : " << nomorakun << "\n"
             << "Nama Nasabah  : " << namanasabah << "\n"
             << "Saldo         : " << formatRupiahDisplay(saldo) << "\n"
             << "Bank          : " << banks << "\n"
             << "Jenis Tabungan: " << jenistabungan << "\n"
             << "No. Telepon   : " << no_telp << "\n"
             << "Alamat        : " << alamat << "\n"
             << "Email         : " << email << "\n"
             << "Tanggal Lahir : " << tanggal_lahir << "\n"
             << "Jenis Kelamin : " << kelamin << endl;
             return sm.str();
    }

   string InputDataNasabah() override {
    clear();
    cout << "========= REGISTRASI USER BARU =========\n";
    cin.ignore();

    cout << "Nama Nasabah  : ";
    getline(cin, namanasabah);

    while (true) {
        cout << "Bank          : ";
        getline(cin, banks);

        if (banks == "BNI" || banks == "bni") banks = "BNI";
        else if (banks == "BRI" || banks == "bri") banks = "BRI";
        else if (banks == "BCA" || banks == "bca") banks = "BCA";
        else if (banks == "Mandiri" || banks == "mandiri") banks = "MDRI";
        else {
            cout << "Bank tidak valid! Harus BNI/BRI/BCA/Mandiri.\n";
            jeda();
            continue;
        }
        break;
    }

    cout << "No. Telepon   : ";
    cin >> no_telp;
    cin.ignore();

    cout << "Alamat        : ";
    getline(cin, alamat);

    cout << "Email         : ";
    getline(cin, email);

    cout << "Tanggal Lahir : ";
    getline(cin, tanggal_lahir);


    string kelamin;
    while (true) {
        cout << "Jenis Kelamin : ";
        cin >> kelamin;

        if (kelamin == "laki-laki" || kelamin == "Laki-laki" || kelamin == "pria" || kelamin == "Pria") {
            kelamin = "Pria";
            break;
        } else if (kelamin == "perempuan" || kelamin == "Perempuan" || kelamin == "wanita" || kelamin == "Wanita") {
            kelamin = "Perempuan";
            break;
        } else {
            cout << "Jenis kelamin tidak valid! Harus 'laki-laki' atau 'perempuan'.\n";
            jeda();
        }
    }

   

    do{
        clear();
        cout << "Pilih Jenis Tabung" << endl;
        if(banks == "BNI"){
            cout << "1. Taplus Anak\n";
            cout << "2. Taplus\n";
            cout << "3. Taplus Bisnis\n";
            cout << "4. Informasi jenis tabungan\n";
            cout << "Pilih: ";
            cin >> pilihlah;
            
            if (pilihlah == 1){
                jenistabungan = "Taplus Anak";
                break;
            } else if(pilihlah == 2){
                jenistabungan = "Taplus";
                break;
            } else if(pilihlah == 3){
                jenistabungan = "Taplus Bisnis";
                break;
            } else if(pilihlah == 4){
                InfoBank("TAPLUS ANAK", "TAPLUS", "TAPLUS BISNIS");
            } else{
                inputTidakValid();
                jeda();
                clear();
            }
            
        } else if(banks == "BRI"){
            cout << "1. Britama Anak\n";
            cout << "2. Britama\n";
            cout << "3. Britama Bisnis\n";
            cout << "4. Informasi jenis tabungan\n";
            cout << "Pilih: ";
            cin >> pilihlah;
            
            if (pilihlah == 1){
                jenistabungan = "Britama Anak";
                break;
            } else if(pilihlah == 2){
                jenistabungan = "Britama";
                break;
            } else if(pilihlah == 3){
                jenistabungan = "Britama Bisnis";
                break;
            } else if(pilihlah == 4){
                InfoBank("BRITAMA ANAK", "BRITAMA", "BRITAMA BISNIS");
            } else{
                inputTidakValid();
                jeda();
                clear();
            }
        } else if(banks == "BCA"){
            cout << "1. Simpenan Pelajar\n";
            cout << "2. Gold\n";
            cout << "3. Premium\n";
            cout << "4. Informasi jenis tabungan\n";
            cout << "Pilih: ";
            cin >> pilihlah;
            
            if (pilihlah == 1){
                jenistabungan = "Simpenan Pelajar";
                break;
            } else if(pilihlah == 2){
                jenistabungan = "Gold";
                break;
            } else if(pilihlah == 3){
                jenistabungan = "Premium";
                break;
            } else if(pilihlah == 4){
                InfoBank("SIMPENAN PELAJAR", "GOLD", "PREMIUM");
            } else{
                inputTidakValid();
                jeda();
                clear();
            }
        } else if(banks == "MDRI"){
            cout << "1. Taplus Pendidikan\n";
            cout << "2. Taplus Rupiah\n";
            cout << "3. SiMakmur\n";
            cout << "4. Informasi jenis tabungan\n";
            cout << "Pilih: ";
            cin >> pilihlah;
            
            if (pilihlah == 1){
                jenistabungan = "Taplus Pendidikan";
                break;
            } else if(pilihlah == 2){
                jenistabungan = "Taplus Rupiah";
                break;
            } else if(pilihlah == 3){
                jenistabungan = "SiMakmur";
                break;
            } else if(pilihlah == 4){
                InfoBank("SIMPANAN PELAJAR", "TABUNGAN RUPIAH", "SIMAKMUR");
            } else{
                inputTidakValid();
                jeda();
                clear();
            }
        } else {
            cout << "Bank tidak valid!\n";
            jeda();
        }
    } while (pilihlah != 1 || pilihlah != 2 || pilihlah != 3);
    
        
        cout << "Sistem memproses nomor akun kartu ATM";
        loading();
        nomorakun = banks;
        for (int i = 0; i < 6; i++) {
            nomorakun += to_string(rand() % 10);
        }
        
        while (true) {
            clear();
            cout << "\nMASUKKAN PIN ATM (8 DIGIT): ";
            cin >> no_pinword;

        if (no_pinword.length() != 8) {
            cout << "PIN harus 8 digit!\n";
            jeda();
        } else {
            break;
        }
    }

 
    nasabah.push_back(new Nasabah(nomorakun, saldo, no_pinword, namanasabah, no_telp, alamat, email, banks, tanggal_lahir, kelamin, jenistabungan, ModelTabungan));

    clear();
    cout << "AKUN DAN KARTU BERHASIL DIBUAT!\n";
    cout << buatKartuATM(namanasabah, nomorakun, banks) << endl;
    system("pause");
    return nomorakun;

}
    
};

string admin_user = "";
string admin_no_pin = "" ;

class Admin : public Nasabah {
public:

    Admin() : Nasabah() {}

   ~Admin() {
    for (auto* n : nasabah) {
        cout << "[INFO] Menghapus nasabah: " << n->getnomorakun() << endl;
        delete n;
    }
    nasabah.clear();
}


    void AdminloginMenu() {
        int pilihan;
        clear();
        do {
            clear();
            cout << "========== ADMIN ==========\n";
            cout << "(1) > Login Admin\n";
            cout << "(2) > Registrasi Admin\n";
            cout << "(3) > Back\n";
            cout << "\nPilih: ";
            cin >> pilihan;

            switch (pilihan) {
                case 1: adminLogin(); break;
                case 2: AdminRegister(); break;
                case 3: return;
                default: inputTidakValid();
                jeda();
                AdminloginMenu();
            }
        } while (pilihan != 4);
    }

    void AdminRegister() {
        if (admin_user != "" && admin_no_pin != "") {
            clear();
            cout << "\nAdmin sudah terdaftar!\n";
            jeda();
            AdminloginMenu();
            return;
        }
        
        clear();
        cout << "====== REGISTRASI ADMIN =======\n";
        cout << "Masukkan Username : ";
        cin >> admin_user;
        cout << "Masukkan Password : ";
        cin >> admin_no_pin;
        clear();
        cout << "REGISTRASI ADMIN BERHASIL!!!\n";
        jeda();
        adminLogin();
    }
    

    void adminLogin() {
    if (admin_user == "" || admin_no_pin == "") {
        clear();
        cout << "ADMIN BELUM TERDAFTAR!!\n";
        jeda();
        AdminRegister();
        return; 
    }

    string input_user, input_pin;
    clear();
    cout << "===== LOGIN =====\n";
    cout << "Username : "; cin >> input_user;
    cout << "Password : "; cin >> input_pin;

    if (input_user == admin_user && input_pin == admin_no_pin) {
        clear();
        cout << "LOGIN BERHASIL!!!"; loading();
        adminMenu();
    } else {
        clear();
        cout << "Username atau Password salah!\n";
        jeda();
        clear();
        cout << "LOGIN GAGAL!!!"; loading();
        AdminloginMenu(); 
    }
}

    void adminMenu() {
        int pilihan;
     do {
            clear();
            cout << "========== MENU ADMIN ==========\n";
            cout << "(1) > Lihat Semua User\n";
            cout << "(2) > Registrasi User Baru\n";
            cout << "(3) > Export Laporan User (TXT)\n";
            cout << "(4) > Hapus Akun User\n";
            cout << "(5) > Logout\n";
            cout << "\nPilih: ";
            cin >> pilihan;

            switch (pilihan) {
                case 1: showAllUsers(); break;
                case 2: InputDataNasabah(); break;
                case 3: exportUserReport(); break;
                case 4: deleteUser(); break;
                case 5: cout << "Logout admin";
                        loading();
                        return; 
                        break;
                default: inputTidakValid();
                jeda();
                adminMenu();
                return;
            }
        } while (pilihan != 4); 
    }

    void showAllUsers() {
    clear();
    cout << "===== DAFTAR NASABAH =====\n" << endl;
    if (nasabah.empty()) {
        cout << "Tidak ada nasabah terdaftar.\n";
        system("pause");
        return;
     }
    for (size_t i = 0; i < nasabah.size(); ++i) {
        cout << nasabah[i]->DataNasabah() << endl;
        cout << "------------------------------------\n";
     }
      system("pause");
   }


    void exportUserReport() {
        ofstream report("laporan_user_" + getHariTanggal() + ".txt");
        report << "========= LAPORAN DATA USER =========\n";
        for (Bank* n : nasabah) {
        report << n->DataNasabah();
        report << "-------------------------------------\n";
        }
        report.close();
        clear();
        cout << "Laporan user berhasil diekspor ke 'laporan_user.txt'\n";
        jeda();
    }

    void deleteUser() {
    string no_acc;
    clear();
    cout << "======== DELETE USER ========\n";  
    cout << "Masukkan No Rekening yang akan dihapus: ";
    cin >> no_acc;
    clear();
    cout <<"Sedang mencari data user"; loading();

    for (size_t i = 0; i < nasabah.size(); ++i) {
        if (nasabah[i]->getnomorakun() == no_acc) {
            cout << "\nUser ditemukan: " << nasabah[i]->namanasabah << endl;
            cout << "No akun bank  : " << nasabah[i]->getnomorakun() << endl;
            cout << "Apakah yakin ingin menghapus?" << endl;
            cout << "(1) > Ya" << endl;
            cout << "(2) > Tidak" << endl;
            int konfirmasi;
            cin >> konfirmasi;
            if (konfirmasi == 1) {
                delete nasabah[i];                          
                nasabah.erase(nasabah.begin() + i);         
                clear();
                cout << "Akun berhasil dihapus!!!\n";
                jeda();
                adminMenu();
            } else {
                cout << "Penghapusan dibatalkan.\n";
                return;
            }
        }
    }
    cout << "No rekening tidak ditemukan.\n";
    jeda();
    deleteUser();
}

    void logTransaction(const string& logData) {
        ofstream logFile("laporan.txt", ios::app);
        logFile << logData << endl;
        logFile.close();
    }
};



class ATM : public Bank {
public:


ATM():Bank(){}

string DataNasabah() override {}

string InputDataNasabah() override {}


ATM(string nomorakun, int saldo, string no_pinword,string namanasabah, string no_telp, string alamat,string email, string banks, string tanggal_lahir,string kelamin, string jenistabungan, string ModelTabungan)  
    : Bank(nomorakun, saldo, no_pinword, namanasabah, no_telp, alamat, email, banks, tanggal_lahir, kelamin, jenistabungan, ModelTabungan) {}

void TampilanMasukKartu() {
    string nomor_kartu;
    clear();

    if (nasabah.empty()) {
        cout << "DATA NASABAH PADA DATABASE MASIH KOSONG!!!";
        loading();
        return;
    }

    cout << "====== HALO SELAMAT DATANG DI BANK ======" << endl;
    cout << "Masukkan nomor kartu anda: ";
    cin >> nomor_kartu;

    for (size_t i = 0; i < nasabah.size(); i++) {
        if (nasabah[i]->getnomorakun() == nomor_kartu) {
            string sementara = nomor_kartu;
            Pin(sementara);
            return;
        }
    }

    clear();
    cout << "NOMOR KARTU TIDAK DITEMUKAN!!!";
    loading();
    TampilanMasukKartu();  
}

    
bool Pin(string user){
    string input_pin;
    int attempts = 0;

    Bank* currentUser = nullptr;
    for (auto* n : nasabah) {
        if (n->getnomorakun() == user) {
            currentUser = n;
            break;
        }
    }

    if (!currentUser) {
        cout << "AKUN TIDAK DITEMUKAN!" << endl;
        return false;
    }
    while(attempts < 3){
        clear();
        tampilATM();
        cout << "DEMI KEAMANAN DAN KENYAMANAN SILAKAN \nGANTI PIN ANDA SECARA BERKALA\n" << endl;
        cout << "MASUKKAN PIN ATM ANDA" << endl;
        cin >> input_pin;

         if (input_pin == currentUser->getno_pinword()) {
            clear();
            cout << "INPUTAN PIN BENAR!!!";
            jeda();
            MenuAtm(user, input_pin);
            return true;
        } else {
            clear();
            cout << "INPUTAN PIN ANDA SALAH\n";
            jeda();
            clear();
            cout << "PERCOBAAN TERSISA: " << 2 - attempts << "X" << endl;
            jeda();
            attempts++;
        }
    }
    cout << "ANDA TELAH MELEWATI BATAS PERCOBAAN PIN!!!\n";
    return false;
    
}

string PilihPecahanUang(string user, int jumlah){
int pilihan, uang_pecahan;
clear();
cout << "- PECAHAN UANG YANG DAPAT DIAMBIL" << endl;
cout << "(1) > 100.000" << endl;
cout << "(2) > 50.000\n" << endl;

cout << setw(28) << "JIKA ADA MASALAH PADA SAAT" << endl;
cout << setw(28) << "ANDA BERTRANSAKSI, HUBUNGI" << endl;
cout << setw(26) << "CABANG TERDEKAT ATAU " << endl;
cout << setw(23) << "BNI CALL 1500046" << endl;
cout << "\nPilih: ";
cin >> pilihan;

if(pilihan == 1){
   uang_pecahan = jumlah / 100000;
   
    if (jumlah % 100000 != 0) {
        clear();
        cout << "Jumlah penarikan harus kelipatan Rp50.000!" << endl;
        jeda();
        return PilihPecahanUang(user, jumlah); 
    }
   prosesPenarikan(user, jumlah, uang_pecahan, 100000);
} else if(pilihan == 2){
   uang_pecahan = jumlah / 50000;
    prosesPenarikan(user, jumlah, uang_pecahan, 50000);
} else {
    inputTidakValid();
    jeda();
    return PilihPecahanUang(user, jumlah); 
}
return user;
}

int InputSaldo(string user, int setoran){
    clear();
    proses();
    clear();
    for (size_t i = 0; i < nasabah.size() ; i++){
        if(user == nasabah[i]->getnomorakun()){
            nasabah[i]->tambahSaldo(setoran);
            cout << "SALDO ANDA BERHASIL DI TAMBAHKAN!!!" << endl;
            jeda();
            clear();
            cout << "SALDO ANDA MENJADI Rp " << formatRupiahDisplay(nasabah[i]->getsaldo())<< endl;
            system("pause");
            pilih(user);
        }
  }
}


int PilihPecahanUang(string user){
    int pilihan, uang_pecahan;
    clear();
    cout << "- PECAHAN UANG YANG DAPAT DIAMBIL" << endl;
    cout << "100.000" << endl;
    cout << "50.000\n" << endl;
    
    cout << setw(28) << "JIKA ADA MASALAH PADA SAAT" << endl;
    cout << setw(28) << "ANDA BERTRANSAKSI, HUBUNGI" << endl;
    cout << setw(26) << "CABANG TERDEKAT ATAU " << endl;
    cout << setw(23) << "BNI CALL 1500046" << endl;
    cout << "\n> LANJUTKAN";
    _getch();
    SetorUang(user);
}

int jumlah_setor = 0;

int SetorUang(string user){
int setoran = 0, uang , jumlah, pilih;
clear();
cout <<"MASUKKAN JUMLAH UANG TUNAI YANG INI DISETOR" 
<< endl;
cout << "(1) > Rp 100.000" << endl;
cout << "(2) > Rp 50.000" << endl;
cout << "Pilih: ";
cin >> pilih;
if(pilih == 1){
    uang = 100000;
} else if(pilih == 2){
    uang = 50000;
} else{
    inputTidakValid();
    jeda();
return SetorUang(user);
}
    
clear();
cout << "Jumlah uang yang anda masukkan: ";
cin >> jumlah;
clear();
setoran = jumlah * uang;
cout << "TOTAL YANG ANDA MASUKKAN" << endl << endl;
cout <<  setw(10)  << formatRupiahDisplay(setoran) << endl << endl;
system("pause");
InputSaldo(user, setoran);
}


string prosesPenarikan(string user,int jumlah, int uang_pecahan, int uang){
proses();
for (size_t i = 0; i < nasabah.size(); i++){
    if(user == nasabah[i]->getnomorakun()){
        if(nasabah[i]->getsaldo() < jumlah){
            clear();
            cout << "SALDO ANDA TIDAK CUKUP UNTUK MELAKUKAN PENARIKAN UANG!!!";
            jeda();
            MenuAtm(user, "");
              return user;
        }

        nasabah[i]->kurangiSaldo(jumlah);
        clear();
        for (int i = 0; i < uang_pecahan ; i++){
        if(uang == 50000){
            printRupiah50();
        } else {
            printRupiah100();
        } 
    }
        cout << "PENARIKAN ANDA SEBESAR Rp" << jumlah << " BERHASIL!!!" << endl;
        system("pause");
        pilih(user);
        thankyou();
        return user;
    }
  }
}


string formatRupiahInput(long value) {
    stringstream ss;
    ss << "Rp";
    ss << setfill('0') << setw(2) << (value / 1000000) % 100 << ".";
    ss << setfill('0') << setw(3) << (value / 1000) % 1000 << ".";
    ss << setfill('0') << setw(3) << value % 1000;
    return ss.str();
}


int inputNominal(string user) {
  int limitPenarikan;

for (size_t i = 0; i < nasabah.size(); i++) {
    if (nasabah[i]->jenistabungan == "Taplus Anak" || nasabah[i]->jenistabungan == "Britama Anak" || nasabah[i]->jenistabungan == "Simpenan Pelajar" || nasabah[i]->jenistabungan == "Taplus Pendidikan") {
            limitPenarikan = 500000;
        } else if (nasabah[i]->jenistabungan == "Taplus" || nasabah[i]->jenistabungan == "Britama" || nasabah[i]->jenistabungan == "Gold" || nasabah[i]->jenistabungan == "Taplus Rupiah") {
            limitPenarikan = 40000000;
        } else {
            limitPenarikan = 500000000;
        }
        break;
    }

    int jumlah = 0;

    while (true) {
    clear();
    cout << "MASUKKAN JUMLAH NOMINAL PENARIKAN" << endl;
    cout << setw(32) << "YANG DIINGINKAN DALAM KELIPATAN" << endl;
    cout << setw(29) << "Rp 50.000 ATAU Rp 100.000" << endl;
    cout << setw(15) << "(MAKSIMUM " << formatRupiahDisplay(limitPenarikan) << ") " << endl << endl;
    cout << setw(20) << formatRupiahInput(jumlah) << endl << endl;

    char input = _getch();

    if (input == 13 && jumlah > 0) {
        if (jumlah > limitPenarikan) {
            clear();
            cout << "PERINGATAN!\n";
            cout << "Anda melebihi batas maksimal penarikan berdasarkan tipe akun Anda.\n";
            cout << "Batas maksimal Anda: " << formatRupiahInput(limitPenarikan) << endl;
            cout << "Penarikan Anda: " << formatRupiahInput(jumlah) << endl;
            jeda();
            continue;
        }

        clear();
        cout << "NOMINAL: " << formatRupiahDisplay(jumlah) << endl;
        cout << "(1) > JIKA BENAR" << endl;
        cout << "(2) > JIKA SALAH" << endl;

        char pilihan = _getch();
        if (pilihan == '1') {
            PilihPecahanUang(user, jumlah);
            return jumlah;
        } else if (pilihan == '2') {
            jumlah = 0;
            continue;
        }
    } else if (input == 8 && jumlah > 0) { //kode 8 backspace
        jumlah /= 10;
    } else if (isdigit(input)) {
        int digit = input - '0';
        if (jumlah <= 99999999) {
            int newValue = jumlah * 10 + digit;
            if (newValue <= limitPenarikan) {
                jumlah = newValue;
            }
        }
    } else if (input == 27) { //kode esc
        cout << "Transaksi dibatalkan" << endl;
        return -1;
    }
}
}

void MenuAtm(string user, string pin){
    clear();
    int choose;
    cout << setw(31) <<"MENU PENARIKAN CEPAT"
    << endl;
    cout << setw(37) << "SILAHKAN PILIH JUMLAH PENARIKAN"
    << endl;
    cout << "(PILIH 'MENU LAIN' JIKA INGIN CETAK RECEIPT)\n"
    << endl;

    cout << "(1) > 250.000 " << setw(31) <<"500.000 < (5)\n" << endl;
    cout << "(2) > 1.000.000" << setw(30) << "SETORAN < (6)\n" << setw(39) << "TUNAI " << endl;
    cout << "(3) > INFORMASI\n      & MUTASI" << setw(31) <<"PENARIKAN < (7)\n" << setw(38) <<"JUMLAH LAIN " << endl << endl;
    cout << "(4) > EXIT"<< setw(34) << "MENU LAIN < (8)" << endl;
    cout << "\nPILIH: ";
    cin >> choose;

    switch (choose){
    case 1:
        PilihPecahanUang(user,250000);
    break;
    case 2:
        PilihPecahanUang(user,1000000);
    break;
    case 3:
        lihatMutasi(user, pin);
        return;
    break;
    case 4:
        return;
    break;
    case 5:
        PilihPecahanUang(user,500000);
    break;
    case 6:
        PilihPecahanUang(user);
    break;
    case 7:
        inputNominal(user);
    break;
    case 8:
        MenuLIain(user, pin);
    break;
    default:
        inputTidakValid();
        jeda();
        MenuAtm(user, pin);
    break;
    }
}

void GantiPin(string user, string pin){
    int pilih;
    string pw;
    clear();
    cout << "APAKAH ANDA INGIN MENGGANTI PASSWORD?" << endl;
    cout << "(1) > YA" << endl;
    cout << "(2) > TIDAK" << endl;
    cout << "PILIH: ";
    cin >> pilih;

    if (pilih == 1){
        while (true) {
            clear();
            cout << "MASUKKAN PASSWORD SEBELUMNYA (8 DIGIT)" << endl;
            cin >> pw;

            if (pw.length() != 8){
                clear();
                cout << "ANGKA HARUS 8 DIGIT!" << endl;
                jeda();
                inputTidakValid();
                continue; 
            }

           
            bool cocok = false;
            for (size_t i = 0; i < nasabah.size(); i++) {
                if (user == nasabah[i]->getnomorakun() && pw == nasabah[i]->getno_pinword()) {
                    cocok = true;

                   
                    string baru, validasi;
                    cout << "MASUKKAN PASSWORD BARU (8 DIGIT): ";
                    cin >> baru;

                    if (baru.length() != 8){
                        cout << "PASSWORD HARUS 8 DIGIT!";
                        jeda();
                        inputTidakValid();
                        return;
                    }

                    cout << "VALIDASI PASSWORD: ";
                    cin >> validasi;

                    if(validasi == baru){
                        clear();
                        nasabah[i]->setno_pinword(baru);
                        cout << "SEDANG PROSES PERGANTIAN PASSWORD"; loading();
                        clear();
                        cout << "PERGANTIAN PASSWORD BERHASIL!!!"<< endl;
                        cout << "PASSWORD ANDA SEKARANG: " << nasabah[i]->getno_pinword() << endl;
                        jeda();
                        MenuAtm(user, pin);
                    } else {
                        cout << "VALIDASI GAGAL!" << endl;
                        jeda();
                        return;
                    }
                }
            }

            if (!cocok) {
                clear();
                cout << "PASSWORD LAMA SALAH!" << endl;
                jeda();
            }
        }
    } else if(pilih == 2){
        return; 
    }
}


void Transfer(string user, string pin) {
    clear();
    string akun;
    int condition;
    cout << "MASUKKAN NO REKENING BANK YANG INGIN ANDA TRANSFER\n> ";
    cin >> akun;

    if(akun == user) {
        cout << "TIDAK BISA MENTRANSFER KE DIRI SENDIRI!";
        jeda();
        return;
    }

    Bank* penerima = nullptr;
    Bank* pengirim = nullptr;

    for(size_t i = 0 ; i < nasabah.size() ; i++) {
        if (nasabah[i]->getnomorakun() == akun) {
            penerima = nasabah[i];
        }
        if (nasabah[i]->getnomorakun() == user) {
            pengirim = nasabah[i];
        }
    }

    if (penerima == nullptr || pengirim == nullptr) {
        clear();
        cout << "REKENING TIDAK DITEMUKAN!" << endl;
        jeda();
        MenuLIain(user, pin);
        return;
    }

    clear();
    cout << "AKUN DITEMUKAN!!!\n";
    cout << "======================================\n";
    cout << "Nama             : " << penerima->namanasabah << endl;
    cout << "Nomor Rekening   : " << penerima->getnomorakun() << endl;
    cout << "Bank             : " << penerima->banks << endl;
    cout << "======================================\n";
    cout << "LANJUTKAN?\n(1) > YA\n(2) > TIDAK\nPILIH: ";
    cin >> condition;

    if (condition != 1) {
        cout << "TRANSFER DIBATALKAN.";
        jeda();
        return;
    }

    int jumlah = 0;
    char input;
    bool selesai = false;

int limitPenarikan;

for (size_t i = 0; i < nasabah.size(); i++) {
    if (nasabah[i]->jenistabungan == "Taplus Anak" || nasabah[i]->jenistabungan == "Britama Anak" || nasabah[i]->jenistabungan == "Simpenan Pelajar" || nasabah[i]->jenistabungan == "Taplus Pendidikan") {
            limitPenarikan = 500000;
        } else if (nasabah[i]->jenistabungan == "Taplus" || nasabah[i]->jenistabungan == "Britama" || nasabah[i]->jenistabungan == "Gold" || nasabah[i]->jenistabungan == "Taplus Rupiah") {
            limitPenarikan = 40000000;
        } else {
            limitPenarikan = 500000000;
        }
        break;
    }
    
    clear();
    cout << "MAXIMAL TRANSFER" << formatRupiahDisplay(limitPenarikan);
    cout << "MASUKKAN NOMINAL YANG INGIN DITRANSFER" << endl << endl;
    
    while (!selesai) {
        cout << formatRupiahInput(jumlah) << "\r"; 
        input = _getch();
        
        if (input == 13) { 
            selesai = true;
        } else if (input == 8) { 
            jumlah /= 10;
        } else if (isdigit(input)) {
            int digit = input - '0';
            if (jumlah <= 999999999) { 
                jumlah = jumlah * 10 + digit;
            }
        }
    }

    if (jumlah <= 0 || jumlah > pengirim->getsaldo()) {
        clear();
        cout << "SALDO TIDAK CUKUP ATAU NOMINAL TIDAK VALID!" << endl;
        jeda();
        return;
    }

   
    clear();
    cout << "ANDA AKAN TRANSFER SEBESAR: " << formatRupiahDisplay(jumlah) << endl;
    cout << "(1) > KONFIRMASI" << endl;
    cout << "(2) > BATALKAN" << endl;
    cout << "PILIH: ";
    cin >> condition;

    if (condition != 1) {
        cout << "TRANSFER DIBATALKAN.";
        jeda();
        return;
    }

    pengirim->kurangiSaldo(jumlah);
    penerima->tambahSaldo(jumlah);

    ofstream report("transaksi_transfer.txt", ios::app);
    report << "============== TRANSFER ============= \n";
    report << "Dari   : " << pengirim->namanasabah << endl;
    report << "Ke     : " << penerima->namanasabah << endl;
    report << "Bank   : " << penerima->banks << endl;
    report << "Jumlah : " << formatRupiahDisplay(jumlah) << endl;
    report << "Waktu  : " << getTanggalDanJam() << endl;
    report << "--------------------------------------\n";
    report.close();

    clear();
    cout << "TRANSFER BERHASIL!!!" << endl;
    jeda();
    clear();

    cout << "SISA SALDO ANDA " << formatRupiahDisplay(pengirim->getsaldo()) << endl;
    system("pause");
    pilih(user);
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

void lihatMutasi(string user, string pin) {
    clear();
    ifstream file("transaksi_transfer.txt");
    if (!file.is_open()) {
        cout << "BELUM ADA TRANSAKSI TERSIMPAN.\n";
        system("pause");
        MenuAtm(user, "");
    }

    string line;
    cout << "===== RIWAYAT TRANSAKSI ANDA =====\n\n";

    while (getline(file, line)) {
        if (line.find("Dari") != string::npos && line.find(user) != string::npos) {
       
            cout << line << endl;
            for (int i = 0; i < 5; i++) {
                if (getline(file, line)) {
                    cout << line << endl;
                }
            }
            cout << endl;
        }
    }

    file.close();
    system("pause");
    MenuAtm(user, pin);
}


void tampilkanMenu(string user, string pin) {
    cout << fixed << setprecision(2);

    while (true) {
        int pilihan;
        string layanan, deskripsi;
        int nominal = 0;
        const int biayaAdmin = 2500;
        double total;

        clear();
        cout << "\n=== MENU PEMBAYARAN ===" << endl;
        cout << "1. PLN" << endl;
        cout << "2. PDAM" << endl;
        cout << "3. Pendidikan" << endl;
        cout << "Pilih layanan (1-3): ";

        if (!(cin >> pilihan) || pilihan < 1 || pilihan > 3) {
            inputTidakValid();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore();

        switch (pilihan) {
            case 1: layanan = "PLN"; break;
            case 2: layanan = "PDAM"; break;
            case 3: layanan = "Pendidikan"; break;
        }

        clear();
        cout << "Masukkan nominal pembayaran untuk " << layanan << " (Rp): ";
        if (!(cin >> nominal) || nominal <= 0) {
            cout << "Nominal tidak valid. Masukkan angka positif.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(); 

        cout << "Deskripsi: ";
        getline(cin, deskripsi);

        total = nominal + biayaAdmin;
        string nomor = generateNomor();

       
        bool ditemukan = false;

        for (size_t i = 0; i < nasabah.size(); i++) {
            if (user == nasabah[i]->getnomorakun()) {
                ditemukan = true;

                clear();
                cout << "Pembayaran         : " << layanan << endl;
                cout << "Deskripsi          : " << deskripsi << endl;
                cout << "Nama               : " << nasabah[i]->namanasabah << endl;
                cout << "Biaya              : " << formatRupiahDisplay(nominal) << endl;
                cout << "Biaya Admin        : " << formatRupiahDisplay(biayaAdmin) << endl;
                cout << "Total Pembayaran   : " << formatRupiahDisplay(total) << endl;
                cout << "Nomor Pembayaran   : " << nomor << endl;
                cout << "\n(1) > KONFIRMASI\n(2) > BATALKAN\n";
                cout << "\nPilihan Anda: ";

                int konfirmasi;
                cin >> konfirmasi;

                if (konfirmasi == 1) {
                    if (total > nasabah[i]->getsaldo()){
                        clear();
                        cout << "MAAF SALDO ANDA TIDAK CUKUP WKWK";
                        jeda();
                        MenuLIain(user, pin);
                    }
                    
                    ofstream outfile("pembayaran.txt", ios::app);
                    if (outfile.is_open()) {
                        outfile << "Pembayaran         : " << layanan << endl;
                        outfile << "Deskripsi          : " << deskripsi << endl;
                        outfile << "Nama               : " << nasabah[i]->namanasabah << endl;
                        outfile << "Biaya              : " << formatRupiahDisplay(nominal) << endl;
                        outfile << "Biaya Admin        : " << formatRupiahDisplay(biayaAdmin) << endl;
                        outfile << "Total Pembayaran   : " << formatRupiahDisplay(total) << endl;
                        outfile << "Nomor Pembayaran   : " << nomor << endl;
                        outfile << "-------------------------------" << endl;
                        outfile.close();
                        cout << "\nData berhasil disimpan ke pembayaran.txt!" << endl;
                    } else {
                        cout << "Gagal membuka file!" << endl;
                    }

                    nasabah[i]->kurangiSaldo(total);
                    proses();
                    thankyou();
                } else {
                    cout << "\nTransaksi dibatalkan oleh pengguna."; loading();
                }

                pilih(user);  
                return;
            }
        }

        if (!ditemukan) {
            cout << "Akun tidak ditemukan!" << endl;
            return;
        }
    }
}


void infoSaldo(string user, string pin){
 
    clear();
    cout << "==== SALDO ANDA ====" << endl;

    for (size_t i = 0; i < nasabah.size(); i++) {
        if (nasabah[i]->getnomorakun() == user) {
            cout << formatRupiahDisplay(nasabah[i]->getsaldo()) << endl;
            system("pause");
            MenuLIain(user, pin);
        }
    }

    cout << "Akun tidak ditemukan." << endl;
    system("pause");

}

void MenuLIain(string user, string pin){
    int chose;
    clear();
    cout << "MENU LAIN ANDA DAPAT MENGAKSES FITUR TAMBAHAN ATM DISINI" << endl << endl;
    cout << "(1) > GANTI PIN" << setw(42) << "INFORMASI SALDO < (3)" << endl << endl;
    cout << "(2) > TRANSFER" << setw(43) << "PEMBAYARAN < (4)" << endl << endl;
    cout << "(5) > BACK\n";
    cout << "\nPILIH: ";
    cin >> chose;
    
    switch(chose){
    case 1:
        GantiPin(user, pin);
    break;
    case 2:
        Transfer(user, pin);
    break;
    case 3:
        infoSaldo(user, pin);
    break;
    case 4:
        tampilkanMenu(user, pin);
    break;
    case 5:
        MenuAtm(user, pin);
    break;  
    default:
    break;
    }
}

void pilih(string user){
    int pkl;
    clear();
    cout << "APAKAH ANDA INGIN MELAKUKAN TRANSAKASI LAGI?" << endl;
    cout << "> YA" << endl;
    cout << "> TIDAK" << endl;
    cout << "PILIH: ";
    cin >> pkl;

    if (pkl == 1){
        Pin(user);
    } else {
        thankyou();
        return;
    }
}
};

int main() {
    Admin* admin = new Admin();
    ATM* atm = new ATM();

    int pilih;
    do {
        admin->clear();
        cout << "========== "; 
        cout << "SELAMAT DATANG DI BANK"; 
        cout << " =========\n";
        cout << "Anda mau akses yang mana?" << endl;
        cout << "(1) > ADMIN" << endl;
        cout << "(2) > NASABAH" << endl;
        cout << "(3) > KELUAR" << endl;
        cout << "\nPilih: ";
        cin >> pilih;

        switch (pilih) {
             case 1:
                 admin->AdminloginMenu(); 
                break;
            case 2:
                atm->TampilanMasukKartu();
                break;
            case 3:
                admin->clear();
                cout << "Terima kasih!" << endl;
                exit(0);
            default:
                cout << "PILIHAN TIDAK VALID!!!" << endl;
        }
    } while (true);
}

