/* EL2208 Praktikum Pemecahan Masalah dengan C 2019/2020
* MODUL 8 – TUGAS BESAR
* Kelompok : 6
* Hari dan Tanggal : Jumat, 17 April 2020
* Asisten (NIM) : Lionel Valdarant (18316020)
* Nama File : queue_masalah.c
* Deskripsi : implementasi fungsi ekstrenal untuk queue dan pemecahan masalah
*/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"
#include "queue_masalah.h"
#define Nil NULL

void createEmpty(Queue* Q);
node* Alokasi(char*);
void Push(Queue* Q, char*);
void Pop(Queue* Q, char*);
void Print(Queue*);

//n itu berapa banyak tabel gram yang dibentuk
void Search (char* key_current, gram tabel_gram[],int index_found_array[],int* count,int N) //untuk mencari berapa kali sebuah key muncul dalam tabel n-gram
{
	int i,j;
	i =0;
	j =0;
	*count = 0;
	printf("Masuk ke search\n");
	
	while(i<N){ 
		if(strcmp(tabel_gram[i].key,key_current)==0){ //kata pada current key akan dibandingkan dengan indeks di tabel n-gram
			index_found_array[j] = i; //jika sama maka count ditambah 1
			printf("nemu nih\n");
			j++;
		}
		i++;
	}
	*count = j-1;
}

void generate (char* key_current, int* banyak_kata, Queue* Q, gram tabel_gram[], int N){ //menghasilkan queue yang berisi kata2 yang telah digenerate berdasarkan tabel n-gram
	int index_found_array[10];
	int index_found;
	int banyak_kemunculan;
	int length;
	//Basis
	if (*banyak_kata==0){
		printf("n_gram berhasil di generate\n");
	}
	
	//Rekurens
	else
	{
		char* token[10]; //aray untuk memisahkan kata dalam key
		int i;
		int random;
		Search(key_current,tabel_gram,index_found_array,&banyak_kemunculan,N); //mencari key pada tabel n gram dan mengecek jumlah kemunculannya
		
		//klo banyak_kemunculan>1
		if(banyak_kemunculan>1) {
			i = 0;
			random = rand() %(banyak_kemunculan + 1 - 0) + 0;
			index_found = index_found_array[random];
		}
		else{ //jika kemunculan hanya 1
			index_found = index_found_array[0]; 
		}
		
		token[0] = strtok(key_current, " "); //karena key terdiri dari sejumlah n-kata, maka akan dipisah
		i =0;
		while (token[i] != NULL) //selama kalimat masih penuh
		{
			i =i+1;
			token[i] = strtok(NULL, " "); //maka kalimat akan terus dipisah dan distore di array token
			
		}
		length = i;
		Push(Q,tabel_gram[index_found].value); //masukkan value tersebut ke queue
		
		//pembuatan key_current baru
		strcpy(key_current, token[1]); 
		strcat(key_current, " ");
		
		for(i=2;i<length;i++){
			strcat(key_current, token[i]); 
			strcat(key_current, " ");
		}
		
		strcat(key_current, tabel_gram[index_found].value);
		//strcat(key_current, " ");
		(*banyak_kata)--;
		
		//rekursif
		generate (key_current,banyak_kata, Q,tabel_gram, N);
	}
}

node* Alokasi(char* X){
	node* P;
	P = (node*) malloc(sizeof(node));
	if(P==Nil){
		return Nil;
	}
	else{
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
		printf("%s",X);
	}
	
}

		
		
	
