#include <stdlib.h>
#include <stdio.h>

// l˝ d¸¸m yap˝s˝
struct dnode
{
    int info;
    struct dnode *left;
    struct dnode *right;
};

typedef struct dnode *DNODEPTR;


// bellekten düğüm alma
DNODEPTR getNode()
{
    DNODEPTR p = (DNODEPTR)malloc(sizeof(struct dnode));
    return p;
}

// Belleğe düğümü iade et
void freeNode(DNODEPTR p)
{
    free(p);
}

// Liste basi isaretcici list olarak verilen cift baglı listede
//  p dugumunun yanina icerigi k olan bir dugum ekle
// right parametresi true ise yeni dugum  saga false ise sola eklenir.
void insertNode(DNODEPTR *list, DNODEPTR p, int k, bool right)
{
    if (*list == NULL)    // Liste bo˛ ise !
    {
        DNODEPTR yeni = getNode();
        yeni->info = k;
        yeni->left = NULL;
        yeni->right = NULL;
        *list = yeni;
    }
    else  // Liste bos degilse
    {
        if (p != NULL)
        {
            DNODEPTR yeni = getNode();
            yeni->info = k;
            
            if (!right)    // p dugumunun soluna
            {
                DNODEPTR sol = p->left;
                if (sol == NULL) // Yeni dugum liste basina
                {
                    yeni->left = NULL;
                    yeni->right = p;
                    *list = yeni;
                    p->left = yeni;
                }
                else
                {
                    yeni->left = sol;
                    yeni->right = p;
                    sol->right = yeni;
                    p->left = yeni;
                }
            }
            else  // p dugumunun sagina
            {
                DNODEPTR sag = p->right;
                if (sag == NULL)  // Yeni dugum liste sonuna ekleniyor
                {
                    yeni->right = NULL;
                    yeni->left = p;
                    p->right = yeni;
                }
                else
                {
                    yeni->left = p;
                    yeni->right = sag;
                    p->right = yeni;
                    sag->left = yeni;
                }
            }
        }
        else
            printf("Adres hatasi! Dugum ekleme yapilamadi!\n");
    }
}

// Liste basina isaretcisi list olan cift baglivbir listeden
// verilen bir p dugumunu silen fonksiyon
int deleteNode(DNODEPTR *list, DNODEPTR p)
{
    if (p != NULL)
    {
        DNODEPTR sol = p->left;
        DNODEPTR sag = p->right;

        if (sol != NULL && sag != NULL)
        {
            sol->right = sag;
            sag->left = sol;
        }

        else if (sol == NULL && sag != NULL)
        {
            sag->left = NULL;
            *list = sag;
        }

        else if (sol != NULL && sag == NULL)
        {
            sol->right = NULL;
        }

        else if (sol == NULL && sag == NULL)
        {
            *list = NULL;
        }

        // Dugum silme asamasi
        int k = p->info;
        freeNode(p);
        printf("\nListeden %d dugumu silindi", k);
        return k;
    }
    else
        return 0;
    
}



// Listeyi p d¸¸m¸nden itibaren ekrana yazd˝ran program
// isLeft true ise sola dogru; false ise saa dogru ilerlenir.
void printList(DNODEPTR p, bool isLeft)
{
    while (p != NULL)
    {
        printf("%d  ", p->info);
        if (isLeft)
            p = p->left;
        else
            p = p->right;
    }
}

// Liste basi isaretcisi list olan cift baglantili bir listede k degerini tasiyan
// ilk dugumm¸ arayan ve buldugunda dugum adresini geri donduren
// fonksiyon. Dugum bulunamazsa NULL degeri geri dondurulur.
DNODEPTR searchNode(DNODEPTR list, int k)
{
    DNODEPTR p = list;
    while (p != NULL && p->info != k)
        p = p->right;
    return p;
}

// list1 icideki ilk k dugumunun hemen sagina list2 listesini
// ekleyen fonksiyon. Eger list1 icinde k dugum¸ bulunamazsa
// list2 listesi, list1'in en sonuna eklenmelidir.
void mergeList(DNODEPTR list1, DNODEPTR list2, int k)
{
    if (list1 != NULL && list2 != NULL)
    {
        DNODEPTR k_adr = searchNode(list1, k);
        // 1. durum (k dugumu bulunursa)
        if (k_adr != NULL)
        {
            DNODEPTR kr = k_adr->right;
            // list2'nin son dugumunun bulunmasi
            DNODEPTR p = list2;
            while (p->right != NULL)
                p = p->right;

            // Baglanti asamasi
            k_adr->right = list2;
            list2->left = k_adr;

            p->right = kr;
            if (kr!=NULL)
                kr->left = p;
        }
        // 2. durum (k dugumu yoksa)
        else
        {
            // list1'in son dugumunun bulunmasi
            DNODEPTR p = list1;
            while (p->right != NULL)
                p = p->right;

            p->right = list2;
            list2->left = p;
        }
    }
}






int main()
{
    DNODEPTR liste = NULL;

    insertNode(&liste, NULL, 5, true); //5
    DNODEPTR p = liste;// p=5
    insertNode(&liste, p, 7, true);//5-7
    insertNode(&liste, p, 12, false); //12-5-7
    p = p->right;// p=7
    insertNode(&liste, p, 8, true); // 12-5-7-8
    insertNode(&liste, p, 14, false);//12-5-14-7-8

    printf("Listenin durumu : ");
    printList(liste, false);  // liste basindan yazdir

    deleteNode(&liste, p);// 7 sil
    deleteNode(&liste, liste);// liste basini sil

    printf("\nListenin son durumu : ");
    printList(liste, false);  // liste basindan itibaren saga dogru yazdir

    p = liste->right->right; //p05

    printf("\nListenin son durumu (ters sirada) : ");
    printList(p, true);  // liste sonundan itibaren sola dogru yazdirma

    deleteNode(&liste, liste);
    deleteNode(&liste, liste);
    deleteNode(&liste, liste);

    if (liste == NULL)
        printf("\nListe su an bos !");
    else
        printf("\nListede eleman var !");

    
    DNODEPTR list1 = NULL;
    insertNode(&list1, NULL, 5, true);
    p = list1;
    insertNode(&list1, p, 7, true);
    insertNode(&list1, p, 12, false);
    p = p->right;
    insertNode(&list1, p, 8, true);
    insertNode(&list1, p, 7, false);

    printf("\nListe-1 : ");
    printList(list1, false);  // list
    
    DNODEPTR list2 = NULL;
    insertNode(&list2, NULL, 44, true);
    p = list2;
    insertNode(&list2, p, 33, true);
    insertNode(&list2, p, 55, false);
    
    printf("\nListe-2 : ");
    printList(list2, false);  // list
    
    mergeList(list1, list2, 7);

    printf("\nListe-1'in son durumu : ");
    printList(list1, false);  // list
    return 0;

}
