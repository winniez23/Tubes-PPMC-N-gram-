/* EL2208 Praktikum Pemecahan Masalah dengan C 2019/2020
* MODUL 9 – TUGAS BESAR
* Kelompok : 6
* Hari dan Tanggal : Kamis, 16 April 2020
* Asisten (NIM) : Lionel Valdarant (18316020)
* Nama File : input.c
* Deskripsi : menimbun isi tabel yang terbentuk
*/

#include "queue_masalah.h"
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//n itu berapa banyak tabel gram yang dibentuk



void generate (int* banyak_kata,int panjangList, Queue* Q, ngram* tabel_gram, int* start){ //menghasilkan queue yang berisi kata2 yang telah digenerate berdasarkan tabel n-gram

	//Basis
	int sth;
	if (*banyak_kata==0){
		if((*start)<panjangList){
			Push(Q,tabel_gram[(*start)].value); //masukkan value tersebut ke queue
			printf("%s ", tabel_gram[(*start)].value);
		}
		
		else{
			//printf("ini kawab i : %d",i);
			//Push(Q,tabel_gram[(*start) - panjangList-1].value); //masukkan value tersebut ke queue
			sth = (*start) - panjangList;
			printf("%s ", tabel_gram[sth].value);
		}
		printf("...\n");
	}
	//Rekurens
	else{
		
		if((*start)<panjangList){
			Push(Q,tabel_gram[(*start)].value); //masukkan value tersebut ke queue
			printf("%s ", tabel_gram[(*start)].value);
		}
		else if ((*start)>=panjangList){
			
			sth = (*start) - panjangList;
			printf("%s ", tabel_gram[sth].value);
			Push(Q,tabel_gram[sth].value); //masukkan value tersebut ke queue
		}
		(*banyak_kata)--;
		(*start)++;
		
		//rekursif
		
		generate (banyak_kata,panjangList, Q, tabel_gram,start);
	}
}

node* Alokasi(char* X){
	node* P;
	P = (node*) malloc(sizeof(node));
	if(P==Nil){
		return Nil;
	}
	else{
		P->valueq = (char*) malloc(100*sizeof(char));
		strcpy(P->valueq,X);
		P->next = Nil;
		return P;
	}
}

void createEmpty(Queue* Q){
	(*Q).head = Nil;
	(*Q).tail = Nil;
}

void Push (Queue* Q, char* X){
/*sudah ditangani jika stack kosong */
	node* P;
	P = Alokasi(X);
	if(P!=Nil){
		if((*Q).head==Nil){ //jika kosong
			(*Q).head = P;
			(*Q).tail = P;
		}
		else{
			((*Q).tail)->next = P;
			(*Q).tail = P;
		}
	}
}

//HATI-HATI
void Pop (Queue* Q, char* X){
/*sudah ditangani jika stack kosong*/
	node* P;
	if((*Q).head==Nil){
			printf("Tidak dapat melakukan pop\n");
	}
	else{
		strcpy(X ,((*Q).head)->valueq);
		P=(*Q).head;
		(*Q).head = P->next;
		if((*Q).head==Nil) // jika ketika di pop jadi kosong
			(*Q).tail = Nil;
		P->next = Nil;
		free(P);
	}
}

boolean isEmpty(Queue Q){
	if(Q.head==Nil){
		return true;
	}
	else {
		return false;
	}
}

void Print(Queue* Q){
	char X[100];
	while(!isEmpty(*Q)){
		Pop(Q,X);
		printf("%s ",X);
	}
	
}

		
		
	
