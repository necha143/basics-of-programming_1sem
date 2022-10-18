#include <stdio.h>

int main(void) {
    int a[7] = {90, 76, 54, 23, 56, 12, 48};
    printf("1. \n");
    for (int i = 0; i < 7; i++) {
        printf("%d%s %d ",i+1,")", a[i]);
        printf("\n");
    }

    int mas1[2][2] = {1, 2,3,4};
    int mas2[2][2] = {1,0,0,1};

    int ans[2][2];
    for (int i=0;i<2;i++){
        for (int j=0;j<2;j++){
            ans[i][j]=mas1[i][0]*mas2[0][j] + mas1[i][1]*mas2[1][j];
        }
    }

    printf("2.\n");
    for (int i=0; i<2; i++)
    {
        for (int j=0; j<2; j++)
        {
            printf ("%d ", ans [i][j]);
        }
        printf ("\n");
    }

    return 0;
}