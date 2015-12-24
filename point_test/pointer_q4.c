#include <stdio.h>

struct answer{
	double _add, _div, _mul, _sub;
};

void calc5(int a, int b, struct answer *p);

int main(){
	int a, b;
	struct answer hoge;

	printf("A :"); 	scanf("%d", &a);
	printf("b :"); 	scanf("%d", &b);

	calc5(a, b, &hoge);

	printf("addition :%f\ndivision :%f\nmultiplication :%f\nsubtraction :%f\n", hoge._add, hoge._div, hoge._mul, hoge._sub);
	return 0;
}

void calc5(int a, int b, struct answer *p){
	p->_add = a + b;
	p->_div = (double)a / (double)b;
	p->_mul = a * b;
	p->_sub = a - b;
}
