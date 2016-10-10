#include <stdio.h>

int med3(int num1, int num2, int num3);

int med3(int num1, int num2, int num3) {
	/* 三つの引数の値をを比較して中央値を返す */
	if (num1 >= num2)
		if (num2 >= num3)
			return num2;
		else if (num1 <= num3)
			return num1;
		else
			return num3;
	else if (num1 > num3)
		return num1;
	else if (num2 > num3)
		return num3;
	else
		return num2;
}

int main(void) {
	int data[13][3] = {
		{3,2,1},
		{3,2,2},
		{3,1,2},
		{3,2,3},
		{2,1,3},
		{3,3,2},
		{3,3,3},
		{2,2,3},
		{2,3,1},
		{2,3,2},
		{1,3,2},
		{2,3,3},
		{1,2,3}
	};
	int i;

	/* 出力 */
	for (i=0; i<13; i++) {
		printf("med3(%d, %d, %d) = %d\n", data[i][0], data[i][1], data[i][2], med3(data[i][0], data[i][1], data[i][2]));
	}

	return 0;
}
