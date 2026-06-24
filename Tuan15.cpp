#include <iostream>
#include <string>
#include <queue>
#include <iomanip>
using namespace std;

const int Sotinh_max = 5;    // khai bao 5 dinh theo de bai, sua lai tu 11 tinh
const int INF = 1e9;          // INF là vo cuc, dung trong thuat toan dijkstra

const string DSTinh[Sotinh_max] = { "A", "B", "C", "D", "E"};  // Chinh sua lai cho vi du Dijkstra, slide 29

struct Matran {   // khai báo
    int Sotinhxet;
    int matrix[Sotinh_max][Sotinh_max];
};

void Khoitaomatran(Matran &g, int n) { // tạo mtr trống (0)
    g.Sotinhxet = n;
    for (int i = 0; i < n; i++) {     // mtr trống
        for (int j = 0; j < n; j++)  g.matrix[i][j] = 0; }
}

void ThemDuongMaTran(Matran &g, int u, int v, int matuyen) {
    g.matrix[u][v] = matuyen;  
    g.matrix[v][u] = matuyen; }


void mtrwarshall(Matran g, int P[Sotinh_max][Sotinh_max]) {
int n = g.Sotinhxet;
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {  // duyet toan ma tran
        if (i == j) P[i][j] = 1;    // luon co duogn den chinh no
            else if (g.matrix[i][j] != 0) P[i][j] = 1; // co duong
        else 
            P[i][j] = 0; // Neu =0 thi co the kh co duong di truc tiep
            } }
// bo sung thuat toan warshall
for (int k = 0; k < n; k++) {  // do tung gia tri dinh trung gian k
    for (int i = 0; i < n; i++) {   // duyyet toan mtr
        for (int j = 0; j < n; j++) {
            if (P[i][j] == 0) {  P[i][j] = P[i][k] && P[k][j]; } } // lap lai de tim duong
    }  }
 }

 // Thuat toan tim duong di ngan nhat Dijkstra
void mtr_Dijkstra(Matran g, int Dinhdau, int kc[Sotinh_max], int tinhtruoc[Sotinh_max]) {
    int n = g.Sotinhxet;
    bool daduyet[Sotinh_max];  // Mang dung de danh dau cac dinh da duyet

for (int i = 0; i < n; i++) {    // khoi tao
    kc[i] = INF;            // kc den cac dinh khac là vo cung
    daduyet[i] = false;     // chua co tinh nao duyet khi khoi tao
    tinhtruoc[i] = -1;  }     // kh co tinh da duyet qua
    kc[Dinhdau] = 0;  // kc den chinh no bang 0

    for (int i = 0; i < n - 1; i++) {
        int kc_min = INF;   
        int u = -1;
        for (int i = 0; i < n; i++) {
            if (!daduyet[i] && kc[i] < kc_min) { // tim tinh gan nhat chua duyet
            kc_min = kc[i];   // cap nhat kc nho nhat
            u = i;}  // cap nhat tinh u gan nhat
        }   
        if (u == -1) break;  // neu kh co duong di den tinh khac thi dung
        daduyet[u] = true; // Danh dau da xet qua u

        for (int v = 0; v < n; v++) {   // duyet tat ca cac dinh
            if (!daduyet[v] && g.matrix[u][v] != 0) {    // neu gap tinh chua duyet (v) va co duogn di tu u toi do
                if (kc[u] + g.matrix[u][v] < kc[v]) {   // neu kc tu dau den u + kc tu u den v nho hon kc tu dau den v
                kc[v] = kc[u] + g.matrix[u][v]; // Cap nhat kc
                tinhtruoc[v] = u;   }                       //danh dau lai: đi qua u rồi tới v
            }   }
    }
}

// ham in ma tran
void Inmatran(int P[Sotinh_max][Sotinh_max], int n) {
    cout << setw(6) << " ";
    for (int j = 0; j < n; j++) { cout << setw(5) << DSTinh[j]; }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << setw(6) << DSTinh[i];
        for (int j = 0; j < n; j++)    cout << setw(5) << P[i][j];
        cout << endl;
    }  }


int main() {
    int n = Sotinh_max;
    Matran g; 
    Khoitaomatran(g, n);
int CacTuyenDuong[][3] = {  {0, 1, 4}, {0, 2, 2}, {1, 2, 5}, {1, 3, 10}, 
 {2, 3, 3},  {2, 4, 7}, {3, 4, 4}  }; // cap nhat lai dlieu

    int soTuyen = sizeof(CacTuyenDuong) / sizeof(CacTuyenDuong[0]);
    
    for(int i = 0; i < soTuyen; i++) { 
    ThemDuongMaTran(g, CacTuyenDuong[i][0], CacTuyenDuong[i][1], CacTuyenDuong[i][2]);}
    cout << "             Ma tran ban dau" << endl ; 
    Inmatran(g.matrix, n);


    cout << " \n    Ma tran tim duong di ( thuat toan Warshall)" << endl; 
    int P[Sotinh_max][Sotinh_max];
    mtrwarshall(g, P);
    Inmatran(P, n);

    int kc[Sotinh_max];       // khai bao de goi ham
    int tinhtruoc[Sotinh_max];
    int nguon = 0; // vi du tu dinh A
    
    mtr_Dijkstra(g, nguon, kc, tinhtruoc);  // goi ham khoi tao
    cout << " \nTim duong di ngan nhat bang thuat toan Dijkstra (xet tu dinh A):" << endl; 
    cout << left << setw(15) << "Tinh" << "Kc" << endl;

    for (int i = 0; i < n; i++) {  // test ham khoi tao voi dinh A lam goc
        cout  << left << setw(15) << DSTinh[i];
        if (kc[i] == INF)   cout << "Vo cung  " << endl;
        else   cout << kc[i] << endl;      }

    return 0;
}
