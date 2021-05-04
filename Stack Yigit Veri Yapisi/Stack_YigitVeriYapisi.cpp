#include "stdlib.h"
#include "stdio.h"

#define SIZE 3
// Yigit yapi modeli
struct stack
{
    float items[SIZE];
    int top;
    
};
// Yigitin bos olup olmadigini geri donduren temel fonksiyon
bool isEmpty(struct stack *s)
{
    if (s->top == -1)
        return true;
    else
        return false;
}
// Yigittan eleman ceken temel fonksiyon

float pop(struct stack *s)
{
    if (!isEmpty(s))  // yigit bos degilse
    {
        double x = s->items[s->top]; // geri dondurelecek deger
        (s->top)--;    // yigitin tepe degerini bir azalt
        return x;
    
        // return s->items[s->top--];    // yukar˝daki 3 sat˝r yerine sadece bu sat˝r da yaz˝labilir
    
    }
    else
    {
       printf("Yigit bos! Eleman cekme islemi (pop) yapilamadi!\n");
       return 0;
    }
    
}

// Yigita eleman iten (ekleyen) temel fonksiyon
void push(struct stack *s, double x)
{
    if (s->top < SIZE - 1)    //Yigitta bos yer var
    {
        (s->top)++;    // Yigitin tepe degerini bir arttir
        s->items[s->top] = x;
    
        // s->items[++s->top] = x;  // yukaridaki 2 satir yerine sadece bu satir da yazilabilir
    
    }
    else
    {
        printf("Yigit tam dolu! Ekleme (push) islemi yapilamadi!\n");
    }
}

void PrintStack(struct stack *s)
{
    while (!isEmpty(s))
        printf("%2.1f  ", pop(s));
}


// ANA PROGRAM
int main()
{
    double d;

    struct stack y;
    y.top = -1;    // Bos yigit

    push(&y, 1);
    push(&y, 2);
     push(&y, 2.7777);
   
    PrintStack(&y);
    d = pop(&y);
    printf("Yigittan cekilen eleman = %.2f\n", d);
    d = pop(&y);
    return 0;
}





