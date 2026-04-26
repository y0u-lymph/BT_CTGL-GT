#include <iostream>
using namespace std;
struct Ngay{
	int ngay, thang, nam;
};
struct SinhVien{
	char maSV[9];
	char hoTen[50];
	int gioiTinh;
	Ngay ngaySinh;
	char diaChi[100];
	char lop[12];
	char khoa[7];
};
struct Node{
	SinhVien data;
	Node *link;
};
struct List{
 	Node *first;
	Node *last;
};
int main{
  
}
