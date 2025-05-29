#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include <sstream> 
#include <cctype>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <iomanip>
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
  

    Bank() : saldo(2000000) {
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

    int setTingkatIsaldo(){}

    void kurangiSaldo(int jumlah) {saldo -= jumlah;}
    void tambahSaldo(int jumlah) {saldo += jumlah;}



    
    void loading(){
        for (int i = 0; i < 3; i++){
            cout << ".";
            Sleep(100);
        }
    }

    void clear(){
        system("cls");
    }

    void npc(){
        cout << "Tekan spasi untuk kembali...";
        cin.get();
    }

    void inputTidakValid() {
    cout << "\033[31mINPUTAN TIDAK VALID!!!\033[0m" << endl;
    }

    void jeda(){
        Sleep(2000);
    }

    void proses(){
        clear();
        cout << setw(33) << "SILAHKAN TUNGGU" << endl;
        cout << setw(38) <<"TRANSAKSI SEDANG DIPROSES" << endl << endl << endl << endl;
        cout << setw(30) << "\n\nDEMI KEAMANAN PASTIKAN KARTU BANK ANDA SUDAH DI AMBIL" << endl;
        Sleep(3800);

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


    void setWarna(int kodeWarna) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, kodeWarna);
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
    cout << "+--------------------------------+" << RESET;
}

void printRupiah50() {
    cout << BLUE << "+--------------------------------+" << endl;
    cout << "|        BANK INDONESIA          |" << endl;
    cout << "|                                |" << endl;
    cout << "|          Rp 50.000             |" << endl;
    cout << "|                                |" << endl;
    cout << "|       LIMA PULUH RIBU          |" << endl;
    cout << "+--------------------------------+" << RESET;
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
    clear();
    cout << "TERIMAKASIH SUDAH MENGGUNAKAN LAYANAN BANK KAMI" << endl;
    cout << setw(30) <<"SEMOGA HARI ANDA MENYENANGKAN";
}




// void setWarna(string kode) {
//     cout << "\x1b[38; 5; " << kode << "m";
// }


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
             << "Saldo         : Rp" << saldo << "\n"
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

void infoJumlahNasabah(const vector<Bank*>& nasabahList) {
    cout << "Jumlah nasabah saat ini: " << nasabahList.size() << endl;
}

    void AdminloginMenu() {
        int pilihan;
        clear();
        do {
            clear();
            cout << "===== ADMIN =====\n";
            cout << "> Login Admin\n";
            cout << "> Registrasi Admin\n";
            cout << "> Sistem ATM\n";
            cout << "Pilih: ";
            cin >> pilihan;

            switch (pilihan) {
                case 1: adminLogin(); break;
                case 2: AdminRegister(); break;
                case 3: return;
                default: cout << "Pilihan tidak valid.\n";
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
        jeda();;
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
            cout << "===== MENU ADMIN =====\n";
            cout << "> Lihat Semua User\n";
            cout << "> Registrasi User Baru\n";
            cout << "> Export Laporan User (TXT)\n";
            cout << "> Hapus Akun User\n";
            cout << "> Logout\n";
            cout << "Pilih: ";
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
                default: cout << "Pilihan tidak valid.\n";
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
        jeda();;
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
            cout << "> Ya (1)" << endl;
            cout << "> Tidak (2)" << endl;
            int konfirmasi;
            cin >> konfirmasi;
            if (konfirmasi == 1) {
                delete nasabah[i];                          
                nasabah.erase(nasabah.begin() + i);         
                clear();
                cout << "Akun berhasil dihapus!!!\n";
                jeda();;
                return;
            } else {
                cout << "Penghapusan dibatalkan.\n";
                return;
            }
        }
    }
    cout << "No rekening tidak ditemukan.\n";
    jeda();;
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
    jeda();
    TampilanMasukKartu();  
}

    
bool Pin(string user){
    string input_pin;
    int attempts = 0;

    while(attempts < 3){
        clear();
        tampilATM();
        cout << "DEMI KEAMANAN DAN KENYAMANAN SILAKAN \nGANTI PIN ANDA SECARA BERKALA\n" << endl;
        cout << "MASUKKAN PIN ATM ANDA" << endl;
        cin >> input_pin;

        for(size_t i = 0; i < nasabah.size(); i++){
        
             if(user == nasabah[i]->getnomorakun() && input_pin == nasabah[i]->getno_pinword()){
                clear();
                cout << "INPUTAN PIN BENAR!!!";
                jeda();
                MenuAtm(user);
                return true;
            }
            clear();
            cout << "INPUTAN PIN ANDA SALAH";
            jeda();
            clear();
            cout << "PERCOBAAN ANDA TERSISA " << 2 - attempts << "X" << " LAGI" << endl; 
            jeda();;
            attempts++;
            tampilATM();
        }
    }
    cout << "ANDA TELAH MELEWATI BATAS PERCOBAAN PIN!!!\n";
    return false;
    
}

