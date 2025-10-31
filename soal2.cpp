#include <iostream>     // Library untuk input dan output (cin, cout)
#include <string>       // Library untuk tipe data string
using namespace std;    // Agar tidak perlu menulis std:: setiap kali pakai fungsi dari std

// Struktur node untuk menyimpan data film
struct Node {
    string judul;       // Menyimpan judul film
    int tahun;          // Menyimpan tahun rilis film
    int rating;         // Menyimpan rating film
    Node* next;         // Pointer ke node berikutnya
};

// Fungsi untuk menambahkan node di depan linked list
void insertFront(Node*& head, string judul, int tahun, int rating) {
    Node* newNode = new Node;    // Membuat node baru di memori heap
    newNode->judul = judul;      // Mengisi data judul
    newNode->tahun = tahun;      // Mengisi data tahun
    newNode->rating = rating;    // Mengisi data rating
    newNode->next = head;        // Menghubungkan node baru ke node pertama sebelumnya
    head = newNode;              // Menjadikan node baru sebagai head (node pertama)
}

// Fungsi untuk menambahkan node di belakang linked list
void insertBack(Node*& head, string judul, int tahun, int rating) {
    Node* newNode = new Node;    // Membuat node baru
    newNode->judul = judul;      // Mengisi data judul
    newNode->tahun = tahun;      // Mengisi data tahun
    newNode->rating = rating;    // Mengisi data rating
    newNode->next = nullptr;     // Node terakhir menunjuk ke NULL

    if (head == nullptr) {       // Jika list masih kosong
        head = newNode;          // Node baru jadi head
    } else {
        Node* temp = head;       // Menelusuri list dari awal
        while (temp->next != nullptr) // Selama belum sampai node terakhir
            temp = temp->next;
        temp->next = newNode;    // Sambungkan node terakhir dengan node baru
    }
}

// Fungsi untuk menambahkan node setelah node tertentu
bool insertAfter(Node*& head, string targetjudul, string judul, int tahun, int rating) {
    Node* temp = head;           // Mulai dari head
    while (temp != nullptr) {    // Telusuri hingga akhir
        if (temp->judul == targetjudul) {     // Jika ditemukan judul target
            Node* newNode = new Node;         // Buat node baru
            newNode->judul = judul;           // Isi data film baru
            newNode->tahun = tahun;
            newNode->rating = rating;
            newNode->next = temp->next;       // Hubungkan ke node setelah target
            temp->next = newNode;             // Hubungkan target ke node baru
            return true;                      // Berhasil menambah, kembalikan true
        }
        temp = temp->next;                    // Lanjut ke node berikutnya
    }
    return false;                             // Jika target tidak ditemukan
}

// Fungsi untuk menghapus node berdasarkan judul
bool deleteByjudul(Node*& head, string judul) {
    if (head == nullptr) return false;        // Jika list kosong, langsung keluar

    if (head->judul == judul) {               // Jika film yang dihapus ada di head
        Node* temp = head;                    // Simpan sementara untuk dihapus
        head = head->next;                    // Geser head ke node berikutnya
        delete temp;                          // Hapus node lama
        return true;                          // Berhasil
    }

    Node* current = head;                     // Mulai dari node pertama
    while (current->next != nullptr) {        // Telusuri hingga akhir
        if (current->next->judul == judul) {  // Jika node berikutnya cocok
            Node* temp = current->next;       // Simpan node yang akan dihapus
            current->next = temp->next;       // Hubungkan ke node setelahnya
            delete temp;                      // Hapus node target
            return true;                      // Berhasil
        }
        current = current->next;              // Lanjut ke node berikutnya
    }
    return false;                             // Tidak ditemukan
}

// Fungsi untuk menampilkan seluruh isi linked list
void display(Node* head) {
    if (head == nullptr) {                    // Jika list kosong
        cout << "Daftar film kosong.\n";      // Tampilkan pesan
        return;
    }

    int i = 1;                                // Nomor urut tampilan
    while (head != nullptr) {                 // Telusuri seluruh node
        cout << i << ". " << head->judul << " (" << head->tahun 
             << ") - Rating " << head->rating << endl; // Tampilkan data
        head = head->next;                    // Pindah ke node berikutnya
        i++;
    }
}

// Fungsi untuk menghapus seluruh isi list (membersihkan memori)
void clearList(Node*& head) {
    while (head != nullptr) {                 // Selama masih ada node
        Node* temp = head;                    // Simpan node sementara
        head = head->next;                    // Geser head ke node berikutnya
        delete temp;                          // Hapus node lama
    }
}

