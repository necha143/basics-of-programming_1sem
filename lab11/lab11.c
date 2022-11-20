#include "eleventh.h"

int main() {
    struct triangle trian = triangle_init();
    trian= calc_of_sides (trian);
    trian= perimetr(trian);
    trian= area(trian);
    printf("Perimetr: %.2f\nArea: %.0f\n", trian.perimetr, trian.area);
    return 0;
}
