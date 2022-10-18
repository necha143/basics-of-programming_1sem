#include <stdio.h>

#define BEGIN 20
#define END 30

int main(void)
{
   int x,y;
   printf("Input a number: ");
   scanf("%d", &x);

   int result = BEGIN <= x && x <= END;

   printf("1.Does a number %d is inside range from %d to %d?: %s \n", x, BEGIN, END, result ? "Yes!":"No");

   printf("Input new number: ");
   scanf("%d",&y);
   printf("2.17 bit in your number is: %d",(y>>16)%2);

   return 0;
}

