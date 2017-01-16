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

void quick (int *data, int left, int right) {
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
		if (left < large)  quick(data, left, large);
		if (small < right) quick(data, small, right);
	}
}

// クイックソート
void quick_sort (int *data, int n) {
	puts("Quick");
	quick(data, 0, n-1);
}

// バブルソート
void bubble_sort (int *data, int n) {
	int i, j;
	puts("Bubble");
  for (i = 0; i < n-1; i++) {
    for (j = n-1; j > i; j--) {
      if ( compare (data[j], data[j-1]) ){
        swap (data, j, j-1);
      }
    }
  }
}

// 選択ソート
void selection_sort (int *data, int n) {
	int i, j;
	puts("Selection");
	for (i = 0; i < n-1; i++){
		int min = i;
		for (j = i + 1; j < n; j++) {
			if (compare (data[j], data[min])){
				min = j;
			}
		}
		swap (data, i, min);
	}
}

// 挿入ソート
void insert_sort (int *data, int n) {
	int i, j;
	puts("Insert");
  for (i = 1; i < n; i++){
		for (j = i; j > 0; j--){
			if (compare(data[j-1], data[j]) || data[j-1] == data[j]){
				break;
			}
			swap(data, j-1, j);
		}
	}
}

// ヒープソート
void heap_sort (int *data, int n) {
	int parent, childe;
	int i;

	puts("Heap");
	for(i=(n-1)/2; i>=0; i--){
		parent = i;
		childe = 2 * parent + 1;
		while(childe < n){
			if(childe < n-1 && compare(data[childe], data[childe + 1]))
				childe = childe +1;
			if(compare(data[parent], data[childe])) {
				swap(data, parent, childe);
				parent = childe; childe = 2 * parent + 1;
			} else
				break;
		}
	}

	for(i=n-1; i>0; i--) {
		swap(data, 0, i);
		parent = 0;
		childe = 1;
		while(childe < i) {
			if(childe  < i-1 && compare(data[childe], data[childe + 1]))
				childe = childe +1;
			if( compare(data[parent], data[childe])) {
				swap(data, parent, childe);
				parent = childe;
				childe = 2 * parent + 1;
			} else {
				break;
			}
		}
	}
}

void merge (int *data,int left,int mid, int right) {
	int *tmp;
	int i, j, k;

	tmp = (int*) malloc(sizeof(int)*(right-left+1));

	i = left;
	j = mid;
	k = 0;

	while ((i<mid) && (j<=right)) {
		if (compare(data[i], data[j])) tmp[k++] = data[i++];
		else                           tmp[k++] = data[j++];
	}

	while (i<mid)    tmp[k++] = data[i++];
	while (j<=right) tmp[k++] = data[j++];

	for(i=left; i<=right; i++) {
		data[i] = tmp[i-left];
	}

	free(tmp);
}

void mergesort (int *data, int left, int right) {
	int mid;

	if(left<right){
		mid = (right+left)/2;
		mergesort(data, left, mid);
		mergesort(data, mid+1, right);
		merge(data, left, mid+1, right);
	}
}

// マージソート
void merge_sort (int *data, int n) {
	puts("Marge");
	mergesort(data, 0, n-1);
}

// シェルソート
void shell_sort (int *data, int n) {
	int gap;
	int i, j, temp;

	puts("Shell");
	for (gap = n / 2; gap > 0; gap /= 2) {
		for (i = gap; i < n; i ++) {
			for (j = i - gap; j >= 0; j -= gap) {
				if (data[j] <= data[j + gap]) {
					break;
				} else {
					temp = data[j];
					data[j] = data[j + gap];
					data[j + gap] = temp;
				}
			}
		}
	}
}

unsigned long long int counterSwap;
unsigned long long int counterComp;

int main(void) {
	int *data, *data_back;
	int *data1, *data_back1, *data2, *data_back2;
	int n;
	int i, j;
	int com;
	void (* initData[3])(int *d, int x) = {initRandData, initAscendingData, initDescendingData };
	void (* sort[7])(int *d, int x) = {bubble_sort, selection_sort, insert_sort, shell_sort, quick_sort, merge_sort, heap_sort };

	printf("Data Size: ");
	scanf("%d", &n);
	printf("%d\n", n);

	data = (int*) malloc(sizeof(int) *n);
	data_back = (int*) malloc(sizeof(int) *n);
	data1 = (int*) malloc(sizeof(int) *n);
	data_back1 = (int*) malloc(sizeof(int) *n);
	data2 = (int*) malloc(sizeof(int) *n);
	data_back2 = (int*) malloc(sizeof(int) *n);

// データセットの初期化
	for (com = 1; com <= 3; com++){
		if (com==0) {
			for (i=0; i<n; i++) {
				scanf("%d", &data[i]);
			}
		} else {
			initData[com-1](data, n);
			if (com == 1) {
				initRandData(data1, n);
				initRandData(data2, n);
			}
		}

		switch (com) {
			case 1:
				puts("----------Random--------------"); break;
			case 2:
				puts("----------Ascending-----------"); break;
			case 3:
				puts("----------Descending----------"); break;
		}

	// データセットのリセット
		for (i = 0; i < n; i++){
			data_back[i] = data[i];
			if (com == 1) {
				data_back1[i] = data1[i];
				data_back2[i] = data2[i];
			}
		}

		#ifdef DEBUG
			printdata(data, n);
		#endif

	// 4
		for (i = 0; i < 7 ;i++) {
			for (j = 0; j < n; j++){
				data[j] = data_back[j];
				if (com == 1) {
					data1[j] = data_back1[j];
					data2[j] = data_back2[j];
				}
			}


			counterSwap = 0;
			counterComp = 0;

			sort[i](data, n);

			if (com == 1) {
				sort[i](data1, n);
				sort[i](data2, n);
				counterSwap = counterSwap / 3;
				counterComp = counterComp / 3;
			}

		#ifdef DEBUG
			printdata(data, n);
		#endif

			printf(" Comp: %lld\n", counterComp);
			printf(" Swap: %lld\n", counterSwap);
		}
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
