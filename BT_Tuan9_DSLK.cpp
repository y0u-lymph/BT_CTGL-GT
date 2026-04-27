#include <iostream>
using namespace std;
struct Ngay{
	int ngay, thang, nam;
};
struct SinhVien{
	char maSV[9];
	char hoTen[50];
	bool gioiTinh;
	Ngay ngaySinh;
	char diaChi[100];
	char lop[12];
	char khoa[7];
};
struct Node{
	SinhVien data;
	Node *next;
};
struct List{
 	Node *first;
};
Node* themSV(SinhVien sv){
    Node* p = new Node;
    p->data = sv;
    p->next = NULL;
    return p;
}
void nhapSV(SinhVien &sv){
    cout << "Ma SV: "; cin >> sv.maSV;
    cout << "Ho ten: "; cin.getline(sv.hoTen, 50);
    cout << "Gioi tinh(0-Nam,1-Nu): "; cin >> sv.gioiTinh;
    cout << "Ngay sinh(d/m/y): ";
    cin >> sv.ngaySinh.ngay >> sv.ngaySinh.thang >> sv.ngaySinh.nam;
    cout << "Dia chi: "; cin.getline(sv.diaChi, 100);
    cout << "Lop: "; cin.getline(sv.lop, 12);
    cout << "Khoa: "; cin.getline(sv.khoa, 7);
}
void tracuuSV(SinhVien sv){
    cout << sv.maSV << " | " << sv.hoTen << " | "
         << sv.ngaySinh.ngay << "/" << sv.ngaySinh.thang << "/" << sv.ngaySinh.nam
         << endl;
}
int main(){
	struct List ListSV;
}
