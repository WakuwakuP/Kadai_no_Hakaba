#include <stdio.h>
#include <stdlib.h>

int main(){
	int i;
	int *pInt;

	pInt = (int*)malloc(28);
	for(i = 0; i < 28/sizeof(int); i++){
		pInt[i] = 0;
	}
	printf("%d\n", 28/sizeof(int));
	for(i = 0; i < 28/sizeof(int); i++){
		printf("pInt[%d]=%d\n",  i,pInt[i]=0);
	}
	free(pInt);
	return 0;
}