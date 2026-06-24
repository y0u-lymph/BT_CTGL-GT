#include <iostream>
#include <string>
#include <queue>
#include <iomanip>
using namespace std;

const int Sotinh_max = 11;    // khai bao 11 tinh theo de bai
const string DSTinh[Sotinh_max] = {     // 11 tinh thoe bai
    "HN", "TN", "BN", "BG", "UB", "HP", "HD", "HY", "PL", "HB", "ST"};
// Các ký hiệu tương đương : Hà Nội, Thái Nguyên, Bắc Ninh,... theo đề bài

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
    g.matrix[u][v] = matuyen;  // cap nhat lai, khph ton tai ma la tuyen duong
    g.matrix[v][u] = matuyen; }



struct Nut {       // Dnghia nut
    int idTinhKe;      // Tỉnh kề
    int maTuyenDuong;  // Mã đường
    Nut* tiepTheo;      
};

struct DanhSachDoThi {   // Định nghĩa ds lien ke
    int Sotinhxet;
    Nut* dau[Sotinh_max]; };

void Khoitaods(DanhSachDoThi &dt, int n) {  // DS trống (null)
    dt.Sotinhxet = n;
    for (int i = 0; i < n; i++)  dt.dau[i] = nullptr;
}

void ThemDuongDanhSach(DanhSachDoThi &dt, int u, int v, int maTuyen) { // bo sung
    // ham ket noi 2 node u voi v, tinh u co duogn den v và ngược lại
    Nut* nutMoi1 = new Nut;      // Thêm v vào danh sách của u
    nutMoi1->idTinhKe = v;
    nutMoi1->maTuyenDuong = maTuyen; // cap nhat ma tuyến
    nutMoi1->tiepTheo = dt.dau[u];
    dt.dau[u] = nutMoi1;

    // Thêm u vào danh sách của v , tương tự
    Nut* nutMoi2 = new Nut;   
    nutMoi2->idTinhKe = u;
    nutMoi2->maTuyenDuong = maTuyen;
    nutMoi2->tiepTheo = dt.dau[v];
    dt.dau[v] = nutMoi2;
}

void BFS_MaTran(Matran g, int dinhBatDau) {   // Hàm duyệt theo chiều rộng (BFS)
    bool Daduyet[Sotinh_max] = {false}; // Mảng check đỉnh đã duyệt
    queue<int> hangDoi;                // Hàng đợi q để quản lý các đỉnh kề

    Daduyet[dinhBatDau] = true;   // Đánh dấu đỉnh gốc và đẩy vào hàng đợi
    hangDoi.push(dinhBatDau);

    while (!hangDoi.empty()) {   
        int u = hangDoi.front(); // Lấy đỉnh đầu tiên ra khỏi hàng đợi
        hangDoi.pop();           // Quy tắc 2

        cout << DSTinh[u] << " -> ";   

        for (int v = 0; v < g.Sotinhxet; v++) {   // Có đường
            if (g.matrix[u][v] != 0 && !Daduyet[v]) {
                Daduyet[v] = true;     // Đánh dấu đỉnh là đã được duyệt
                hangDoi.push(v);      // Đẩy vào trong hàng đợi
            } } }
    cout << "END" << endl; }

void InMaTran(Matran g) {
        cout << "\n LUU TRU THEO MA TRAN LAN CAN " << endl;
    cout << setw(15) << " ";
  for (int j = 0; j < g.Sotinhxet; j++) {   cout << setw(15) << DSTinh[j]; }  // in ten tỉnh theo hàng
    cout << endl;

    for (int i = 0; i < g.Sotinhxet; i++) {
        cout << setw(15) << DSTinh[i];   // in ten tinh theo cột
        for (int j = 0; j < g.Sotinhxet; j++) {
            if (g.matrix[i][j] == 0)  cout << setw(15) << "0";   // kh co đường đi
            else {
                string tenDuong = "D" + to_string(g.matrix[i][j]);
                cout << setw(15) << tenDuong; } }    // In ra mã đường
        cout << endl;
    }   }

void InDanhSach(DanhSachDoThi dt) {
    cout << "\n LUU TRU THEO DANH SACH LIEN KET " << endl;
    for (int i = 0; i < dt.Sotinhxet; i++) {     
        cout << setw(3) << DSTinh[i] << " -> ";   // In ra tên tỉnh hiện tại đang xét
        
        Nut* tam = dt.dau[i];
        if (tam == nullptr) {
            cout << "Khong co tuyen duong nao";
        } else {
            while (tam != nullptr) {   // Duyệt DSLK tỉnh htai
                cout << DSTinh[tam->idTinhKe] << " D" << tam->maTuyenDuong; // in theo de bai 
                if (tam->tiepTheo != nullptr) cout << " -> "; 
                tam = tam->tiepTheo; 
            }   
        }
        cout << endl;
    }   }

int main() {
    int n = Sotinh_max;
    Matran g; 
    Khoitaomatran(g, n);
    DanhSachDoThi dt;
    Khoitaods(dt, n);

  
    int CacTuyenDuong[][3] = { {0, 6, 1},  {6, 7, 2}, {7, 8, 3},  {0, 8, 4}, {0, 9, 5},   
        {0, 10, 6}, {0, 1, 7},  {0, 2, 8},  {2, 3, 9}, {3, 4, 10},  {2, 4, 11},  {4, 5, 12},{6, 5, 13}  };
// Nạp dữ liệu vào cấu trúc ma trận 

    int soTuyen = sizeof(CacTuyenDuong) / sizeof(CacTuyenDuong[0]);
    for(int i = 0; i < soTuyen; i++) { ThemDuongMaTran(g, CacTuyenDuong[i][0], CacTuyenDuong[i][1], CacTuyenDuong[i][2]);
    
    ThemDuongDanhSach(dt, CacTuyenDuong[i][0], CacTuyenDuong[i][1], CacTuyenDuong[i][2]);
    }

    InMaTran(g);
    InDanhSach(dt);
        cout << "\n DUYET DO THI THEO CHIEU RONG VA IN TU HN  " << endl;
    BFS_MaTran(g, 0);
return 0;}
