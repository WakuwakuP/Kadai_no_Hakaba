#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void sort(int *data, int n);

int compare(int a, int b);

void swap(int *d, int a, int b);

void initRandData(int *d, int n);

void initAscendingData(int *d, int n);

void initDescendingData(int *d, int n);

void printdata(int *d, int n);


unsigned long counterSwap;
unsigned long counterComp;




void sort(int data[], int n)
{
  int i, j;
  for (i = 1; i < n; i++){
		for (j = i; j > 0; j--){
			if (compare(data[j-1], data[j]) || data[j-1] == data[j]){
				break;
			}
			swap(data, j-1, j);
		}
	}
}



int main(void)
{
	int *data;
	int n;
	int i;
	int com;
	void (* initData[3])(int *d, int x) = {initRandData,
	                                       initAscendingData,
	                                       initDescendingData };

	do {
		printf("データタイプ(1-3)\n");
		printf("ランダム:1 昇順:2 降順:3  ");
		scanf("%d", &com);
	} while (! (com==0||com==1||com==2||com==3));

	printf("データ数: ");
	scanf("%d", &n);

	data = (int*) malloc(sizeof(int) *n);
	if (com==0) {
		for (i=0; i<n; i++) {
			scanf("%d", &data[i]);
		}
	} else {
		initData[com-1](data, n);
	}

#ifdef DEBUG
	printdata(data, n);
#endif

	counterSwap = 0;
	counterComp = 0;

	sort(data, n);

#ifdef DEBUG
	printdata(data, n);
#endif

	printf(" 比較: %d 回\n", counterComp);
	printf(" 交換: %d 回\n", counterSwap);

	return 0;
}

int compare(int a, int b)
{
	counterComp++;
	return (a<b);
}

void swap(int *d, int a, int b)
{
	int tmp;

	counterSwap++;
	tmp = d[a];
	d[a] = d[b];
	d[b] = tmp;
}

void initRandData(int *d, int n)
{
	int i, s;
	srand(time(NULL));
	s=n*10;
	for(i=0; i<n; i++) d[i]=rand()%s;
}

void initAscendingData(int *d, int n)
{
	int i;
	for(i=0; i<n; i++)  d[i]=i;
}

void initDescendingData(int *d, int n)
{
	int i;
	for(i=0; i<n; i++)  d[i]=n-i-1;
}

void printdata(int *d, int n)
{
	int i;

	for (i=0; i<n; i++) printf("%d ", d[i]);
	printf("\n");
}
