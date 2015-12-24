#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){
	FILE *fp;
	int n[10] = { 0 };
	double max, min, ave;
	double tmp;
	int i = 0, count = 0;

	/*ファイル指定忘れ判定*/
	if (argc == 2){
		/*Fileの読み込みとエラー判定*/
		if ((fp = fopen(argv[1], "rb")) == NULL){
			printf("File open error!\n");
			exit(EXIT_FAILURE);
		}

		/*Fileの読み込み, MAX判定, MINI判定, AVERAGE判定用総和, loop回数のカウント*/
		while (0 != fread(&tmp,sizeof(double), 1, fp)){
			if(i == 0){
				max = tmp;
				min = tmp;
				ave = 0;
			}else{
				if(max < tmp){
					max = tmp;
				}
				if(min > tmp){
					min = tmp;
				}
			}
			ave += tmp;
			if((int)(tmp*10) == 10){
				n[9]++;
			}else{
				n[(int)(tmp*10)]++;
			}
			count++;
			i++;
		}
		fclose(fp);
		printf("AVE : %f\nMAX : %f\nMIN : %f\n\nFrequency distribution\n", ave / count, max, min);
		for(i= 0;i< 10; ++i){
			printf("%.1f ~< %.1f : %d\n", i * 0.1, (i + 1) * 0.1, n[i]);
		}
	}else{
		printf("No file specification.\n");
	}
	return 0;
}