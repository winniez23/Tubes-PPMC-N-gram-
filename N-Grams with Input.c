/* EL2208 Praktikum Pemecahan Masalah dengan C 2019/2020
* MODUL 9 – TUGAS BESAR
* Kelompok : 6
* Hari dan Tanggal : Kamis, 16 April 2020
* Asisten (NIM) : Lionel Valdarant (18316020)
* Nama File : N-Grams with Input.c
* Deskripsi : mengubah kata-kata pada file eksternal menjadi tabel n-gram beserta kode untuk menerima input user
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    char *key;
    char *value;
    int count;
}ngram;

// List Fungsi
void input_user();
ngram* OpenFile(ngram *NList, char *namafile, int n);

// List variabel
int PanjangList=0;
char *filename;
int n;
int RandWord;

void main(){
    input_user();
    ngram *NList = OpenFile(NList, filename, n); // Pembentukan array ngram di main
    printf("List Key -> Value\n");
    for(int i=0; i<PanjangList; i++){
        printf("[%d] %s -> %s\n", i+1, NList[i].key, NList[i].value);
    }
}

void input_user()
{
    int c;
    filename = malloc(sizeof(char));
    filename[0]='\0';
    printf("Masukkan nama file : ");
    for(int i=0;i<100 && (c=getchar())!='\n' && c!=EOF; i++){
        filename = realloc(filename,(i+2)*sizeof(char));
        filename[i] = (char)c;
        filename[i+1] = '\0';
    }

    printf("Masukkan nilai N untuk N gram : ");
    scanf("%d", &n);
    while (n < 2) //cek masukan nilai n
    {
        printf("Masukkan nilai N tidak boleh dibawah 2! Silahkan ulangi");
        scanf("%d", n);
    }
    printf("Berapa banyak kata random yang ingin dibentuk : ");
    scanf("%d", &RandWord);
    while (RandWord < 2000) //minimal mencetak dari 1 key saja
    {
        printf("Banyak kata random minimal 2000! Silahkan ulangi");
        scanf("%d", RandWord);
    }
}

ngram* OpenFile(ngram *NList, char *namaFile, int n){
    // Open File
    FILE *fp = fopen(namaFile,"r");
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
    while(fscanf(fp," %1023s", word) == 1){ // Pembacaaan kata satu per satu pada file
        NList = realloc(NList,(i+1)*sizeof(ngram)); // Alokasi memori variabel ngram
        int j=0;
        char tmp[1024];
        if(i==0){ // Pembentukan ngram pertama
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
    // Akhir kalimat pada file
    PanjangList = i;
    fclose(fp);
    return NList;
}
