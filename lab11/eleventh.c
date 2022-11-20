#include "eleventh.h"

struct triangle coordinates_init (){
    struct triangle trian_gap;
    printf("Enter x1:\n");
    scanf("%d",&trian_gap.x1);
    printf("Enter y1:\n");
    scanf("%d",&trian_gap.y1);
    printf("Enter x2:\n");
    scanf("%d",&trian_gap.x2);
    printf("Enter y2:\n");
    scanf("%d",&trian_gap.y2);
    printf("Enter x3:\n");
    scanf("%d",&trian_gap.x3);
    printf("Enter y3:\n");
    scanf("%d",&trian_gap.y3);
    return trian_gap;
}

int is_triangle(struct triangle is_triangle){
    double a=sqrt(pow((is_triangle.x2-is_triangle.x1),2) + pow((is_triangle.y2-is_triangle.y1),2));
    double b=sqrt(pow((is_triangle.x3-is_triangle.x2),2) + pow((is_triangle.y3-is_triangle.y2),2));
    double c=sqrt(pow((is_triangle.x3-is_triangle.x1),2) + pow((is_triangle.y3-is_triangle.y1),2));
    if ((a<b+c) && (b<a+c) && (c<a+b)){
        return 1;
    } else {
        return 0;
    }
}

struct triangle calc_of_sides (struct triangle tria){
    tria.first_side=sqrt(pow((tria.x2-tria.x1),2) + pow((tria.y2-tria.y1),2));
    tria.second_side=sqrt(pow((tria.x3-tria.x2),2) + pow((tria.y3-tria.y2),2));
    tria.third_side=sqrt(pow((tria.x3-tria.x1),2) + pow((tria.y3-tria.y1),2));
    return tria;
}

int isosceles(struct triangle isosceles){
    if (isosceles.first_side==isosceles.second_side || isosceles.first_side==isosceles.third_side || isosceles.second_side==isosceles.third_side){
        return 1;
    } else {
        return 0;
    }
}

struct triangle triangle_init(){
    int bool=1;
    struct triangle tria_init;
    struct triangle tria_init2;
    while (bool){
        tria_init=coordinates_init();
        tria_init2= calc_of_sides(tria_init);
        if (is_triangle(tria_init) && isosceles(tria_init2)){
            bool=0;
        } else {
            printf("Enter new coordinates:\n");
        }
    }
    return tria_init;
}

struct triangle perimetr(struct triangle tria){
    tria.perimetr=tria.first_side+tria.second_side+tria.third_side;
    return tria;
}

struct triangle area (struct triangle tria){
    tria.area=(abs((tria.x2-tria.x1)*(tria.y3-tria.y1) - (tria.x3-tria.x1)*(tria.y2-tria.y1)))/2;
    return tria;
}