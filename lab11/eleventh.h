#ifndef LABS11_ELEVENTH_H
#define LABS11_ELEVENTH_H

#include <stdio.h>
#include <math.h>

struct triangle{
    int x1, y1, x2, y2, x3, y3;
    double first_side, second_side, third_side, perimetr, area;
};

struct triangle coordinates_init();

struct triangle calc_of_sides (struct triangle tria);

struct triangle triangle_init ();

struct triangle perimetr (struct triangle tria);

struct triangle area (struct triangle tria);


int is_triangle (struct triangle is_triangle);

int isosceles (struct triangle isosceles);

#endif //LABS11_ELEVENTH_H
