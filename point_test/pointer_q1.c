#include <stdio.h>

void calcTriangle(double base, double height, double *area);

int main(){
	double base, height, area;

	printf("Base :");
	scanf("%lf", &base);
	printf("Heigth :");
	scanf("%lf", &height);

	calcTriangle(base, height, &area);

	printf("calcTriangle :%f\n", area);

	return 0;
}

void calcTriangle(double base, double height, double *area){
	*area = base * height / 2;
}
