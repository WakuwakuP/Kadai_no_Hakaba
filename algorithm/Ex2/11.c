#include <stdio.h>

int mdays[2][12] = {
	{31,28,31,30,31,30,31,31,30,31,30,31},
	{31,29,31,30,31,30,31,31,30,31,30,31}
};

int isleap(int year);
int dayofyear(int y, int m, int d);


int main(void) {
	int year, month, day;
	int retry;

	do {
		/* 入力 */
		printf("year  : ");     scanf("%d", &year);
		printf("month : ");     scanf("%d", &month);
		printf("day   : ");     scanf("%d", &day);

		/* 出力 */
		printf("年内で%d日目です。\n", dayofyear(year, month, day));
		printf("もう一度しますか (1…yes/0…no) :");
		scanf("%d", &retry);
	} while (retry == 1);
	return 0;
}

int isleap(int year){
	return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

int dayofyear(int y, int m, int d){
	while (--m > 0) {
		d += mdays[isleap(y)][m-1];
	}
	return d;
}
