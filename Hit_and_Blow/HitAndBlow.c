#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int Retry(void);
void input_str(char *in, int size);
void Random_HB (int reset, int *rnum);
void make4number (int *rnum);
int checknumber (char innum[]);
void judgeHB (int rnum[], char innum[], int *hit, int *blow);
void printHB (int numhit, int numbrrow);


int main(){
	int i;
	int play;
	int anser[4];
	char input[6];
	int hit = 0, blow = 0;

	do{
		srand ((unsigned) time (NULL));

		printf("\n------------- Hit and Blow -------------\n\n");

		make4number(&anser[0]);

		for(play = 0 ; play < 10 ; ++play){
			int Flag = 0;

			printf("%d", play + 1);
			switch(play){
				case 0:
					printf("st "); break;
				case 1:
				case 2:
					printf("nd "); break;
				default:
					printf("th ");
			}
			printf("try.\n");

			do{
				printf("Number:");
				input_str(&input[0], sizeof(input));
				if(0 == checknumber(input)){
					Flag = 1;
				}else if (1 == checknumber(input)){
					printf("Error : number of digits is not correct.\n");
				}else if(2 == checknumber(input)){
					printf("Error: contains non-numeric.\n");
				}else if (3 == checknumber(input)){
					printf("Error: contains the same number.\n");
				}
			}while (Flag == 0);
			judgeHB(anser, input, &hit, &blow);
			if(4 == hit){
				printf("congratulations!\nIt is a success in the %d", play);
				switch(play){
					case 1:
						printf("st."); break;
					case 2:
					case 3:
						printf("nd."); break;
					default:
						printf("th.");
				}
				break;
			}else{
				printHB(hit, blow);
			}
			hit = 0;
			blow = 0;
		}
		if (play == 10){
			printf("That's too bad.\n");
		for(i = 0 ; i < 4 ; ++i){
			printf("%d", anser[i]);
		}
		}
		puts ("");
	}while(0 ==Retry());
	return 0;
}

/*	*	*	*	*	*	*	*	*	*	*
*	リトライの判定用関数				*
*	続ける場合 = 0	|| 終わる場合 = 1	*
*	*	*	*	*	*	*	*	*	*	*/

int Retry(){
	char repeater[4];
	while(1){
		printf("Retry Now? [yes/no] :");
		input_str(&repeater[0], sizeof(repeater));
		if ('y' == repeater[0] || 'Y' == repeater[0]){
			return 0;
		}
		if ('n' == repeater[0] || 'N' == repeater[0]){
			return 1;
		}
		printf("Input error. ");
	}
}

/* 文字列の入力用関数 */
void input_str(char *in, int size){
	int i = 0, n;
	//size -= 1;
	char in_tmp;
	while ((in_tmp = getchar()) != '\n'){
		n = i;
		if(in_tmp == '\b' && 0 < i){
			if(i >= size){
				n = size;
			}else{
				*(in + n) = '\0';
			}
			i--;
		}else{
			if(i >= size){
				n = size;
			}else{
				*(in + n) = in_tmp;
			}
			i++;
		}
	}
	if(i > size){	n = size;	}
	*(in + n + 1) = '\0';
}

/* 被らない4つの整数(0~9)をランダムに生成する */
void Random_HB (int reset, int* rnum) {
	int i, flag;
	if (0 == reset) {
		reset = 0;
		*(rnum + reset) = rand () % 10;
	} else {
		do {
			flag = 0;
			*(rnum + reset) = rand () % 10;
			for (i = 0; i < reset; ++i) {
				if (*(rnum + reset) == *(rnum + i)) {
					flag = 1;
				}
			}
		} while (1 == flag);
	}
}

/* 答えの生成用関数 */
void make4number (int *rnum) {
	int i;
	for (i = 0; i < 4; ++i) {
		Random_HB (i, rnum);
	}
}

/* 入力のフォーマットチェック関数 */
int checknumber (char innum[]) {
	int i;
	if (4 != strlen (innum)) {
		return 1;
	}
	for(i = 0; i < 4; ++i){
		if ('0' > innum[i] || '9' < innum[i]) {
			return 2;
		}
	}
	for(i = 0; i < 3; ++i){
		int j;
		for(j = i; j < 3; ++j){
			if(innum[i] == innum[j + 1]){
				return 3;
			}
		}
	}
	return 0;
}

void judgeHB (int rnum[], char innum[], int *hit, int *blow) {
	int i, j;
	for(i = 0; i < 4; ++i){
		for(j = 0; j < 4; ++j){
			if(rnum[i] == innum[j] - '0'){
				if(i == j){
					*hit += 1;
				}else{
					*blow += 1;
				}
			}
		}
	}
}

void printHB (int numhit, int numbrrow) {
	printf("HIT\t: %d\nBLOW\t: %d\n\n", numhit, numbrrow);
}