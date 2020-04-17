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
    /* while (RandWord < 2000) //minimal mencetak dari 1 key saja
    {
        printf("Banyak kata random minimal 2000! Silahkan ulangi");
        scanf("%d", RandWord);
    }*/
}
