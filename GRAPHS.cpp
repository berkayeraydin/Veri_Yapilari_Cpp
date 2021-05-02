
#include <iostream>
#include <stdlib.h>
#define SIZE 5
#define WSIZE 6
#define MEMBER 1
#define NOMEMBER 0

//Yonlendirilmis agirlik matrisi
int weight[WSIZE][WSIZE]={{0,10,3,0,0},
    {0,0,1,2,0},
    {0,4,0,8,2},
    {0,0,0,0,7},
    {0,0,0,9,0}};


short int adj[SIZE][SIZE]={{0,0,1,1,0},
    {1,0,1,0,1},
    {0,0,0,1,1},
    {1,0,0,1,0},
    {0,0,0,0,1}};
//iki matrisin boolean  çarpımı
//C=A.B
void matrisCarp(short int a[][SIZE], short int b[][SIZE], short int c[][SIZE])
{//mavi kırmızı yeşil için ders notlarına bakınız
    int yesil ,mavi ,kirmizi,toplam;
    for(yesil=0; yesil<SIZE;yesil++)
    {
        for(mavi=0; mavi<SIZE; mavi++)
            {
                toplam=0;
            for(kirmizi=0; kirmizi<SIZE; kirmizi++)
                toplam= toplam ||(a[yesil][kirmizi]&& b[kirmizi][mavi]);
            c[yesil][mavi]=toplam;
        }}}
// verilen graf için yol matrisini (path) bulalım.
// Bunun için adj matrisini kullanalım.
void yolMatrisi(short int adj[][SIZE], short int path[][SIZE])
{
    int satir, sutun, kuvvet;
    
    short int sonAdj[SIZE][SIZE];
    short int carpimSonucu[SIZE][SIZE];
    //Baslangıç için gerekli taşıyıcı matrislerin ayarlanması
    for(satir=0; satir<SIZE; satir++)
    {
        for(sutun=0; sutun<SIZE;sutun++)
        {
            sonAdj[satir][sutun]=adj[satir][sutun];
            carpimSonucu[satir][sutun] =adj[satir][sutun];
            }
        }
    for(kuvvet=0; kuvvet<SIZE; kuvvet++)
    {
        matrisCarp(sonAdj, adj, carpimSonucu);
        //yol matrisi ile boolean toplama
        for(satir=0; satir<SIZE; satir++)
              for(sutun=0; sutun<SIZE;sutun++)
                  path[satir][sutun]=path[satir][sutun]||carpimSonucu[satir][sutun];
        
        for(satir=0; satir<SIZE; satir++)
           for(sutun=0; sutun<SIZE;sutun++)
               sonAdj[satir][sutun]=carpimSonucu[satir][sutun];
        
    }
    
}

void matrisYazdır(short int a[][SIZE])
{ int satir, sutun;
    for(satir=0; satir<SIZE; satir++)
    {
        for(sutun=0; sutun<SIZE;sutun++)
            printf("%d",a[satir][sutun]);
        printf("\n");
        
        }}

void Dijkstra(int weight[][WSIZE], int baslangic)
{
    int yol[WSIZE], perm[WSIZE];
    // Ziyaret edilmemiş butun dugumlere sonsuz ata
    // ayrıca ziyaret edilmedikleri gosterir NOMEMBER değeri atıyoruz
    
    for(int i=0; i<WSIZE;i++)
    yol[i]=INT_MAX, perm[i]=NOMEMBER;
    // Başalngıç düğümünün uzaklığı 0
    yol[baslangic]=0;
    
    for(int dolas=0; dolas<WSIZE-1; dolas++)
    {
        int min=INT_MAX, min_index;// Hiç uğranmamış düğümlere değer ata
        
        //Iclerinden en kucugunu sec (Extract min)
        for(int j=0; j<WSIZE; j++)
            if(perm[j]==NOMEMBER && yol[j]<=min)
                min=yol[j], min_index=j;
        
        int u=min_index;
        
        perm[u]=MEMBER;
        
        //Relax işlemi
        for(int v=0; v <WSIZE; v++)
            
            if(!perm[v]&& weight[u][v] && yol[u]!=INT_MAX &&
               yol[u]+weight[u][v]<yol[v])//Geçilmiş düğümler
                yol[v]=yol[u]+weight[u][v]; //İçinde daha kısa yol bul
    }
                
  for (int i = 0; i < WSIZE; i++)
  printf("baslangic dugumu %d bitis %d en kisa yol  %d\n", baslangic,  i, yol[i]); //Dugumleri ve uzakliklari yazdir.
        
        
    }


int main()
{
    short int yol[SIZE][SIZE];
    yolMatrisi(adj, yol);
    matrisYazdır(yol);
    
    Dijkstra(weight, 0);
    return 0;
}
