/* EL2208 Praktikum Pemecahan Masalah dengan C 2019/2020
* MODUL 8 – TUGAS BESAR
* Kelompok : 6
* Hari dan Tanggal : Kamis, 16 April 2020
* Asisten (NIM) : Lionel Valdarant (18316020)
* Nama File : input.c
* Deskripsi : berisi library untuk queue
*/

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
ngram;

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

void generate (int* banyak_kata,int panjangList,  Queue* Q, ngram* tabel_gram, int* start); //menghasilkan queue yang berisi kata2 yang telah digenerate berdasarkan tabel n-gram
