#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
using namespace std;

class menuUtama{
	
private:

	struct dataAkun{
		string nama;
		string username;
		string password;
		string alamat;
		string noTelp;
	};

	bool ketemu;

	string userInput;
	string passInput;

	string garis;
	string karakter;

    string namaFile;

	dataAkun akun;
	dataAkun akunLama;
	dataAkun fileData;

public:

	void pilihPengguna();
	void menu();
	void menuCustomer();
	void menuAkun();
	void pengaturanAkun();

	bool validasiPinAdmin();

	void registrasi();
	void login();
	void tampilkanAkun();
	void updateDataFile();
};

void clearScreen(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void menuUtama::pilihPengguna(){

    int pilih;

    do{
        clearScreen();

        cout << "========================================\n";
        cout << "     SISTEM MANAJEMEN LAUNDRY FSN\n";
        cout << "========================================\n\n";

        cout << "=========== PILIH PENGGUNA =============\n";
        cout << "1. Admin\n";
        cout << "2. Customer\n";
        cout << "0. Keluar\n";
        cout << "----------------------------------------\n";

        cout << "Pilih : ";
        cin >> pilih;
        cin.ignore();

        switch(pilih){

            case 1:
                karakter = "Admin";
                namaFile = "admin.txt";
                menu();
                break;

            case 2:
                karakter = "Customer";
                namaFile = "customer.txt";
                menu();
                break;

            case 0:
                cout << "\nProgram selesai...\n";
                break;

            default:
                cout << "\nPilihan tidak valid!\n";
                system("pause");
        }

    } while(pilih != 0);
}

void menuUtama::menu(){

    int pilih;

	do{
		clearScreen();

		cout << "========================================\n";
        cout << "     SISTEM MANAJEMEN LAUNDRY FSN\n";
        cout << "========================================\n\n";

        cout << "------------- MENU " << karakter << " -------------\n";
        cout << "1. Login\n";
        cout << "2. Registrasi\n";
        cout << "0. Kembali\n";
        cout << "-----------------------------------------\n";

        cout << "Pilih : ";
        cin >> pilih;
   		cin.ignore();

        switch(pilih){

            case 1:
                login();
                break;

            case 2:
                registrasi();
                break;

            case 0:
                cout << "\nTerima kasih...\n";
                system("pause");
                break;

            default:
                cout << "\nPilihan tidak valid!\n";
                system("pause");
        }

    } while(pilih != 0);
}

bool menuUtama::validasiPinAdmin(){

    const string PIN_ADMIN = "123456";
    string pinInput;
    bool pinValid = true;

    cout << "PIN Admin 6 digit : ";
    getline(cin, pinInput);

    if(pinInput.length() != 6){
        pinValid = false;
    }

    for(int i = 0; i < pinInput.length(); i++){
        if(!isdigit(pinInput[i])){
            pinValid = false;
            break;
        }
    }

    if(!pinValid){
        cout << "\nPIN harus terdiri dari 6 digit angka!\n";
        system("pause");
        return false;
    }

    if(pinInput != PIN_ADMIN){
        cout << "\nPIN Admin salah! Registrasi dibatalkan.\n";
        system("pause");
        return false;
    }

    return true;
}

void menuUtama::registrasi(){

	clearScreen();

	cout << "==============================\n";
    cout << "          REGISTRASI\n";
    cout << "==============================\n";

    if(karakter == "Admin"){
        if(!validasiPinAdmin()){
            return;
        }

        cout << "\nPIN benar. Silakan lanjut registrasi admin.\n\n";
    }

    cout << "Nama          : ";
    getline(cin, akun.nama);

    cout << "Username      : ";
    getline(cin, akun.username);

    cout << "Password      : ";
    getline(cin, akun.password);

    cout << "Alamat        : ";
    getline(cin, akun.alamat);

    cout << "Nomor Telepon : ";
    getline(cin, akun.noTelp);

    ofstream file(namaFile.c_str(), ios::app);

    file << akun.nama << endl;
    file << akun.username << endl;
    file << akun.password << endl;
    file << akun.alamat << endl;
    file << akun.noTelp << endl;
    file << "------------------------" << endl;

    file.close();

    cout << "\nRegistrasi berhasil!\n";
	system("pause");
}

void menuUtama::login(){

    clearScreen();

    ketemu = false;

    cout << "==============================\n";
    cout << "            LOGIN\n";
    cout << "==============================\n";

    cout << "Username : ";
    getline(cin, userInput);

    cout << "Password : ";
    getline(cin, passInput);

    ifstream file(namaFile.c_str());

    if(!file){
        cout << "\nData belum ada!\n";
        system("pause");
        return;
    }

    while(getline(file, fileData.nama)){

        getline(file, fileData.username);
        getline(file, fileData.password);
        getline(file, fileData.alamat);
        getline(file, fileData.noTelp);
        getline(file, garis);

        if(userInput == fileData.username &&
           passInput == fileData.password){

            ketemu = true;

            akun = fileData;
            akunLama = fileData;

            break;
        }
    }

    file.close();

    if(ketemu){

        cout << "\nLogin berhasil sebagai " << karakter << ".\n";
        system("pause");

        menuCustomer();

    } else {

        cout << "\nUsername atau password salah!\n";
        system("pause");
    }
}

void menuUtama::menuCustomer(){

    int pilih;

    do{
        clearScreen();

        cout << "----------------------------------------\n";
        cout << "             MENU CUSTOMER\n";
        cout << "----------------------------------------\n";

        cout << "1. Akun\n";
        cout << "2. Lihat Poin\n";
        cout << "3. Lihat Layanan Laundry\n";
        cout << "4. Check Status Cucian\n";
        cout << "0. Logout\n";

        cout << "\nPilih : ";
        cin >> pilih;
        cin.ignore();

        switch(pilih){

            case 1:
                menuAkun();
                break;

            case 2:
                cout << "\nMenu Lihat Poin dipilih\n";
                system("pause");
                break;

            case 3:
                cout << "\nMenu Layanan Laundry dipilih\n";
                system("pause");
                break;

            case 4:
                cout << "\nMenu Status Cucian dipilih\n";
                system("pause");
                break;

            case 0:
                cout << "\nLogout berhasil\n";
                system("pause");
                break;

            default:
                cout << "\nPilihan tidak valid!\n";
                system("pause");
        }

    } while(pilih != 0);
}

void menuUtama::menuAkun(){

    int pilih;

    do{
        clearScreen();

        cout << "----------------------------------------\n";
        cout << "              AKUN CUSTOMER\n";
        cout << "----------------------------------------\n\n";

        cout << "1. Pengaturan Akun\n";
        cout << "2. Berikan Ulasan dan Rating\n";
        cout << "0. Kembali\n";

        cout << "\nPilih : ";
        cin >> pilih;
        cin.ignore();

        switch(pilih){

            case 1:
                pengaturanAkun();
                break;

            case 2:
                cout << "\nMenu Ulasan dan Rating dipilih\n";
                system("pause");
                break;

            case 0:
                cout << "\nKembali...\n";
                system("pause");
                break;

            default:
                cout << "\nPilihan tidak valid!\n";
                system("pause");
        }

    } while(pilih != 0);
}

void menuUtama::pengaturanAkun(){

    int pilih;

    do{
        clearScreen();

        cout << "----------------------------------\n";
        cout << "         PENGATURAN AKUN\n";
        cout << "----------------------------------\n";

        cout << "1. Ubah Nama\n";
        cout << "2. Ubah Username\n";
        cout << "3. Ubah Password\n";
        cout << "4. Ubah Alamat\n";
        cout << "5. Ubah No. Telepon\n";
        cout << "6. Lihat Informasi Akun\n";
        cout << "0. Kembali\n";

        cout << "\nPilih : ";
        cin >> pilih;
        cin.ignore();

        switch(pilih){

            case 1:
                cout << "Nama Baru : ";
                getline(cin, akun.nama);
                updateDataFile();
                break;

            case 2:
                cout << "Username Baru : ";
                getline(cin, akun.username);
                updateDataFile();
                break;

            case 3:
                cout << "Password Baru : ";
                getline(cin, akun.password);
                updateDataFile();
                break;

            case 4:
                cout << "Alamat Baru : ";
                getline(cin, akun.alamat);
                updateDataFile();
                break;

            case 5:
                cout << "No Telp Baru : ";
                getline(cin, akun.noTelp);
                updateDataFile();
                break;

            case 6:
                tampilkanAkun();
                break;

            case 0:
                cout << "\nKembali...\n";
                system("pause");
                break;

            default:
                cout << "\nPilihan tidak valid!\n";
                system("pause");
        }

    } while(pilih != 0);
}

void menuUtama::updateDataFile(){

    ifstream fileLama(namaFile.c_str());
    ofstream fileBaru("temp.txt");

    while(getline(fileLama, fileData.nama)){

        getline(fileLama, fileData.username);
        getline(fileLama, fileData.password);
        getline(fileLama, fileData.alamat);
        getline(fileLama, fileData.noTelp);
        getline(fileLama, garis);

        if(fileData.username == akunLama.username &&
           fileData.password == akunLama.password){

            fileBaru << akun.nama << endl;
            fileBaru << akun.username << endl;
            fileBaru << akun.password << endl;
            fileBaru << akun.alamat << endl;
            fileBaru << akun.noTelp << endl;
            fileBaru << "------------------------" << endl;

        }else{

            fileBaru << fileData.nama << endl;
            fileBaru << fileData.username << endl;
            fileBaru << fileData.password << endl;
            fileBaru << fileData.alamat << endl;
            fileBaru << fileData.noTelp << endl;
            fileBaru << "------------------------" << endl;
        }
    }

    fileLama.close();
    fileBaru.close();

    remove(namaFile.c_str());
    rename("temp.txt", namaFile.c_str());

    akunLama = akun;

    cout << "\nData berhasil diperbarui!\n";
    system("pause");
}

void menuUtama::tampilkanAkun(){

	clearScreen();

    cout << "----------------------------------\n";
    cout << "        INFORMASI AKUN\n";
    cout << "----------------------------------\n";

    cout << "Nama      : " << akun.nama << endl;
    cout << "Username  : " << akun.username << endl;
    cout << "Password  : " << akun.password << endl;
    cout << "Alamat    : " << akun.alamat << endl;
    cout << "No Telp   : " << akun.noTelp << endl;

    cout << "----------------------------------\n";

    system("pause");
}

int main(){

	menuUtama x;
	x.pilihPengguna();

	return 0;
}
