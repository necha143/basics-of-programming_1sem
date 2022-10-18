#include <stdio.h>
#include <stdlib.h>

int main() {
    int mas [4] = {50, 40, 30, 20};
    int *q;
    q=mas;
    printf("1: \n");
    for (int i=0; i<4; i++)
    {
        printf ("%d\n", *(q+i));
    }
    printf ("\n");

    int *n;
    n = calloc(4,sizeof (int));

    for (int i=0;i<4;i++){
        n[i]=mas[i];
    }

    printf("2: \n");
    for (int i=0; i<4; i++)
    {
        printf ("%d\n", n[i]);
    }
    free(n);

    return 0;
}