#include <stdio.h>
#include <math.h>
int main(void) {
	double m;
	scanf_s("%lf", &m);

	double a1 = sqrt ((pow ((3 * m + 2),2)) - 24*m);
	double a2 = (3 * sqrt(m)) - (2 / (sqrt(m)));
	double z1 = a1 / a2;

	printf("Result 1: %lf\n", z1);

	double z2 = -(sqrt(m));

	printf("Result 2: %lf", z2);

	return 0;
}

