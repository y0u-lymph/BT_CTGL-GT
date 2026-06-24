#include <iostream>
#include <string>
#include <queue>
#include <iomanip>

using namespace std;

const int Sotinh_max = 5; 
const int INF = 1e9; 

const string DSTinh[Sotinh_max] = { "A", "B", "C", "D", "E" };

struct Matran { 
    int Sotinhxet; 
    int matrix[Sotinh_max][Sotinh_max];
};

void Khoitaomatran(Matran &g, int n) { 
    g.Sotinhxet = n; 
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) {
            g.matrix[i][j] = 0; 
        }
    }
}

void ThemDuongMaTran(Matran &g, int u, int v, int matuyen) { 
    g.matrix[u][v] = matuyen;  
    g.matrix[v][u] = matuyen; 
}

// Tối ưu: Truyền tham chiếu hằng (const Matran &g) để tăng hiệu năng
void mtrwarshall(const Matran &g, int P[Sotinh_max][Sotinh_max]) {
    int n = g.Sotinhxet;
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) { 
            if (i == j || g.matrix[i][j] != 0) {
                P[i][j] = 1; 
            } else {
                P[i][j] = 0; 
            }
        } 
    }
    
    // Thuật toán Warshall
    for (int k = 0; k < n; k++) { 
        for (int i = 0; i < n; i++) { 
            for (int j = 0; j < n; j++) { 
                if (P[i][j] == 0) { 
                    P[i][j] = P[i][k] && P[k][j]; 
                } 
            } 
        } 
    } 
}

// Tối ưu: Truyền const Matran &g và sửa lỗi trùng tên biến vòng lặp i
void mtr_Dijkstra(const Matran &g, int Dinhdau, int kc[Sotinh_max], int tinhtruoc[Sotinh_max]) { 
    int n = g.Sotinhxet;
    bool daduyet[Sotinh_max]; 

    for (int i = 0; i < n; i++) { 
        kc[i] = INF; 
        daduyet[i] = false; 
        tinhtruoc[i] = -1; 
    } 
    kc[Dinhdau] = 0; 

    for (int step = 0; step < n - 1; step++) { // Đổi tên biến vòng ngoài thành 'step'
        int kc_min = INF;  
        int u = -1; 
        
        for (int i = 0; i < n; i++) { // Vòng lặp tìm đỉnh u có khoảng cách ngắn nhất
            if (!daduyet[i] && kc[i] < kc_min) { 
                kc_min = kc[i]; 
                u = i;
            } 
        }  
        
        if (u == -1) break; 
        daduyet[u] = true; 

        for (int v = 0; v < n; v++) { 
            if (!daduyet[v] && g.matrix[u][v] != 0) { 
                if (kc[u] + g.matrix[u][v] < kc[v]) { 
                    kc[v] = kc[u] + g.matrix[u][v]; 
                    tinhtruoc[v] = u; 
                } 
            } 
        } 
    }
}

// Hàm bổ sung: Truy vết và in đường đi từ đỉnh nguồn đến đích
void InDuongDi(int tinhtruoc[], int dich) {
    if (tinhtruoc[dich] == -1) {
        cout << DSTinh[dich];
        return;
    }
    InDuongDi(tinhtruoc, tinhtruoc[dich]);
    cout << " -> " << DSTinh[dich];
}

void Inmatran(const int P[Sotinh_max][Sotinh_max], int n) { 
    cout << setw(6) << " "; 
    for (int j = 0; j < n; j++) { 
        cout << setw(5) << DSTinh[j]; 
    } 
    cout << endl; 
    for (int i = 0; i < n; i++) { 
        cout << setw(6) << DSTinh[i]; 
        for (int j = 0; j < n; j++) {
            cout << setw(5) << P[i][j]; 
        }
        cout << endl; 
    } 
}

int main() { 
    int n = Sotinh_max; 
    Matran g;  
    Khoitaomatran(g, n);
    
    int CacTuyenDuong[][3] = { 
        {0, 1, 4}, {0, 2, 2}, {1, 2, 5}, {1, 3, 10},  
        {2, 3, 3}, {2, 4, 7}, {3, 4, 4} 
    }; 

    int soTuyen = sizeof(CacTuyenDuong) / sizeof(CacTuyenDuong[0]);  
    for(int i = 0; i < soTuyen; i++) {  
        ThemDuongMaTran(g, CacTuyenDuong[i][0], CacTuyenDuong[i][1], CacTuyenDuong[i][2]);
    } 
    
    cout << "--- Ma tran ban dau ---" << endl;  
    Inmatran(g.matrix, n);

    cout << "\n--- Ma tran tim duong di (Thuat toan Warshall) ---" << endl;  
    int P[Sotinh_max][Sotinh_max]; 
    mtrwarshall(g, P); 
    Inmatran(P, n);
    
    int kc[Sotinh_max]; 
    int tinhtruoc[Sotinh_max]; 
    int nguon = 0; // Đỉnh bắt đầu là A
    
    mtr_Dijkstra(g, nguon, kc, tinhtruoc); 
    
    cout << "\n--- Ket qua thuat toan Dijkstra (Tu dinh A) ---" << endl;  
    cout << left << setw(10) << "Dich" << setw(15) << "Khoang cach" << "Chi tiet duong di" << endl;
    cout << string(45, '-') << endl;

    for (int i = 0; i < n; i++) { 
        cout << left << setw(10) << DSTinh[i]; 
        if (kc[i] == INF) {
            cout << setw(15) << "Khong co duong" << endl;
        } else {
            cout << setw(15) << kc[i];
            // Nếu là chính nó thì không cần truy vết
            if (i == nguon) {
                cout << DSTinh[nguon] << endl;
            } else {
                InDuongDi(tinhtruoc, i);
                cout << endl;
            }
        } 
    }
    
    return 0;
}
