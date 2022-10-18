#include <stdio.h>

int main(void) {
    int a,a1;

    printf("1.Enter a decimal number: ");
    scanf(" %d", &a);

    printf("2.Your number in the octal number system: %o\n", a);

    long long res3 = a<<1;
    printf("3.New shifted number of %o is: %o\n", a, res3);

    long long res4 = ~a;
    printf("4.'Not' %o is: %o\n", a, res4);

    printf("5.Enter a number in octal number system: ");
    scanf("%o",&a1);
    printf("5.'Exlusive or': %o", a^a1);

    return 0;
}

