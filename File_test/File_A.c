#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){
	FILE *fp;
	int n[101] = { 0 };	// 入力ファイルの中身が1から100でなく0から100のため101の配列を用意
	int max_size = 0;
	int tmp;
	int i;

	if (argc == 2){
		if ((fp = fopen(argv[1], "r")) == NULL){
			printf("File open error!\n");
			exit(EXIT_FAILURE);
		}
		while (EOF != fscanf(fp, "%d\n", &tmp)){
			n[tmp]++;
			if(max_size < n[tmp]){
				max_size = n[tmp];
			}
		}
		printf("MAX : %d\n", max_size);
		for(i = 0 ; i < 100 ; ++i){
			if(max_size == n[i]){
				printf("%d\n", i);
			}
		}
		fclose(fp);
	}else{
		printf("No file specification.\n");
	}
	return 0;
}