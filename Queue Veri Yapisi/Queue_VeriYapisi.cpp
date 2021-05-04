#include "stdlib.h"
#include "stdio.h"

#define SIZE 5

// Kuyruk Veri Yapisi
struct queue
{
	double items[SIZE];
	int front;
	int rear;
};

// Kuyrugun bo� olup olmadigini test eden fonksiyon
bool isEmpty(struct queue *q)
{
	if (q->front == q->rear)
		return true;
	else
		return false;
}

// Kuyruga x elemanini ekleyen fonksiyon
void insert(struct queue *q, double x)
{
	if (((q->rear) + 1)%SIZE == q->front)	// Son hucreye eleman eklenmemeli!
	{
		printf("Kuyruk DOLU! %.1f elemani eklenemedi! \n",x);
	}
	else
	{
		q->rear = (q->rear + 1)%SIZE;	// Cevrimsel kuyruk : mod�ler artim
		q->items[q->rear] = x;
		//printf("%.1f elemani kuyruga eklendi! \n",x);
	}
}

// Kuyruktan eleman �ikaran fonksiyon
double remove(struct queue *q)
{
	if (!isEmpty(q))
	{
		q->front = (q->front + 1)%SIZE;	 // �evrimsel kuyruk : mod�ler artim
		double d = q->items[q->front];
		//printf("%.1f elemani kuyruktan cikarildi! \n", d);
		return d;
	}
	else
	{
		printf("Kuyruk BOS! remove islemi yapilamadi! \n");
	}
}

// Kuyrugu ekrana yazdiran fonksiyon.
// Islem sonucunda kuyruk bosalir.
void printQueue(struct queue *q)
{
	while (!isEmpty(q))
	{
		printf("%.1f  ", remove(q));
	}
}

// Kuyrugu ekrana yazdiran fonksiyon.
// Islem sonucunda kuyruk korunur (yedek kuyruk kullanimi ile).
void printQueue2(struct queue *q)
{
	struct queue yedek;
	yedek.front = SIZE - 1;
	yedek.rear = SIZE - 1;

	while (!isEmpty(q))
	{
		double eleman = remove(q);	// �ek
		printf("%.1f  ", eleman);	// Yazdir
		insert(&yedek, eleman);		// Yedekle
	}

	// Orjinal kuyrugu yeniden olusturma
	while (!isEmpty(&yedek))
		insert(q, remove(&yedek));
}

// Kuyrugu ekrana yazdiran fonksiyon.
// Islem sonucunda kuyruk korunur (parametre olarak adres degil, deger g�nderiliyor).
void printQueue3(struct queue q)
{
	while (!isEmpty(&q))
	{
		printf("%.1f  ", remove(&q));
	}
}

// q kuyru�undaki en b�y�k elemani ve bu elemanin kuyruktaki sirasini geri donduren fonksiyon
double findBiggest(struct queue q, int *yer)
{
	if (!isEmpty(&q))	// Kuyruk bos de�ilse
	{
		double eb = remove(&q);	// Kuyrugun ilk elemanini en b�y�k kabul et
		*yer = 1;
		int i = 1;
		while (!isEmpty(&q))
		{
			double x = remove(&q);
			i++;			// Kuyruktan �ekilen eleman sayiyi 1 arttir.
			if (x > eb)
			{
				eb = x;
				*yer = i;
			}
		}
		return eb;
	}
	else
		printf("Kuyruk bos! En buyuk eleman bulunamadi!\n");
}

// Bir kuyrugun en b�y�k elemanin kuyrugun en basina tasiyan fonksiyon
// �NEMLI NOT : en b�y�k sayidan sadece bir tane oldugu kabul ediliyor
void bringBiggestToFront(struct queue *q)
{
	if (!isEmpty(q))
	{
		int yer = -1;
		double eb = findBiggest(*q, &yer);

		struct queue yedek;
		yedek.front = SIZE - 1;
		yedek.rear = SIZE - 1;

		while (!isEmpty(q))
		{
			double x = remove(q);
			if (x != eb)		// en b�y�k disindaki tum elemanlari yedekle
				insert(&yedek, x);
		}

		insert(q, eb);	// Bos olan orjinal kuyruga en b�y�k sayiyi ekleyelim.

		// Yedekten orjinal kuyru�a kopyala
		while (!isEmpty(&yedek))
			insert(q, remove(&yedek));
	}
}

void main()
{
	struct queue q;
	q.front = SIZE - 1;
	q.rear = SIZE - 1;

	double d = remove(&q); // Hata mesaji

	insert(&q, 1.2);
	insert(&q, 22.5);
	insert(&q, 63.7);
	insert(&q, 11.1);
	insert(&q, 11.9);		// Bu eleman eklenemez ! kuyruk dolu.

	d = remove(&q);
	printf("Cekilen eleman = %.1f \n", d);

	//Kuyrugun ekrana yazdirilmas�
	printf("Kuyrugun son durumu : ");
	printQueue3(q);
	printf("\n");	// Alt satira ge�
	printQueue3(q);

	insert(&q, 22.1);	// Yeni eleman ekledik
	printf("\n Kuyrugun guncel durumu : ");
	printQueue3(q);

	int konum = -1;
	double en_buyuk = findBiggest(q, &konum);
	printf("\n Kuyrugun en buyuk elemani %.1f olup kuyruktaki sirasi %d dir", en_buyuk, konum);

	// En b�y�k elemani en basa alma 
	bringBiggestToFront(&q);
	printf("\n Kuyrugun en guncel durumu : ");
	printQueue3(q);

}
























