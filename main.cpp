#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


typedef struct veri
{
    int numara;
    char isim[10];
} kayitlar;


kayitlar liste[125];


int HashingBolenKalan(int anahtarDeger)
{
    return anahtarDeger%125;
}


int ekleBolenKalan (kayitlar data)
{
    if(liste[HashingBolenKalan(data.numara)].numara == -1)
    {
        liste[HashingBolenKalan(data.numara)] = data;
        return 1;
    }
    else
    {
        int donusSayisi =0;
        int indis = HashingBolenKalan(data.numara);

        while(liste[indis].numara != data.numara && liste[indis].numara!=-1)
        {
            indis ++;
            if(indis>=125)
            {
                if(donusSayisi>=1)
                {
                    printf("hashtable dolu");
                    return -1;
                }
                indis = indis %125;
                donusSayisi++;
            }
        }

        liste[indis]=data;
    }
}


int araBolenkalan(int aranan)
{

    if(liste[HashingBolenKalan(aranan)].numara == aranan)
    {
        printf("Kisi Bulundu : %d. Sirada. ", HashingBolenKalan(aranan));
    }
    else
    {
        int listeTaramaSayisi =0;
        int indis = HashingBolenKalan(aranan);
        while(liste[indis].numara != aranan)
        {
            indis ++;

            if(indis>=125)
            {
                if(listeTaramaSayisi>=1)
                {
                    printf("Kayit Bulunamadi.");
                    return -1;
                }
                indis = indis %125;
                listeTaramaSayisi++;
            }

        }

        printf("Kisi Bulundu : %d. Sirada. ", HashingBolenKalan(indis));

    }
}


int yazDosyaBolenkalan()
{
    FILE * bolenkalandosya;
    bolenkalandosya = fopen("bolenkalandosya.txt", "w+");

    for(int i = 0; i<125; i++)
    {
        fprintf(bolenkalandosya,"[%d] [ NUMARA:%d ÝSÝM:", i, liste[i].numara);
        fputs(liste[i].isim,bolenkalandosya);
        fprintf(bolenkalandosya," ]\n");
    }
}


int main()
{
    int sinir;
    for(int i = 0; i<125; i++)
    {
        liste[i].numara = -1;
    }
    kayitlar data;


    FILE * okulineerdosya;

    char okunanSatir[100];
    if ((okulineerdosya = fopen("lineerdosya.txt", "r"))==NULL)
    {
        printf("dosya acilamadi!\n");
        exit(1);
    }

    char * satir;

    satir = fgets(okunanSatir,100,okulineerdosya);

    while (satir != NULL)
    {

        char *ayiklanmisNo, *ayiklanmisIsim;
        int ayiklanmisNoInt;

        ayiklanmisNo = strtok(okunanSatir, " ");
        sscanf(ayiklanmisNo,"%d",&ayiklanmisNoInt);

        ayiklanmisIsim = strtok(NULL, "\n");

        data.numara=ayiklanmisNoInt;
        strcpy(data.isim,ayiklanmisIsim);

        satir = fgets(okunanSatir,100,okulineerdosya);

        ekleBolenKalan(data);
    }

    yazDosyaBolenkalan();


    int arananNo;

    time_t baslangic, son;

    printf("Aranacak kisinin numarasini giriniz : ");
    scanf("%d",&arananNo);
    float onceki = time(&baslangic);
    araBolenkalan(arananNo);
    float sonraki = time(&son);
    printf("\n\n");
    printf("Aranan kisiye Bolen-Kalan ile ulasma suresi : %f", sonraki - onceki );
    printf("\n");
}

