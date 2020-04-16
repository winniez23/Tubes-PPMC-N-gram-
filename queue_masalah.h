#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"
#define Nil NULL

typedef struct //struct untuk tabel n-gram
{
	char* key;
	char* value;
}
gram;

typedef struct node{ //struct untuk menyimpan beberapa value dalam satu key
	char* valueq;
	struct node* next;
} node;

typedef struct { //struct untuk queue
	node* head;
	node* tail;
} Queue;

typedef struct { //struct untuk kata
	char huruf[100];
} kata;

void createEmpty(Queue* Q);
node* Alokasi(char*);
void Push(Queue* Q, char*);
void Pop(Queue* Q, char*);
void Print(Queue*);

//n itu berapa banyak tabel gram yang dibentuk
void Search (char* key_current, gram tabel_gram[],int index_found_array[],int* count,int N); //untuk mencari berapa kali sebuah key muncul dalam tabel n-gram

void generate (char* key_current, int* banyak_kata, Queue* Q, gram tabel_gram[], int N); //menghasilkan queue yang berisi kata2 yang telah digenerate berdasarkan tabel n-gram
