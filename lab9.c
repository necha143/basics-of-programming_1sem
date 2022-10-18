#include <stdio.h>
#include <stdbool.h>

bool isS1mple(int number)
{
    bool res=true;
    for (int i=2;i<number;i++){
        if (number%i==0){
            res=false;
            break;
        }
    }
    return res;
}

int main()
{
    char line[100]={};
    printf("Enter your line with numbers or english letters:");
    gets(line);
    int numb=0, big=0, small=0;

    for (int i=0; i<100;i++){
        if ((line[i]>='0')&&(line[i]<='9')){
            numb++;
        } else if ((line[i]>='a')&&(line[i]<='z')) {
            small++;
        } else if ((line[i]>='A')&&(line[i]<='Z')) {
            big++;
        }
    }

    printf("1. Count of: numbers: %d; lowercase letters: %d; uppercase letters: %d\n", numb, small, big);

    int a;
    printf("Enter a number:");
    scanf("%d", &a);
    printf("2. Prime numbers that are included in a given number: ");

    for (int i=2; i<=a;i++){
        if (isS1mple(i)){
            printf("%d ",i);
        }
    }

    return 0;
}
