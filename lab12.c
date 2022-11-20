#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    freopen(argv[1],"w",stdout);

    int summ=0;
    if (argc == 1) {
        printf("No arguments in configurations!");
    }
    else {
        for (int i = 2; i < argc; i++) {
            summ=summ+atoi(argv[i]);
        }
    }

    printf("The result of adding command line arguments: %d", summ);

    return 0;
}
