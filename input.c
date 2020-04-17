/* EL2208 Praktikum Pemecahan Masalah dengan C 2019/2020
* MODUL 8 – TUGAS BESAR
* Kelompok : 6
* Hari dan Tanggal : Kamis, 16 April 2020
* Asisten (NIM) : Lionel Valdarant (18316020)
* Nama File : input.c
* Deskripsi : berisi kode untuk menerima input user
*/

#include <stdio.h>
#include <stdlib.h>

void input_user()
{
    printf("Masukkan nama file : ");
    scanf("%s", filename);
    printf("Masukkan nilai N untuk N gram : ");
    scanf("%d", n);
    while (n < 2) //cek masukan nilai n
    {
        printf("Masukkan nilai N tidak boleh dibawah 2! Silahkan ulangi!\n");
        scanf("%d", n);
    }
    printf("Berapa banyak kata random yang ingin dibentuk : ");
    scanf("%d", RandWord);
}
