//
//  main.cpp
//  isaretci
//

// stdio kullanmadan yazım:

//#include <iostream>

//int main(int argc, const char * argv[]) {
    // insert code here...
   // std::cout << "Hello, World!\n";
    //return 0;
//}
#include "stdio.h"


// Degisken adresi uzerinde artim yapan fonksiyon
void n_artp(int *x, int n)
{
    printf("Fonksiyon calisti\n");
    *x = *x + n;
    printf("a=%d \n", *x);
}


// Sonucu geri donduren fonksiyon
int n_artd(int x, int n)
{
    x = x + n;
    return x;
}


int main()
{
    // Tanimlamalar
    int a = 5;
    int c = 88;
    int *b;        // tamsayi turunde isaretci
    double d=3.14159;
    int dizi[100];

   
    a = n_artd(a, 7); //a degiskeninş kullanarak
    
    n_artp(&a, 7);// a degiskenin adresini isaretciye at ve isaretci icerigini 7 artir
    b = &c;        // b isaretcisi, d degiskeninin adresine isaret ediyor
    *b = 10;    // b adresinin icerisine 10 ata
    c = 45;
    n_artp(b, 7);// b isaretcisinin icerigini 7 artir
    
    printf("a = %d, b = %d, c = %d", a, *b, c);

    //char x;
   // scanf_s("%c", &x);
    return 0;
}

