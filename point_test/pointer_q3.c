#include <stdio.h>

void calc4(int a, int b, double *_add, double *_div, double *_mul, double *_sub);

int main(){
	int a, b;
	double _add, _div, _mul, _sub;

	printf("A :"); 	scanf("%d", &a);
	printf("b :"); 	scanf("%d", &b);

	calc4(a, b, &_add, &_div, &_mul, &_sub);

	printf("addition :%f\ndivision :%f\nmultiplication :%f\nsubtraction :%f\n", _add, _div, _mul, _sub);
	return 0;
}

void calc4(int a, int b, double *_add, double *_div, double *_mul, double *_sub){
	*_add = a + b;
	*_div = (double)a / (double)b;
	*_mul = a * b;
	*_sub = a - b;
}
