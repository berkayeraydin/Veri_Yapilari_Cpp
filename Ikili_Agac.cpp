#include <stdlib.h>
#include <stdio.h>

// Bir ikili agac dugum yapisi
struct btnode
{
    int info;
    struct btnode *left;
    struct btnode *right;
    struct btnode *parent;    // ‹st dugum adres
};

// Dugum isaretci tipinin tanimlanmasi
typedef struct btnode *BTNODEPTR;

// Bir dugummluk bellek alani alma
BTNODEPTR getNode()
{
    BTNODEPTR p = (BTNODEPTR)malloc(sizeof(struct btnode));
    return p;
}

// Bir dugumu ana bellege iade etme
void freeNode(BTNODEPTR p)
{
    free(p);
}

// info alani r olan bir ikili agac kok dugumu olusturma
BTNODEPTR createRoot(int r)
{
    BTNODEPTR root = getNode();
    root->info = r;
    root->left = NULL;
    root->right = NULL;
    root->parent = NULL;
    return root;
}


BTNODEPTR addChildNode(BTNODEPTR parent, int k, bool isLeft)
{
    bool kosul1 = (parent != NULL);
    bool kosul2 = (isLeft == true && parent->left == NULL);
    bool kosul3 = (isLeft == false && parent->right == NULL);

    if (kosul1 && (kosul2 || kosul3))
    {
        BTNODEPTR c = getNode();    // Yeni dugumu olustur
        c->info = k;
        c->left = NULL;
        c->right = NULL;
        if (isLeft == true)
            parent->left = c;
        else
            parent->right = c;
    
        c->parent = parent;      // cocuk dugum ust dugum baglantisi
        return c;
    }
    else
    {
        printf("Cocuk dugum ekleme hatasi!\n");
        return NULL;
    }
}


// ikili agaci preorder duzende tarayan ve
// dugumleri ekrana yazdiran fonksiyon
void preorder(BTNODEPTR root)
{
    if (root != NULL)
    {
        printf("%d ", root->info);
        preorder(root->left);
        preorder(root->right);
    }
}


// ikili agacı inorder duzende tarayan ve
// dugumleri ekrana yazd˝ran fonksiyon
void inorder(BTNODEPTR root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->info);
        inorder(root->right);
    }
}

// ikili agaci postorder duzende tarayan ve
// dugumleri ekrana yazdiran fonksiyon
void postorder(BTNODEPTR root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->info);
    }
}


// Ana Program
int main()
{
    BTNODEPTR r = createRoot(20);
    BTNODEPTR p1 = addChildNode(r, 15, true);    // r'nin soluna 15
    BTNODEPTR p2 = addChildNode(r, 32, false);    // r'nin sagina 32
    addChildNode(p1, 6, true);
    addChildNode(p1, 11, false);
    p2 = addChildNode(p2, 25, true);
    BTNODEPTR p3 = addChildNode(p2, 22, true);
    p3 = addChildNode(p2, 30, false);


    printf(" PRE-ORDER tarama :");
    preorder(r);
    printf("\n IN-ORDER tarama :");
    inorder(r);
    printf("\n POST-ORDER tarama :");
    postorder(r);

  

    

    return 0;
}









