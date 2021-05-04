
#include <iostream>
# include <stdio.h>
# include <stdlib.h>

// Tek bağlantili liste dugum yapisi
struct node
{
    float info;
    struct node *next;
};

// NODEPTR : dugum isaretci tipi
typedef struct node *NODEPTR;


// Bellekten bir dugumluk yer alma
NODEPTR getNode()
{
    NODEPTR p=(NODEPTR) malloc(sizeof(struct node));
    return p;
}

// Bir dugumluk bellek alanini sisteme iade etme
void freeNode(NODEPTR p)
{
    free(p);
}

// Liste basina dugum ekleme
void push(NODEPTR *list, float k)
{
    NODEPTR p = getNode();    // Bellekten dugum al
    p->info = k;    // Dugumun veri alanini doldur
    p->next = *list; // Yeni dugumu liste basina bağla
    *list = p;    // Liste basini guncelle
}

// Liste basindan dugum cikarma
float pop(NODEPTR *list)
{
    if (*list != NULL)
    {
        NODEPTR p = *list;        // p : Silinecek dugum
        *list = (*list)->next;    // liste basini guncelle
        float k = p->info;        // dugumun icerigini kopyala
        freeNode(p);            // dugumu sil
        return k;                // icerigi geri dondur
    }
    else
        printf("Liste bos! Dugum silinemedi! \n");
    return 0;

}

// Araya dugum ekleme
void insertAfter(NODEPTR q, float k)
{
    if (q != NULL)
    {
        NODEPTR p = getNode();    // Eklenecek olan yeni dugum
        p->info = k;
        p->next = q->next;
        q->next = p;
    }
    else
        printf("Adres hatasi! Dugum eklenemedi! \n");
}

// Aradan dugum silme
float deleteAfter(NODEPTR q)
{
    if (q != NULL && q->next != NULL)
    {
        NODEPTR p = q->next;        // Silinecek düğüm
        float k = p->info;
        q->next = p->next;
        freeNode(p);
        return k;
    }
    else
        printf("Adres hatasi! Dugum silinemedi! \n");
    return 0;
}

// Tum listeyi ekrana yazdiran fonksiyon
void printList(NODEPTR list)
{
    while (list != NULL)
    {
        printf("%.1f - ", list->info);
        list = list->next;
    }
    // İslemlerin sonunda list isaretcisinin yeri degismez (adresi gonderilmedi).
}

//Listede x verisini içeren düğümü arar
//Eğer bu düğüm varsa düğümü, yoksa NULL döndürür.
NODEPTR searchNode(NODEPTR list, float x)
{
    NODEPTR p=list;
    while(p!=NULL && p->info !=x)
        p=p->next;
    return p;
  
}
//Bir listede her x düğümünün arkasına y düğümünü ekleyen
// ve eklenen düüğüm sayısını dödüren fonksiyonu yazınız.
int searchAndInsert(NODEPTR list, float x, float y)
{
    int sayac=0;
    NODEPTR p=list;
    
    while(p!=NULL)
    {
        
        if (p->info==x)
        {
            insertAfter(p,y);
            sayac++;
           p=p->next; // eğer x ile y eşit ise sonsuz döngğden kurtarır
        }
       
        p=p->next;
    }
    
    return sayac;
}


// listenin sıralı olup olmadığını kontrol eden fonksiyon

bool isSorted(NODEPTR list)
{
    NODEPTR p=list;
    bool kontrol=true;
    
    while(p!=NULL && p->next!=NULL && kontrol==true)
    {
         if(p->info>(p->next)->info)
             kontrol=false;
        else
            p=p->next;
    }
    return kontrol;
    
}

// Verilen bir listenin ters sıralı bir kopyasını olusturan
// ve yeni oluşan listenin liste başı işaretçisini geri döndüren fonksiyon

NODEPTR createRevList(NODEPTR list)
{
    NODEPTR newlist=NULL;
    NODEPTR p=list;
    
    while(p!=NULL)
    {
        push(&newlist, p->info);
        p=p->next;

    }
        
    return newlist;
}



int main()
{
    NODEPTR liste = NULL;    // Bos Liste
 
    push(&liste, 6);
    push(&liste, 3);
    push(&liste, 4);

    printf("Listenin ilk durumu : ");
    printList(liste);
    
    pop(&liste);
    pop(&liste);

    printf("Listenin ara durumu : ");
    printList(liste);

    push(&liste, 4);
    push(&liste, 2);
    push(&liste, 1);

    printf("Listenin son durumu : ");
    printList(liste);

   
    
    NODEPTR p = liste;
    p = p->next;
    insertAfter(p, 11);
    p = p->next;
    p = p->next;
    insertAfter(p, 17);
    p = p->next;
    p = p->next;
    insertAfter(p, 1);

    printf("Listenin guncel durumu : ");
    printList(liste);
    
      p = liste;
      deleteAfter(p);
      p = p->next;
      p = p->next;
      deleteAfter(p);
      p = p->next;
      p = p->next;
      deleteAfter(p);

      printf("Listenin en guncel durumu : ");
      printList(liste);
    
    NODEPTR q=searchNode(liste, 9);
    if (q==NULL)
        printf("düğüm yok!\n\n");
    else
        printf("düğüm var, %.1f", q->info);
    
    //Listeye 11 den sonra 12 ekleyen komutu yazalım
    int k= searchAndInsert(liste, 11,12);
    printList(liste);
     
//     Liste sıralı mı kontrol edelim.
    bool kont=isSorted(liste);
      if(kont)
          printf("liste sıralı\n");
     else
         printf("liste sıralı değil \n");
    
    NODEPTR tersList=NULL;
    tersList=createRevList(liste);
    printList(tersList);
    
    return 0;
}
