#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Struktur edge: tujuan dan jarak
struct Edge {
    int tujuan;
    int jarak;
};

// Nama kota
string namaKota[5] = {
    "Ikan Bakar Pak Harry",    // A (0)
    "Gudang Kaleng Bekas",     // B (1)
    "Sushi Kucing Alya",       // C (2)
    "Kedai IKLC",              // D (3)
    "Pasar Ikan Tengah Malam"  // E (4)
};

// Graf tidak berarah berbobot
vector<Edge> graf[5] = {    //0=A, 1=B, 2=C, 3=D, 4=E
    {{2, 2}, {1, 5}},       // A -> C(2), B(5)
    {{0, 5}, {3, 4}},       // B -> A(5), D(4)
    {{0, 2}, {3, 1}},       // C -> A(2), D(1)
    {{1, 4}, {2, 1}, {4, 3}}, // D -> B(4), C(1), E(3)
    {{3, 3}}                // E -> D(3)
};

// Fungsi rekursif DFS untuk menelusuri seluruh kota
void dfsUtil(int kota, bool visited[], int asal, int jarakDariAsal, int &totalJarak, int &totalLangkah) {
    visited[kota] = true; // Tandai kota ini sudah dikunjungi

    if (asal != -1) { // Jika bukan kota awal
        cout << jarakDariAsal << "m\n"; // Tampilkan jarak dari asal
        totalJarak += jarakDariAsal; // Tambahkan ke total jarak
        totalLangkah++; // Tambahkan ke total langkah
    }

    //untuk menampilkan nama kota dan hurufnya
    cout << namaKota[kota] << " (" << char('A' + kota) << ")\n";

    for (int i = 0; i < graf[kota].size(); i++) { // Telusuri semua tetangga
        int next = graf[kota][i].tujuan; // Kota tujuan berikutnya
        int jarak = graf[kota][i].jarak; // Jarak ke kota tujuan berikutnya
        if (!visited[next]) { // Jika kota belum dikunjungi
            dfsUtil(next, visited, kota, jarak, totalJarak, totalLangkah); // Rekursif ke kota berikutnya
        }
    }
}

// Fungsi DFS utama
void DFS(int start) {
    bool visited[5] = {false}; // kota belum ada yang dikunjungi
    int totalJarak = 0, totalLangkah = 0; //saat belum ada kota yang dikunjungi

    cout << "\nPENJELAJAHAN PARUL (DFS dari " << char('A' + start) << "):\n";
    // Panggil fungsi rekursif DFS untuk menelusuri kota
    dfsUtil(start, visited, -1, 0, totalJarak, totalLangkah);

    cout << "\nTotal langkah: " << totalLangkah << " edge";
    cout << "\nTotal jarak: " << totalJarak << " meter\n";
}

// Fungsi BFS untuk mencari jalur terpendek
void BFS(int start, int goal) {
    queue<vector<int>> q; // Antrian untuk menyimpan jalur
    bool visited[5] = {false}; // kota belum ada yang dikunjungi

    q.push({start}); //masukkan kota awal ke antrian
    visited[start] = true; //menandai kota awal sudah dikunjungi

    // Proses BFS untuk mencari jalur terpendek
    while (!q.empty()) { //selama antrian tidak kosong (ada jalur yang belum diperiksa)
        vector<int> path = q.front(); //ambil jalur terdepan
        q.pop(); //hapus jalur tersebut karena akan diproses

        int kotaSekarang = path.back(); //ambil kota terakhir di jalur

        if (kotaSekarang == goal) { //jika sudah sampai kota tujuan
            cout << "\nJALUR TERCEPAT PARUL (BFS):\n";
            int totalJarak = 0;

            // untuk menampilkan nama kota dan hurufnya
            for (int i = 0; i < path.size(); i++) {
                int k = path[i];
                cout << namaKota[k] << " (" << char('A' + k) << ")\n";
                // menampilkan jarak antar kota (jika bukan kota terakhir):
                if (i < path.size() - 1) { // jika bukan kota terakhir
                    int next = path[i + 1]; // kota berikutnya
                    for (int j = 0; j < graf[k].size(); j++) { // mencari jarak ke kota berikutnya
                        if (graf[k][j].tujuan == next) { 
                            cout << graf[k][j].jarak << "m\n";
                            totalJarak += graf[k][j].jarak; // tambahkan ke total jarak
                            break;
                        }
                    }
                }
            }

            // menampilkan jalur terpendek
            cout << "\nJalur terpendek: ";
            for (int i = 0; i < path.size(); i++) {
                cout << char('A' + path[i]);
                if (i < path.size() - 1) cout << " -> ";
            }
            cout << "\nTotal langkah: " << path.size() - 1 << " edge";
            cout << "\nTotal jarak: " << totalJarak << " meter\n";
            return;
        }

        // Telusuri semua tetangga kota sekarang
        for (int i = 0; i < graf[kotaSekarang].size(); i++) {
            int next = graf[kotaSekarang][i].tujuan;
            if (!visited[next]) { // Jika kota belum dikunjungi
                visited[next] = true; // Tandai kota sudah dikunjungi
                vector<int> newPath = path; // Salin jalur saat ini
                newPath.push_back(next); // Tambahkan kota berikutnya ke jalur
                q.push(newPath); //masukkan ke antrian
            }
        }
    }
}

int main() {
    DFS(0); // 0 = A

    BFS(0, 4); // 0 = A, 4 = E

    return 0;
}