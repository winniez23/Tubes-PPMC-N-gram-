#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"
#include "queue_masalah.h"
#define Nil NULL

ngram* OpenFile();

// List variabel
int PanjangList=0;
char *filename;
int n;
int RandWord;
ngram *NList;


int main(){
	int c, i, pil1;
	Queue Q;
	char* X;
	char pil;

	printf("----------MAIN MENU----------\n");
    printf("Program ini akan menerima sebuah input n dari pengguna yang\n");
    printf("harus bernilai 2 atau lebih agar tidak menghasilkan\n");
    printf("kalimat random. Kemudian, pengguna akan diminta memasukkan jumlah\n");
    printf("kata random yang ingin dicetak(haruslah bernilai 2000 atau lebih).\n");
    printf("Silakan mencoba~~\n");
    printf("Tekan huruf Y untuk memulai program, dan tekan huruf X untuk keluar.\n");
    scanf("%c", &pil);

    if (pil=='Y'||pil=='y')
    do
    {
        filename = malloc(sizeof(char));
        filename[0]='\0';
        printf("Masukkan nama file : ");
        scanf("%s", filename);

        printf("\nMasukkan nilai N untuk N gram : ");
        scanf("%d", &n);
        while (n < 2) //cek masukan nilai n
        {
            printf("Masukkan nilai N tidak boleh dibawah 2! Silahkan ulangi");
            scanf("%d", n);
        }

        printf("Berapa banyak kata random yang ingin dibentuk : ");
        scanf("%d", &RandWord); //RandWord == banyak kata


        createEmpty(&Q);

        // ini dihapus nanti
        //int* index_found_array;
        //index_found_array = (int*)malloc(100*sizeof(int));
        OpenFile(); // Pembentukan array ngram di main

        char* string_awal;
        char* key_current;
        string_awal = (char*) malloc (100*n*sizeof(char));
        X = (char*) malloc (100*sizeof(char));
        key_current = (char*) malloc (n*100*sizeof(char));
        strcpy(string_awal,NList[2].key);
        strcpy(key_current,string_awal);

        generate (key_current, &RandWord, &Q, NList, PanjangList);

        printf("...");
        printf("%s",string_awal);
        Print(&Q);
        printf("...");

        printf("\nApakah pengguna ingin memasukkan jumlah kata lagi?\n");
        printf("Tekan 1 untuk memasukkan kata lagi, 0 untuk kembali ke main menu.\n");
        scanf("%d", &pil1);
        if (pil1==1)
        do
        {
            createEmpty(&Q);

            // ini dihapus nanti
            //int* index_found_array;
            //index_found_array = (int*)malloc(100*sizeof(int));
            OpenFile(); // Pembentukan array ngram di main

            char* string_awal;
            char* key_current;
            string_awal = (char*) malloc (100*n*sizeof(char));
            X = (char*) malloc (100*sizeof(char));
            key_current = (char*) malloc (n*100*sizeof(char));
            strcpy(string_awal,NList[2].key);
            strcpy(key_current,string_awal);

            generate (key_current, &RandWord, &Q, NList, PanjangList);

            printf("...");
            printf("%s",string_awal);
            Print(&Q);
            printf("...");

        } while (pil1==1);
        //free(index_found_array);
        free(X);
        free(key_current);
        free(string_awal);

        free(NList);
    } while (pil=='Y'||pil=='y');
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
