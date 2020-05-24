#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node Node;
typedef struct table Table;

struct node{
    int data;
    Node * next;
};

struct table{
    Node ** list;
    int size;
};

int NextPrime(int n){
    while(1){
        if(n % 2 == 0){
            n++;
        }
        int flag = 0;
        for(int i = 3; i < sqrt(n); i++){
            if(n % i == 0){
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            return n;
        }
        n++;
    }
}

Table * CreateTable(int size){
    Table * t = (Table *)malloc(sizeof(Table));
    t->size = NextPrime(size);
    t->list = (Node **)malloc(sizeof(Node *) * t->size);
    for(int i = 0; i < t->size; i++){
        t->list[i] = (Node *)malloc(sizeof(Node));
        t->list[i]->next = NULL;
    }
    return t;
}

int Hash(int data, int size){
    return abs(data % size);
}

Node * Find(Table * t, int data){
    int index = Hash(data, t->size);
    Node * list = t->list[index]->next;
    Node * n = list;
    /// if it is not the end of the list and the node has not been found yet
    while(n != NULL && n->data != data){
        n = n->next;
    }
    return n;
}

void Insert(Table * t, int data){
    int index = Hash(data, t->size);
    Node * temp = (Node *)malloc(sizeof(Node));
    temp->data = data;
    temp->next = t->list[index]->next;
    t->list[index]->next = temp;
}

void Delete(Table * t, int data){
    int index = Hash(data, t->size);
    Node * l = t->list[index]->next;
    Node * temp = t->list[index];

    while(l != NULL && l->data != data){
        temp = t;
        l = l->next;
    }
    temp->next = l->next;
}


void Destroy(Table * t){
    for(int i = 0; i < t->size; i++){
        Node * list = t->list[i];
        Node * temp;

        while(list != NULL){
            temp = list->next;
            free(list);
            list = temp;
        }
    }
    free(t->list);
    free(t);
}
int main()
{
    int n;
    scanf("%d", &n);
    Table * t = CreateTable(n);
    int op;
    int data;

    while(1){
        printf("1. Insert\n");
        printf("2. Find\n");
        printf("3. Delete\n");
        printf("4. Destroy Table\n");

        scanf("%d", &op);

        switch(op){
            case 1:
                scanf("%d", &data);
                Insert(t, data);
                break;
            case 2:
                scanf("%d", &data);
                Insert(t, data);
                break;
            case 3:
                scanf("%d", &data);
                Delete(t, data);
                break;
            case 4:
                Destroy(t);
                break;
            case 5:
                exit(0);
        }
    }
    return 0;
}
