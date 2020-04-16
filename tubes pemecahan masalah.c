#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"
#define Nil NULL


typedef struct
{
	char key[100];
	char value[100];
}
gram;

typedef struct node{
	char valueq[100];
	struct node* next;
} node;

typedef struct {
	node* head;
	node* tail;
} Queue;

typedef struct {
	char huruf[100];
} kata;

void createEmpty(Queue* Q);
node* Alokasi(char[]);
void Push(Queue* Q, char[]);
void Pop(Queue* Q, char[]);
void Print(Queue*);

//n itu berapa banyak tabel gram yang dibentuk
void Search (char key_current[], gram tabel_gram[],int index_found_array[],int* count,int N){
	
	int i,j;
	i =0;
	j =0;
	*count = 0;
	printf("Masuk ke search\n");
	
	while(i<N){
		if(strcmp(tabel_gram[i].key,key_current)==0){
			index_found_array[j] = i;
			printf("nemu nih\n");
			j++;
		}
		i++;
	}
	*count = j-1;
	
	
}

void generate (char key_current[], int* banyak_kata, Queue* Q, gram tabel_gram[], int N){
	int index_found_array[10];
	int index_found;
	int banyak_kemunculan;
	int length;
	//Basis
	if (*banyak_kata==0){
		// gak ush diprint win, tapi kek kasih kata-kata udh berhasil di generate
		printf("n_gram berhasil di generate\n");
	}
	
	//Rekurens
	else
	{
		char* token[10];
		int i;
		Search(key_current,tabel_gram,index_found_array,&banyak_kemunculan,N); //
		
		//klo banyak_kemunculan>1
		if(banyak_kemunculan>1) {
			// randomize
			// ini belum win
			printf("random\n");
			
		}
		else{
			index_found = index_found_array[0];
		}
		
		token[0] = strtok(key_current, " ");

		i =0;
		while (token[i] != NULL)
		{
			i =i+1;
			token[i] = strtok(NULL, " ");
			
		}
		length = i;
		Push(Q,tabel_gram[index_found].value);
		
		//tolong dirapiin
		strcpy(key_current, token[1]);
		strcat(key_current, " ");
		
		for(i=2;i<length;i++){
			strcat(key_current, token[i]);
			strcat(key_current, " ");
		}
		
		strcat(key_current, tabel_gram[index_found].value);
		//strcat(key_current, " ");
		(*banyak_kata)--;
		generate (key_current,banyak_kata, Q,tabel_gram, N);
	}
}
/* ini mau dicoba2 aja
void handling_file(char file_name[100], n_gram tabel_gram[], int banyak_gram){
	FILE *file;
	kata daftar_kata[1000];
	char* token[100];
	char stream[100];
	
	file = fopen(filename,"r");
	if(file!=Nil){
		while(fscanf(file,stream)!=EOF){
			
			
		}
	}
}
*/


int main(){
	Queue Q;
	char X[100];
	createEmpty(&Q);
	int i,banyak_kata;
	// ini dihapus nanti
	int index_found_array[10];
	int count;
	
	
	gram tabel_gram[100];
	/*
	strcpy(tabel_gram[0].key,"Ships at ");
	strcpy(tabel_gram[0].value,"a ");
	strcpy(tabel_gram[1].key,"at a ");
	strcpy(tabel_gram[1].value,"distance ");
	strcpy(tabel_gram[2].key,"a distance ");
	strcpy(tabel_gram[2].value,"have ");
	strcpy(tabel_gram[3].key,"distance have ");
	strcpy(tabel_gram[3].value,"every ");
	strcpy(tabel_gram[4].key,"have every ");
	strcpy(tabel_gram[4].value,"man ");
	strcpy(tabel_gram[5].key,"every man ");
	strcpy(tabel_gram[5].value,"wish ");
	strcpy(tabel_gram[6].key,"man wish ");
	strcpy(tabel_gram[6].value,"on ");
	strcpy(tabel_gram[7].key,"wish on ");
	strcpy(tabel_gram[7].value,"board. ");
	strcpy(tabel_gram[8].key,"on board. ");
	strcpy(tabel_gram[8].value,"Ships ");
	strcpy(tabel_gram[9].key,"board. Ships ");
	strcpy(tabel_gram[9].value,"at ");
	*/
	
	
	char string_awal[] = "distance have ";
	char key_current[100];
	strcpy(key_current,string_awal);
	banyak_kata = 20-2;
	generate (key_current, &banyak_kata, &Q,tabel_gram,10);
	printf("%s",string_awal);
	Print(&Q);
	
}


node* Alokasi(char X[]){
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

void Push (Queue* Q, char X[]){
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
void Pop (Queue* Q, char X[]){
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

		
		
	
