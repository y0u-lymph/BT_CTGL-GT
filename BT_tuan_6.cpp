#include <iostream>
using namespace std;
typedef struct File{
    char n[100];//ten file
    float size;//kich thuoc file (MB)
    int time;//don vi thay the thoi gian
}File;
struct node//Khai bao node
{
    File data;
    struct node* next;
}node;
struct list//Khai bao danh sach
{
    struct node* first;
}list;
void add_node(struct node a, struct list A)//Them va sap xep tang dan
{
    if(A.first->data.time >= a.data.time){
        a.next = A.first;
        A.first = &a;
        return;
    }
    struct node* i = A.first;
    struct node* j = A.first;
    while(j->next != NULL){
        if(j->data.time >= a.data.time)
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
    if(j->data.time < a.data.time){
        a.next = NULL;
        j->next = &a;
        return;
    }
    i->next = &a;
    a.next = j;
    return;
}
float size_calc(struct list a)//Tinh kich thuoc tep
{
    if(a.first == NULL) return 0;
    float S = a.first->data.size;
    struct node* p = a.first;
    while(p->next != NULL){
        p = p->next;
        S += p->data.size;
    }
    return S;
}
void delete_tail(struct list A)//loai bo node cuoi
{
    struct node* a = new struct node;
    struct node* a = A.first;
    struct node* b = A.first;
    while(a->next != NULL){
        a = a->next;
    }
    while(b->next != a){
        b = b->next;
    }
    b->next = NULL;
    delete a;
}
void sao_luu_32GB(struct list A)//loai bo node lon hon de list size <= 32GB
{
    while(size_calc(A) > 32000)
        delete_tail(A);
}