// Fungsi utama
int main() {
    Node* head = nullptr;                     // Inisialisasi list kosong
    int n;
    cout << "Masukkan jumlah film awal: ";    // Minta jumlah data awal
    cin >> n;
    cin.ignore();                             // Membersihkan buffer enter

    // Input data film awal
    for (int i = 0; i < n; i++) {
        string judul;
        int tahun, rating;
        cout << "\nFilm ke-" << i + 1 << endl;
        cout << "Judul  : "; getline(cin, judul);  // Input judul (pakai getline)
        cout << "Tahun  : "; cin >> tahun;         // Input tahun
        cout << "Rating : "; cin >> rating;        // Input rating
        cin.ignore();                              // Bersihkan buffer
        insertBack(head, judul, tahun, rating);    // Tambahkan ke akhir list
    }

    cout << "\n=== DAFTAR FILM AWAL ===\n";
    display(head);                                // Tampilkan film awal

    // Menanyakan apakah user ingin menghapus film
    char hapus;
    cout << "\nApakah ingin menghapus film? (y/n): ";
    cin >> hapus;
    cin.ignore();

    if (hapus == 'y' || hapus == 'Y') {          // Jika memilih hapus
        string judul;
        cout << "Masukkan judul film yang sudah ditonton: ";
        getline(cin, judul);
        bool ok = deleteByjudul(head, judul);    // Hapus film dengan judul itu
        if (ok) cout << "Film \"" << judul << "\" berhasil dihapus.\n";
        else cout << "Film \"" << judul << "\" tidak ditemukan.\n";
    }

    int choice;
    do {
        // Tampilkan menu utama
        cout << "\n=== MENU KOLEKSI FILM HARRY ===\n";
        cout << "1. Tambah film di depan\n";
        cout << "2. Tambah film di tengah (setelah film tertentu)\n";
        cout << "3. Tambah film di belakang\n";
        cout << "4. Hapus film\n";
        cout << "5. Tampilkan daftar film\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> choice;
        cin.ignore();

        // Tambah di depan
        if (choice == 1) {
            string judul; int tahun, rating;
            cout << "Judul  : "; getline(cin, judul);
            cout << "Tahun  : "; cin >> tahun;
            cout << "Rating : "; cin >> rating;
            cin.ignore();
            insertFront(head, judul, tahun, rating);  // Panggil fungsi insertFront
            cout << "Film berhasil ditambahkan di depan.\n";
        }

        // Tambah di tengah (setelah judul tertentu)
        else if (choice == 2) {
            string target, judul; int tahun, rating;
            cout << "Masukkan judul film yang ingin disisipi setelahnya: ";
            getline(cin, target);
            cout << "Judul baru  : "; getline(cin, judul);
            cout << "Tahun       : "; cin >> tahun;
            cout << "Rating      : "; cin >> rating;
            cin.ignore();
            bool ok = insertAfter(head, target, judul, tahun, rating);  // Sisipkan node
            if (ok) cout << "Film berhasil ditambahkan setelah \"" << target << "\".\n";
            else cout << "Film \"" << target << "\" tidak ditemukan.\n";
        }

        // Tambah di belakang
        else if (choice == 3) {
            string judul; int tahun, rating;
            cout << "Judul  : "; getline(cin, judul);
            cout << "Tahun  : "; cin >> tahun;
            cout << "Rating : "; cin >> rating;
            cin.ignore();
            insertBack(head, judul, tahun, rating);  // Tambah di akhir
            cout << "Film berhasil ditambahkan di belakang.\n";
        }

        // Hapus film berdasarkan judul
        else if (choice == 4) {
            string judul;
            cout << "Masukkan judul film yang ingin dihapus: ";
            getline(cin, judul);
            bool ok = deleteByjudul(head, judul);
            if (ok) cout << "Film \"" << judul << "\" berhasil dihapus.\n";
            else cout << "Film \"" << judul << "\" tidak ditemukan.\n";
        }

        // Tampilkan daftar film
        else if (choice == 5) {
            cout << "\n=== DAFTAR FILM SAAT INI ===\n";
            display(head);
        }

        // Keluar dari program
        else if (choice == 0) {
            cout << "Keluar dari program.\n";
        }

        // Jika input salah
        else {
            cout << "Pilihan tidak valid!\n";
        }

    } while (choice != 0);       // Ulangi sampai user memilih keluar

    clearList(head);             // Hapus semua node sebelum keluar (bersihkan memori)
    return 0;                    // Program selesai
}
