#include <stdio.h>

struct Striangle{
	double Base;
	double Height;
	double Area;
};

void calcTriangleS(double base,double height,struct Striangle* p_stri);

int main(){
	double base, height;
	struct Striangle tri;

	printf("Base :");
	scanf("%lf", &base);
	printf("Heigth :");
	scanf("%lf", &height);

	calcTriangleS(base, height, &tri);

	printf("calcTriangleS\n\tBase :%f, Height :%f, Area :%f\n", tri.Base, tri.Height, tri.Area);

	return 0;
}

void calcTriangleS(double base,double height,struct Striangle* p_stri){
	p_stri->Base = base;
	p_stri->Height = height;
	p_stri->Area = p_stri->Base * p_stri->Height / 2;
}
