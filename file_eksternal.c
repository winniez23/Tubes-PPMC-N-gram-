/* EL2208 Praktikum Pemecahan Masalah dengan C 2019/2020
* MODUL 9 – TUGAS BESAR
* Kelompok : 6
* Hari dan Tanggal : Kamis, 16 April 2020
* Asisten (NIM) : Lionel Valdarant (18316020)
* Nama File : file_eksternal.c
* Deskripsi : File pembacaan file eksternal dan pembentukan ngram
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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
int p = 0;
int countWord = 0;
char ch;

void Search (char* key_current, ngram* tabel_gram,int* index_found_array,int* count,int N) //untuk mencari berapa kali sebuah key muncul dalam tabel n-gram
{
	int i,j;
	i =0;
	j =0;
	*count = 0;

	while(i<N){
		if(strcmp(tabel_gram[i].key,key_current)==0){ //kata pada current key akan dibandingkan dengan indeks di tabel n-gram
			index_found_array[j] = i; //jika sama maka count ditambah 1
			j++;
		}
		i++;
	}
	*count = j-1;
	if (*count > 100)
	{
		*count = 100;
	}
}

void main(){
	int index_found;
	int index_found_array[100];
	int index=0;
    input_user();
    int banyak_kemunculan;
    ngram *NList = OpenFile(NList, filename, n); // Pembentukan array ngram di main
    printf("List Key -> Value\n");

	//seharusnya PanjangList
    for(int i=0; i<PanjangList; i++){
        printf("[%d] %s -> %s\n", i+1, NList[i].key, NList[i].value);
    }
    FILE *fp = fopen(filename,"r");
    ch = fgetc(fp);
    while(ch != EOF)
    {
        if(ch == ' ' || ch == '\n')
        {
            countWord += 1;
        }
        else
        {
            countWord += 0;
        }
        ch = fgetc(fp);
    }
    while (p < RandWord - n)
    {
        if (p < countWord - 1)
        {
            if (p == 0)
            {
                printf("...");
                printf("%s", NList[index+2].key); //aku ambil dari key[3]
                printf("%s ", NList[index+2].value);
                Search(NList[index+2].key, NList, index_found_array, &banyak_kemunculan, n);
                if(banyak_kemunculan>1) {
					int random = rand() %(banyak_kemunculan + 1 - 0) + 0;
					index_found = index_found_array[random];
					index = index_found;
				}
				else{ //jika kemunculan hanya 1
					index_found = index_found_array[0];
					index = index_found;
				}
				printf("%s ", NList[index].value);
				index +=1;
				p += 2;
            }
            else if (p == (RandWord - n)-1)
            {
                printf("%s ", NList[index+2].value);
                printf("...");
                index +=1;
				p += 1;
            }
            else
            {
                printf("%s ", NList[index+2].value);
                Search(NList[index+2].key, NList, index_found_array, &banyak_kemunculan, n);
                if(banyak_kemunculan>1) {
					int random = rand() %(banyak_kemunculan + 1 - 0) + 0;
					index_found = index_found_array[random];
					index = index_found;
				}
				else{ //jika kemunculan hanya 1
					index_found = index_found_array[0];
					index = index_found;
				}
				printf("%s ", NList[index].value);
                index +=2;
				p += 1;
            }
        }
        else
        {
            if (p == (RandWord - n)-1)
            {
                printf("%s ", NList[index%(countWord - 1)].value);
                printf("...");
                p += 1;
            }
            else
            {
                printf("%s ", NList[index%(countWord - 1)].value);
                p += 1;
                index +=1;
            }
        }
    }
    free(NList);
    free(filename);
    return;
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
        printf("Masukkan nilai N tidak boleh dibawah 2! Silahkan ulangi\n");
        scanf("%d", n);
    }
    printf("Berapa banyak kata random yang ingin dibentuk : ");
    scanf("%d", &RandWord);
	/*
    while (RandWord < 2000) //minimal mencetak dari 1 key saja
    {
        printf("Banyak kata random minimal 2000! Silahkan ulangi");
        scanf("%d", RandWord);
    }
	*/
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
	char tmp[1024];
    while(fscanf(fp," %1023s", word) == 1){ // Pembacaaan kata satu per satu pada file
        NList = realloc(NList,(i+1)*sizeof(ngram)); // Alokasi memori variabel ngram
        int j=0;

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
