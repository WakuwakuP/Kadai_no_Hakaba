#include <stdio.h>

typedef struct{
	int y;
	int m;
	int d;
} YMD;

int mdays[2][12] = {
	{31,28,31,30,31,30,31,31,30,31,30,31},
	{31,29,31,30,31,30,31,31,30,31,30,31}
};

int isleap (int year);
YMD after (YMD x, int n);

int main () {
	YMD date, date_next;
	int days;

	/* input */
	printf("年     : ");     scanf("%d", &date.y);
	printf("月     : ");     scanf("%d", &date.m);
	printf("日     : ");     scanf("%d", &date.d);
	printf("何日後 : ");   scanf("%d", &days);

	/* function */
	date_next = after(date, days);

	/* output */
	printf("西暦%4d年%2d月%2d日の%d日後は\n", date.y, date.m, date.d, days);
	printf("西暦%4d年%2d月%2d日です。\n", date_next.y, date_next.m, date_next.d);
	return 0;
}

int isleap (int year) {
	return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
}

YMD after (YMD x, int n) {
	YMD res;
	res = x;
	res.d = x.d + n;
	while(res.d > mdays[isleap(res.y)][res.m]){
		res.d -= mdays[isleap(res.y)][res.m];

		if (res.m >= 12) {
			++res.y;
			res.m = 1;
		} else {
			++res.m;
		}
	}
	return res;
}
