#include <stdio.h>
#include <stdlib.h>

int main(){
	int i;
	int *pArr;
	int n;

	scanf("%d", &n);
	do{
		pArr = (int *)malloc(sizeof(int)*n);
		for(i = 0; i < n; i++){
			pArr[i] = i;
		}
		for(i = 0; i < n; i++){
			printf("pArr[%d] = %d\n", i,*(pArr+i));
		}
		free(pArr);
		scanf("%d", &n);
	}while(-1 != n);
	return 0;
}