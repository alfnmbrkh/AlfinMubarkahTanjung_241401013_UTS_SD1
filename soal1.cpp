#include <iostream>   // Library untuk input dan output (cin, cout)
#include <string>     // Library untuk tipe data string
#include <vector>     // Library untuk menggunakan vector (array dinamis)
using namespace std;  // Agar tidak perlu menulis std:: setiap kali pakai fungsi dari std

// Struktur untuk menyimpan data pasien
struct Patient {
    string nama;        // Menyimpan nama hewan pasien
    string jenis;       // Menyimpan jenis hewan (misal: kucing, anjing, dll)
    int umur;           // Umur hewan
    int darurat;        // Tingkat darurat (1-5), semakin tinggi semakin darurat
    int arrivalIndex;   // Menyimpan urutan kedatangan pasien
};

int main() {
    int n; // Variabel untuk jumlah pasien
    cout << "Masukkan jumlah pasien: ";  // Menampilkan pesan input
    cin >> n;    // Menerima jumlah pasien dari user
    cin.ignore(); // Membersihkan buffer agar getline berikutnya tidak terlewat

    vector<Patient> pasien; // Membuat vector untuk menyimpan semua data pasien

    // Perulangan untuk input data setiap pasien
    for (int i = 0; i < n; i++) {
        Patient p;  // Membuat variabel sementara untuk menyimpan data 1 pasien
        cout << "\nPasien ke-" << i + 1 << endl;
        cout << "Nama hewan   : ";
        getline(cin, p.nama);   // Input nama pasien
        cout << "Jenis hewan  : ";
        getline(cin, p.jenis);  // Input jenis hewan
        cout << "Umur         : ";
        cin >> p.umur;          // Input umur hewan
        cout << "Tingkat darurat (1-5): ";
        cin >> p.darurat;       // Input tingkat darurat (semakin besar semakin prioritas)
        p.arrivalIndex = i;     // Simpan urutan kedatangan pasien (0, 1, 2, ...)
        cin.ignore();           // Bersihkan buffer untuk menghindari error pada getline berikutnya
        pasien.push_back(p);    // Masukkan data pasien ke dalam vector
    }

    // Proses pengurutan data pasien berdasarkan prioritas
    // Kriteria:
    // 1. Darurat lebih besar harus di depan
    // 2. Jika darurat sama, maka urut berdasarkan kedatangan (arrivalIndex)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (pasien[j].darurat < pasien[j + 1].darurat ||  // Bandingkan tingkat darurat
               (pasien[j].darurat == pasien[j + 1].darurat && // Jika sama daruratnya,
                pasien[j].arrivalIndex > pasien[j + 1].arrivalIndex)) { // lihat siapa datang lebih dulu
                Patient temp = pasien[j];       // Tukar posisi pasien
                pasien[j] = pasien[j + 1];
                pasien[j + 1] = temp;
            }
        }
    }

    // Tampilkan hasil urutan pelayanan setelah disortir
    cout << "\n=== Urutan Pelayanan ===\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". " << pasien[i].nama << " (" << pasien[i].umur
             << " tahun)" << " - Darurat " << pasien[i].darurat << endl;
    }

    return 0; // Akhiri program
}
