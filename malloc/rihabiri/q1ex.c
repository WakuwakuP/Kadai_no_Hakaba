#include <stdio.h>
#include <stdlib.h>

void sortarr(char arr[],int size){
	int i,j;
	char tmp;

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

void rndset(char arr[],int size){
	int i;
	for(i=0;i<size;i++){
		arr[i] = GetRandom(65,90);
	}
	arr[size]='\0';
}

void printarr(char arr[],int size){
	int i;
	for(i = 0; i < size; i++){
		printf("arr[%d] = %c\n", i, arr[i]);
	}
	printf("\n");
}

int main(void){
	int i;
	int hsize;
	char *hairetsu;
	printf("配列数を入力:");
	scanf("%d",&hsize);
	hairetsu = (char *)malloc(sizeof(char)*(hsize + 1));
	rndset(hairetsu,hsize);
	printarr(hairetsu,hsize);
	sortarr(hairetsu,hsize);
	printarr(hairetsu,hsize);

	return 0;
}