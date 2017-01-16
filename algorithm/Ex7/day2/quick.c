#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
/* Quick Sort */

int compare (int a, int b);

void swap (int *d, int a, int b);

void initRandData (int *d, int n);

void initAscendingData (int *d, int n);

void initDescendingData (int *d, int n);

void printdata (int *d, int n);

void quicksort_front (int *data, int left, int right) {
	int pivot;
	int small, large;

	if(left < right) {
		small = left;
		large = right;
		pivot = data[(left+right)/2];
		while(small<=large){
			while(compare(data[small], pivot)) small++;
			while(compare(pivot, data[large])) large--;
			if(small<=large){
				swap(data, small++, large--);
			}
		}
		if (left < large)  quicksort_front(data, left, large);
		if (small < right) quicksort_front(data, small, right);
	}
}

void quicksort_back (int *data, int left, int right) {
	int pivot;
	int small, large;

	if(left < right) {
		small = left;
		large = right;
		pivot = data[right];
		while(small<=large){
			while(compare(data[small], pivot)) small++;
			while(compare(pivot, data[large])) large--;
			if(small<=large){
				swap(data, small++, large--);
			}
		}
		if (left < large)  quicksort_back(data, left, large);
		if (small < right) quicksort_back(data, small, right);
	}
}

void quicksort_center (int *data, int left, int right) {
	int pivot;
	int small, large;

	if(left < right) {
		small = left;
		large = right;
		pivot = data[(left+right)/2];
		while(small<=large){
			while(compare(data[small], pivot)) small++;
			while(compare(pivot, data[large])) large--;
			if(small<=large){
				swap(data, small++, large--);
			}
		}
		if (left < large)  quicksort_center(data, left, large);
		if (small < right) quicksort_center(data, small, right);
	}
}

void quicksort_median (int *data, int left, int right) {
	int pivot;
	int small, large;

	if(left < right) {
		int mid[3] = {data[left], data[right], data[(left + right) / 2]};
		int i, j;
	  for (i = 0; i < 2; i++) {
	    for (j = 2; j > i; j--) {
	      if (mid[j] < mid[j - 1]){
	        int tmp = mid[j];
					mid[j] = mid[j - 1];
					mid[j - 1] = tmp;
	      }
	    }
	  }
		small = left;
		large = right;
		pivot = mid[1];
		while(small<=large){
			while(compare(data[small], pivot)) small++;
			while(compare(pivot, data[large])) large--;
			if(small<=large){
				swap(data, small++, large--);
			}
		}
		if (left < large)  quicksort_median(data, left, large);
		if (small < right) quicksort_median(data, small, right);
	}
}

void sort_front (int *data, int n) {
	puts("Front");
	quicksort_front(data, 0, n-1);
}

void sort_back (int *data, int n) {
	puts("Back");
	quicksort_back(data, 0, n-1);
}

void sort_center (int *data, int n) {
	puts("Center");
	quicksort_center(data, 0, n-1);
}

void sort_median (int *data, int n) {
	puts("Median");
	quicksort_median(data, 0, n-1);
}

unsigned long counterSwap;
unsigned long counterComp;

int main(void) {
	int *data, *data_back;
	int n;
	int i, j;
	int com;
	void (* initData[3])(int *d, int x) = {initRandData, initAscendingData, initDescendingData };
	void (* sort[4])(int *d, int x) = {sort_front, sort_back, sort_center, sort_median };

	do {
		printf("Data Type(1-3)\n");
		printf("Random:1 Ascending:2 Descending:3\n: ");
		scanf("%d", &com);
		printf("%d\n", com);
	} while (! (com==0||com==1||com==2||com==3));

	printf("Data Size: ");
	scanf("%d", &n);
	printf("%d\n", n);

	data = (int*) malloc(sizeof(int) *n);
	data_back = (int*) malloc(sizeof(int) *n);

	if (com==0) {
		for (i=0; i<n; i++) {
			scanf("%d", &data[i]);
		}
	} else {
		initData[com-1](data, n);
	}

	for (i = 0; i < n; i++){
		data_back[i] = data[i];
	}

	#ifdef DEBUG
		printdata(data, n);
	#endif

	for (i = 0; i < 4 ;i++) {
		for (j = 0; j < n; j++){
			data[j] = data_back[j];
		}


		counterSwap = 0;
		counterComp = 0;

		sort[i](data, n);

	#ifdef DEBUG
		printdata(data, n);
	#endif

		printf(" Comp: %d\n", counterComp);
		printf(" Swap: %d\n", counterSwap);
	}
	return 0;
}

int compare(int a, int b) {
	counterComp++;
	return (a<b);
}

void swap(int *d, int a, int b) {
	int tmp;

	counterSwap++;
	tmp = d[a];
	d[a] = d[b];
	d[b] = tmp;
}

void initRandData(int *d, int n) {
	int i, s;
	srand(time(NULL));
	s=n*10;
	for(i=0; i<n; i++) d[i]=rand()%s;
}

void initAscendingData(int *d, int n) {
	int i;
	for(i=0; i<n; i++)  d[i]=i;
}

void initDescendingData(int *d, int n) {
	int i;
	for(i=0; i<n; i++)  d[i]=n-i-1;
}

void printdata(int *d, int n) {
	int i;

	for (i=0; i<n; i++) printf("%d ", d[i]);
	printf("\n");
}
