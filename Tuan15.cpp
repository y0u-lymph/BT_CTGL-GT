#include <iostream>
#include <string>
#include <queue>
#include <iomanip>

using namespace std;

const int Sotinh_max = 11;
const string DSTinh[Sotinh_max] = {
    "HN", "TN", "BN", "BG", "UB", "HP", "HD", "HY", "PL", "HB", "ST"
};

// Cấu trúc ma trận kề
struct Matran {
    int Sotinhxet;
    int matrix[Sotinh_max][Sotinh_max];
};

void Khoitaomatran(Matran &g, int n) {
    g.Sotinhxet = n;
    // Sử dụng loop-unrolling hoặc viết gọn lại bằng vòng lặp tiêu chuẩn
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

// Cấu trúc danh sách kề (Danh sách liên kết)
struct Nut {
    int idTinhKe; 
    int maTuyenDuong; 
    Nut* tiepTheo; 
};

struct DanhSachDoThi {
    int Sotinhxet;
    Nut* dau[Sotinh_max];
};

void Khoitaods(DanhSachDoThi &dt, int n) {
    dt.Sotinhxet = n;
    for (int i = 0; i < n; i++) {
        dt.dau[i] = nullptr;
    }
}

void ThemDuongDanhSach(DanhSachDoThi &dt, int u, int v, int maTuyen) {
    // Tối ưu hóa việc cấp phát vùng nhớ trực tiếp bằng Constructor giả lập (nếu cần) 
    // hoặc giữ cấu trúc cũ nhưng viết mạch lạc hơn
    Nut* nutMoi1 = new Nut{v, maTuyen, dt.dau[u]};
    dt.dau[u] = nutMoi1;

    Nut* nutMoi2 = new Nut{u, maTuyen, dt.dau[v]};
    dt.dau[v] = nutMoi2;
}

// HÀM QUAN TRỌNG BỔ SUNG: Giải phóng bộ nhớ của Danh sách liên kết để tránh Memory Leak
void GiaiPhongDanhSach(DanhSachDoThi &dt) {
    for (int i = 0; i < dt.Sotinhxet; i++) {
        Nut* hienTai = dt.dau[i];
        while (hienTai != nullptr) {
            Nut* tam = hienTai;
            hienTai = hienTai->tiepTheo;
            delete tam;
        }
        dt.dau[i] = nullptr;
    }
}

// Tối ưu: Truyền const reference để tránh sao chép dữ liệu ma trận vô ích
void BFS_MaTran(const Matran &g, int dinhBatDau) {
    bool Daduyet[Sotinh_max] = {false};
    queue<int> hangDoi;

    Daduyet[dinhBatDau] = true;
    hangDoi.push(dinhBatDau);

    while (!hangDoi.empty()) {
        int u = hangDoi.front();
        hangDoi.pop();

        cout << DSTinh[u];
        
        // Xem còn phần tử trong hàng đợi không để in dấu mũi tên cho đẹp
        bool hasNext = false;
        for (int v = 0; v < g.Sotinhxet; v++) {
            if (g.matrix[u][v] != 0 && !Daduyet[v]) {
                Daduyet[v] = true;
                hangDoi.push(v);
                hasNext = true;
            }
        }
        if (!hangDoi.empty() || hasNext) cout << " -> ";
    }
    cout << " -> END" << endl;
}

// Tối ưu: Sử dụng const Matran &g
void InMaTran(const Matran &g) {
    cout << "\nLUU TRU THEO MA TRAN LAN CAN\n" << endl;
    cout << setw(6) << " ";
    for (int j = 0; j < g.Sotinhxet; j++) {
        cout << setw(6) << DSTinh[j];
    }
    cout << "\n" << string(6 + g.Sotinhxet * 6, '-') << endl;

    for (int i = 0; i < g.Sotinhxet; i++) {
        cout << setw(5) << DSTinh[i] << " |";
        for (int j = 0; j < g.Sotinhxet; j++) {
            if (g.matrix[i][j] == 0) {
                cout << setw(6) << "0";
            } else {
                cout << setw(5) << "D" << g.matrix[i][j];
            }
        }
        cout << endl;
    }
}

// Tối ưu: Sử dụng const DanhSachDoThi &dt
void InDanhSach(const DanhSachDoThi &dt) {
    cout << "\n================ LUU TRU THEO DANH SACH LIEN KET ================\n" << endl;
    for (int i = 0; i < dt.Sotinhxet; i++) {
        cout << setw(3) << DSTinh[i] << " -> ";
        Nut* tam = dt.dau[i];
        if (tam == nullptr) {
            cout << "Khong co tuyen duong nao";
        } else {
            while (tam != nullptr) {
                cout << "[" << DSTinh[tam->idTinhKe] << " | D" << tam->maTuyenDuong << "]";
                if (tam->tiepTheo != nullptr) cout << " -> ";
                tam = tam->tiepTheo;
            }
        }
        cout << endl;
    }
}

int main() {
    int n = Sotinh_max;
    Matran g;
    Khoitaomatran(g, n);

    DanhSachDoThi dt;
    Khoitaods(dt, n);

    int CacTuyenDuong[][3] = {
        {0, 6, 1}, {6, 7, 2}, {7, 8, 3}, {0, 8, 4}, {0, 9, 5},
        {0, 10, 6}, {0, 1, 7}, {0, 2, 8}, {2, 3, 9}, {3, 4, 10},
        {2, 4, 11}, {4, 5, 12}, {6, 5, 13}
    };

    int soTuyen = sizeof(CacTuyenDuong) / sizeof(CacTuyenDuong[0]);
    for (int i = 0; i < soTuyen; i++) {
        ThemDuongMaTran(g, CacTuyenDuong[i][0], CacTuyenDuong[i][1], CacTuyenDuong[i][2]);
        ThemDuongDanhSach(dt, CacTuyenDuong[i][0], CacTuyenDuong[i][1], CacTuyenDuong[i][2]);
    }

    InMaTran(g);
    InDanhSach(dt);

    cout << "\nDUYET DO THI THEO CHIEU RONG (BFS) TU " << DSTinh[0] << ":" << endl;
    BFS_MaTran(g, 0);

    // Dọn dẹp bộ nhớ trước khi thoát
    GiaiPhongDanhSach(dt);

    return 0;
}
