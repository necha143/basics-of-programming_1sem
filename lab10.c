#include <stdio.h>

int NOD(int a, int b){
    while (a!=b){
        if (a>b){
            a=a-b;
        } else {
            b=b-a;
        }
    }
    return a;
}

int NOK(int a, int b){
    a=(a*b)/NOD(a,b);
    return a;
}

int summ(int a){
    if (!a){
        return 0;
    }
    return (a%10) + summ(a/10);
}

int main() {
    int a,b;
    printf("1.Enter 2 numbers to calculate NOD and NOK:");
    scanf("%d",&a);
    scanf("%d",&b);

    printf("1. Your NOD: %d \n", NOD(a,b));
    printf("1. Your NOK: %d \n", NOK(a,b));

    int c;
    printf("\n2.Enter a number to calculate sum of digits:");
    scanf("%d",&c);

    printf("2. Your sum of digits: %d", summ(c));
    return 0;
}