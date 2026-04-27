#include <iostream>
using namespace std;
struct Ngay{
	int ngay, thang, nam;
};
struct SinhVien{
	int maSV;
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
void xuatSV(SinhVien sv){
    cout << sv.maSV << " | " << sv.hoTen << " | " << (sv.gioiTinh? "Nu" : "Nam") << " | "
         << sv.ngaySinh.ngay << "/" << sv.ngaySinh.thang << "/" << sv.ngaySinh.nam
         <<sv.diaChi << " | " << sv.lop << " | " << sv.khoa
         << endl;
}
void add_node(struct Node a, struct List A)
{
    if(A.first->data.maSV >= a.data.maSV){
        a.next = A.first;
        A.first = &a;
        return;
    }
    struct Node* i = A.first;
    struct Node* j = A.first;
    while(j->next != NULL){
        if(j->data.maSV >= a.data.maSV)
            break;
        j = j->next;
    }
    if(j == A.first){
        A.first->next = &a;
        return;
    }
    while (i->next != j){
        i = i->next;
    }
    if(j->data.maSV < a.data.maSV){
        a.next = NULL;
        j->next = &a;
        return;
    }
    i->next = &a;
    a.next = j;
    return;
}
bool sameDate(Ngay a, Ngay b) {
    return (a.ngay == b.ngay && a.thang == b.thang && a.nam == b.nam);
}
void timCungNgaySinh(List ListSV, SinhVien sv){
    bool found = false;
    for (Node* i = ListSV.first; i != NULL; i = i->next){
        if (sameDate(i->data.ngaySinh, sv.ngaySinh)){
            xuatSV(i->data);
            found = true;
        }
    }
    if(!found) cout << "Khong tim thay sinh vien cung ngay sinh.\n";
}
void deleteNode(int maSV, List &ListSV){
    if(ListSV.first == NULL) return;
    if(ListSV.first->data.maSV == maSV){
        Node* temp = ListSV.first;
        ListSV.first = ListSV.first->next;
        delete temp;
        return;
    }
    Node* prev = ListSV.first;
    Node* curr = ListSV.first->next;
    while(curr != NULL){
        if(curr->data.maSV == maSV){
            prev->next = curr->next;
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    cout << "Khong tim thay sinh vien co ma SV: " << maSV << endl;
}
void xoaCungNgaySinh(List &ListSV){
    bool found = false;
    for (Node* i = ListSV.first; i != NULL;){
        for (Node* j = i->next; j != NULL; j = j->next){
            if (sameDate(i->data.ngaySinh, j->data.ngaySinh)){
                deleteNode(j->data.maSV, ListSV);
                found = true;
            }
        }
        if(found){
            Node* temp = i;
            i = i->next;
            deleteNode(temp->data.maSV, ListSV);
            found = false;
        }
        else i = i->next;
    }
    cout << "Da xoa cac sinh vien cung ngay sinh.\n";
}
int main(){
	struct List ListSV[100];
}
