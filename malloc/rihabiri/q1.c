#include <stdio.h>
#include <stdlib.h>

void sortarr(int arr[],int size){
	int i,j;
	int tmp;

	for (i=0; i<size-1; i++) {
		for (j=i+1; j<size; j++) {
			if (arr[i] > arr[j]) {
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}

int GetRandom(int min,int max){
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

void rndset(int arr[],int size){
	int i;
	for(i=0;i<size;i++){
		arr[i] = GetRandom(0,(int)(size*1.5));
	}
}

void printarr(int arr[],int size){
	int i;
	for(i=0;i<size;i++){
		printf("[%d]=%d\n",i,arr[i]);
	}
	printf("\n");
}

int main(void){
	int i;
	int hsize;
	int *hairetsu; //動的配列のためのポインタ

	printf("配列数を入力:");
	scanf("%d",&hsize);
	hairetsu = (int *)malloc(sizeof(int)*hsize);
	rndset(hairetsu,hsize);
	printarr(hairetsu,hsize);
	sortarr(hairetsu, hsize);
	printarr(hairetsu,hsize);
	return 0;
}