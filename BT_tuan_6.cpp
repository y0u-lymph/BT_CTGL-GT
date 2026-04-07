#include <iostream>
using namespace std;
typedef struct File{
    char n[100];
    float size;
    int time;
}File;
struct node{
    File data;
    struct node* next;
}node;
struct list{
    struct node* first;
}list;
void add_node(struct node a, struct list A){
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
    i->next = &a;
    a.next = j;
    return;
}
float size_calc(struct list a){
    if(a.first == NULL) return 0;
    float S = a.first->data.size;
    struct node* p = a.first;
    while(p->next != NULL){
        p = p->next;
        S += p->data.size;
    }
    return S;
}
