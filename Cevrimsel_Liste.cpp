# include <stdio.h>
# include <stdlib.h>
# include <iostream>

using namespace std;

// Tek bağlantılı (çevrimsel) liste düğüm yapısı
struct node
{
    float info;
    struct node *next;
};

// CCNODEPTR : düğüme işaretçi tipi
typedef struct node *CNODEPTR;


// Bellekten bir düğümlük yer alma
CNODEPTR getNode()
{
    CNODEPTR p=(CNODEPTR) malloc(sizeof(struct node));
    return p;
}

// Bir düğümlük bellek alanını sisteme iade etme
void freeNode(CNODEPTR p)
{
    free(p);
}

// Liste başına düğüm ekleme
void push(CNODEPTR *list, float k)
{
    CNODEPTR p = getNode();    // Bellekten düğüm al
    p->info = k;    // Düğümün veri alanını doldur
    
    if (*list == NULL) // Liste boş ise
    {
        p->next = p;
        *list = p;
    }
    else
    {
        p->next = (*list)->next;
        (*list)->next = p;
    }
}

// Liste başından düğüm çıkarma
float pop(CNODEPTR *list)
{
    if (*list != NULL)
    {
        CNODEPTR p = (*list)->next;    // p: silinecek düğüm
        if (p==*list)    // Listede tek düğüm varsa
        {
            *list = NULL;
        }
        else
        {
            (*list)->next = p->next;
        }

        float k = p->info;    // düğümün içeriğini al
        freeNode(p);    // düğümü sil
        return k;
    }
    else
    {   printf("Liste bos! Dugum silinemedi! \n");
        return 0;}

}

// Tüm listeyi ekrana yazdıran fonksiyon
void printList(CNODEPTR list)
{
    if (list != NULL)
    {
        CNODEPTR p = list;
        do
        {
            p = p->next;
            printf("%.1f - ", p->info);

        } while (p != list);
    }
    else
        printf("\n BOS Liste ! \n");
}

// Araya düğüm ekleme
void insertAfter(CNODEPTR q, float k)
{
    if (q != NULL)
    {
        CNODEPTR p = getNode();    // Eklenecek olan yeni düğüm
        p->info = k;
        p->next = q->next;
        q->next = p;
    }
    else
        printf("Adres hatasi! Dugum eklenemedi! \n");
}




// ANA PROGRAM
int main()
{
    CNODEPTR liste = NULL;    // Boş liste yarat

    // Listenin oluşturulması
    push(&liste, 38);
    push(&liste, 33);
    push(&liste, 27);
    push(&liste, 21);
    push(&liste, 19);
    push(&liste, 16);
    push(&liste, 11);
    push(&liste, 5);

    printList(liste);
    printf("\n");    // Alt satır
    
    pop(&liste);

    printList(liste);
      printf("\n");    // Alt satır
   
    return 0;
}

