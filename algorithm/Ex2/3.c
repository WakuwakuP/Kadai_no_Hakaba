#include <stdio.h>

double aveof(const int a[], int n);

int main() {
	int data[] = {10, 20, 30, 40, 23};
	int datasize = 5;
	printf("%f\n", aveof(data, datasize));
	return 0;
}

double aveof(const int a[], int n){
	int sum = 0;
	int i;
	for (i = 0; i < n; i++) {
		sum += a[i];
	}
	return (double)sum / n;
}
