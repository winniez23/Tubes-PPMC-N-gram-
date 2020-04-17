/* EL2208 Praktikum Pemecahan Masalah dengan C 2019/2020
* MODUL 9 – TUGAS BESAR
* Kelompok : 6
* Hari dan Tanggal : Kamis, 16 April 2020
* Asisten (NIM) : Lionel Valdarant (18316020)
* Nama File : input.c
* Deskripsi : Berisi main program dan pemecahan masalah
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"
#include "queue_masalah.h"
#define Nil NULL

ngram* OpenFile();

// List variabel
long int PanjangList=0;
char *filename;
int n;
int RandWord;
ngram *NList;
int main(){
	int c,pil1;
	Queue Q;
	int i;
	int banyak_kata;
	int start;
	char pil='Y';

	while(pil=='Y' || pil=='y'){
        printf("----------MAIN MENU----------\n");
        printf("Program ini akan menerima sebuah input n dari pengguna yang\n");
        printf("harus bernilai 2 atau lebih agar tidak menghasilkan\n");
        printf("kalimat random. Kemudian, pengguna akan diminta memasukkan jumlah\n");
        printf("kata random yang ingin dicetak(haruslah bernilai 2000 atau lebih).\n");
        printf("Silakan mencoba~~\n");
        printf("Tekan huruf Y untuk memulai program, dan tekan huruf X untuk keluar.\n");
        scanf("%c", &pil);

        filename = (char*)malloc(100*sizeof(char));
        printf("Masukkan nama file : ");
        scanf("%s", filename);

        printf("Masukkan nilai N untuk N gram : ");
        scanf("%d", &n);
        while (n < 2) //cek masukan nilai n
        {
            printf("Masukkan nilai N tidak boleh dibawah 2! Silahkan ulangi");
            scanf("%d", n);
        }
        
        pil1 = 1;
        while(pil1 == 1){
			printf("Berapa banyak kata random yang ingin dibentuk : ");
			scanf("%d", &RandWord); //RandWord == banyak kata
            OpenFile();
            if(NList!=NULL){
                createEmpty(&Q);
                //start = rand() %(PanjangList + 1 - 0) + 0;
                start = 3;
                printf("... %s",NList[start].key);
                banyak_kata = RandWord-n;
                generate (&banyak_kata,PanjangList,&Q,NList, &start);
                //Print(&Q);
                printf("\nApakah pengguna ingin memasukkan jumlah kata lagi?\n");
                printf("Tekan 1 untuk memasukkan kata lagi, 0 untuk kembali ke main menu.\n");
                scanf("%d", &pil1);
            }
        }
        free(NList);
        printf("Tekan huruf Y untuk memulai program, dan tekan huruf X untuk keluar.\n");
        scanf("%trash", &pil);
        scanf("%c", &pil);
        system("cls");
	}

	return 0;
}

ngram* OpenFile(){
    // Open File
    FILE *fp = fopen(filename,"r");
    if(!fp){ //Bila file tidak terbuka
        printf("File tidak terbuka\n");
        fclose(fp);
        return NList;
    }

    rewind(fp); // Meletekkan cursor di awal file
    char word[1024]; // Variabel karakter yang menyimpan pembacaan baris pada csv

    /* Percobaan 1 */
    NList = malloc(sizeof(ngram)); // Pembentukan variabel ngram

    char *words;
    for(int i=0; i<n; i++){
        fscanf(fp," %1023s", word);
        if(i==0){
            words = strdup(word);
            strcat(words," ");
        }
        else{
            strcat(words,word);
            strcat(words," ");
        }
    }
    int i=0;
	char tmp[1024];
    while(fscanf(fp," %1023s", word) == 1){ // Pembacaaan kata satu per satu pada file
        NList = realloc(NList,(i+1)*sizeof(ngram)); // Alokasi memori variabel ngram
        int j=0;

        if(i==0){ // Pembentukan ngram pertama
            memset(tmp,'\0',sizeof(tmp));
            strcpy(tmp, words);
            NList[i].key = strdup(tmp);
            NList[i].value = strdup(word);
            i++;
        }
        else{
            strcpy(tmp, NList[i-1].key);
            strcat(tmp, NList[i-1].value);

            words = strchr(tmp, ' ');
            if(words != NULL){
                words = words + 1;
            }
            strcpy(tmp, words);
            strcat(tmp, " ");
            NList[i].key = strdup(tmp);
            NList[i].value = strdup(word);
            i++;
        }
    }

	int j;
	for(j=i;j<i+n;j++){
		char* token;
		char* temp_awal;

		NList = realloc(NList,(j+1)*sizeof(ngram));
		strcpy(tmp, NList[j-1].key);
        strcat(tmp, NList[j-1].value);
		words = strchr(tmp, ' ');
        if(words != NULL){
            words = words + 1;
        }
        strcpy(tmp, words);
        strcat(tmp, " ");
        NList[j].key = strdup(tmp);

		temp_awal = strdup(NList[j-i].key);
		token = strtok(temp_awal," ");
		NList[j].value = strdup(token);
	}

    // Akhir kalimat pada file
    PanjangList = j;
    fclose(fp);
    return NList;
}
