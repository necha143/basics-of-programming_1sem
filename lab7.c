#include <stdio.h>
#include <math.h>

enum OS {Symbian=1, Linux=2, Windows=3, VxWork=4, QNX=5};

struct square {
    int x1;
    int y1;
    int x2;
    int y2;
};

union printer {
    int ch;
    struct {
        unsigned ready:1;
        unsigned little_toner:1;
        unsigned drum_damaged:1;
        unsigned no_paper:1;
    };
};

int main (void){
    enum OS sy, li, win, Vx, QNX;
    sy = Symbian;
    //li = Linux;
    //win = Windows;
    //Vx = VxWork;
    //QNX = QNX;
    printf("1.Symbian = %d\n", sy);

    struct square sqr;
    sqr.x1=1;
    sqr.y1=1;
    sqr.x2=1;
    sqr.y2=3;
    int AB = sqrt(pow(sqr.x2-sqr.x1,2) + pow(sqr.y2-sqr.y1,2));
    int perimetr = AB*4;
    printf("2.Perimetr of the square with coordinates of two points 1.(1,1) and 2.(1,3): %d\n", perimetr);

    union printer p;
    printf("3.Enter a number for the task: ");
    scanf("%x", &p.ch);
    printf("Ready?: ");
    printf(p.ready ? "ON\n" : "OFF\n");
    printf("Little toner?: ");
    printf(p.little_toner ? "ON\n" : "OFF\n");
    printf("Drum damaged?: ");
    printf(p.drum_damaged ? "ON\n" : "OFF\n");
    printf("No paper?: ");
    printf(p.no_paper ? "ON\n" : "OFF\n");

    return 0;
}