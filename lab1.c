#include <stdio.h>

int main(void)
{
	double a;
	char b;

    printf("Double: ");
    scanf(" %lf",&a);
    printf("Symbol: ");
    scanf(" %c",&b);

    printf("\n1.Your number: %lf",a);
    printf("\n2.Your symbol: %c",b);
	return 0;
}