int PilihPecahanUang(string user, int jumlah){
int pilihan, uang_pecahan;
clear();
cout << "- PECAHAN UANG YANG DAPAT DIAMBIL" << endl;
cout << "> 100.000" << endl;
cout << "> 50.000\n" << endl;

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
        MenuAtm(user);
    }
   prosesPenarikan(user, jumlah, uang_pecahan, 100000);
} else if(pilihan == 2){
   uang_pecahan = jumlah / 50000;
    prosesPenarikan(user, jumlah, uang_pecahan, 50000);
} else {
    inputTidakValid();
    jeda();
    MenuAtm(user);   
}

}

int prosesPenarikan(string user,int jumlah, int uang_pecahan, int uang){
proses();
for (size_t i = 0; i < nasabah.size(); i++){
    if(user == nasabah[i]->getnomorakun()){
        if(nasabah[i]->getsaldo() < jumlah){
            clear();
            cout << "SALDO ANDA TIDAK CUKUP UNTUK MELAKUKAN PENARIKAN UANG!!!";
            jeda();
            MenuAtm(user);
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
        return 0;
       
    }
}



}

void pilihJenisTabungan(){
    int pilihan;
    clear();
    cout << "PECAHAN JENIS SETORAN ANDA" << endl << endl;
    cout << "> REKENING GIRO" << endl;
    cout << "> REKENING TABUNGAN" << endl;
    cout << "> KE MENU UTAMA" << endl;
    cout << "PILIH: ";
    cin >> pilihan;

    if (pilihan == 1){
        cout << "GIRO" << endl;
    } else if (pilihan == 2){
        cout << "TABUNGAN" << endl;
    } else if (pilihan == 3){
        return;
    } else{
        inputTidakValid();
        jeda();
        pilihJenisTabungan();
    }
    
}

int PenarikanLain(string user){
int a;
clear();
 cout << "MAASUKKAN JUMLAH PENARIKAN TUNAI" << endl;
 cout << "YANG DIINGINKAN DALAM KELIPATAN " << endl;
 cout << "RP 50.000 ATAU RP 100.000" << endl;
 for (size_t i = 0; i < nasabah.size(); i++){
    if (user == nasabah[i]->getnomorakun()) {
        if (pilihlah == 1){
            a = 500000;
        } else if (pilihlah == 2){
            a = 40000000;
        } else {
            a = 500000000;
     }
}
 cout << "(MAKSIMUM RP " << a << ")" << endl;

 }
 system("pause");
}

void MenuAtm(string user){
    clear();
    int choose;
    cout << setw(31) <<"MENU PENARIKAN CEPAT"
    << endl;
    cout << setw(37) << "SILAHKAN PILIH JUMLAH PENARIKAN"
    << endl;
    cout << "(PILIH 'MENU LAIN' JIKA INGIN CETAK RECEIPT)\n"
    << endl;

    cout << "> 250.000 " << setw(35) <<"500.000 <\n" << endl;
    cout << "> 1.000.000" << setw(34) << "SETORAN <\n" << setw(43) << "TUNAI " << endl;
    cout << "> REGISTRASI\n  E-CHANNEL"<< setw(34) << "PENARIKAN <\n" << setw(43) <<"JUMLAH LAIN " << endl;
    cout << "> INFORMASI\n  & MUTASI" << setw(34) << "MENU LAIN <" << endl;
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
        cout << "REGISTRASI" << endl;
    break;
    case 4:
        cout << "INFORMASI & MUTASI" << endl;
    break;
    case 5:
        PilihPecahanUang(user,500000);
    break;
    case 6:
        cout << "SETORAN TUNAI" << endl;
    break;
    case 7:
        PenarikanLain(user);
    break;
    case 8:
        cout << "MENU LAIN" << endl;
    break;
    default:
        inputTidakValid();
        jeda();
        MenuAtm(user);
    break;
    }
}

void pilih(string user){
    int pkl;
    clear();
    cout << "APAKAH ANDA INGIN MELAKUKAN TRANSAKASI LAGI?" << endl;
    cout << "> Ya" << endl;
    cout << "> Tidak" << endl;
    cout << "Pilih: ";
    cin >> pkl;

    if (pkl == 1){
        Pin(user);
    } else {
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
        cout << "> ADMIN" << endl;
        cout << "> NASABAH" << endl;
        cout << "> KELUAR" << endl;
        cout << "Pilih: ";
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

