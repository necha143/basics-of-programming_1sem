#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(1) // ровняем считывание, после чего идут структуры с байтами файла
typedef struct {
    unsigned char ID[2];
    unsigned int file_size;
    unsigned char unused[4];
    unsigned int pixel_offset;
} BMPHeader;

typedef struct {
    unsigned int header_size;
    unsigned int width;
    unsigned int height;
    unsigned short color_planes;
    unsigned short bits_per_pixel;
    unsigned int comp;
    unsigned int data_size;
    unsigned int pwidth;
    unsigned int pheight;
    unsigned int colors_count;
    unsigned int imp_colors;
} DIBHeader;

typedef struct {
    BMPHeader head;
    DIBHeader important;
    unsigned int colors[256];
    char **arr;
} BMPFile;
#pragma pop


BMPFile* loadBMPFile(char *file_Name) { // заполняем структуры из файла
    FILE* file = fopen(file_Name, "r+b");
    BMPFile *bmp_file = malloc(sizeof(BMPFile));

    fread(&bmp_file->head, sizeof(BMPHeader), 1, file);
    fread(&bmp_file->important, sizeof(DIBHeader), 1, file);
    fread(&bmp_file->colors, sizeof(bmp_file->colors), 1, file);

    bmp_file->arr = malloc(bmp_file->important.height * sizeof(unsigned char*)); // создаем массив с пикселями
    for (int i = 0; i < bmp_file->important.height; i++) {
        bmp_file->arr[i] = malloc(bmp_file->important.width * sizeof(unsigned char) + (3*bmp_file->important.width % 4));
    }

    for (int i = 0; i < bmp_file->important.height; i++) { // заполняем массив с пикселями
        for (int j = 0; j < bmp_file->important.width + (3*bmp_file->important.width % 4); j++) {
            fread(&bmp_file->arr[i][j], 1, 1, file);
        }
    }

    fclose(file);
    return bmp_file;
}


int count_neighbors(int x, int y, int w, int h, char **array){ // подсчет соседей пикселя
#define getPixel(x,y) !array[x][y]
    int count = 0;

    if (x > 0) {
        if (getPixel(x-1,y)){
            count++;
        }
        if (y > 0) {
            if (getPixel(x-1,y-1)){
                count++;
            }
        }
        if (y + 1 < w) {
            if (getPixel(x-1,y+1)){
                count++;
            }
        }
    }
    if (x + 1 < h) {
        if (getPixel(x+1,y)){
            count++;
        }
        if (y > 0) {
            if (getPixel(x+1,y-1)){
                count++;
            }
        }
        if (y + 1 < w) {
            if (getPixel(x+1,y+1)){
                count++;
            }
        }
    }
    if (y > 0) {
        if (getPixel(x,y-1)){
            count++;
        }
    }
    if (y + 1 < w) {
        if (getPixel(x,y+1)){
            count++;
        }
    }

    return count;
}


void GameLife(BMPFile *bmp_file) { // работа с пикселями
    int h=bmp_file->important.height;
    int w=bmp_file->important.width;
    char **array=bmp_file->arr;
    char new_pixels[h][w];


    for (int i = h - 1; i >= 0; i--) {
        for (int j = 0; j < w; j++) {

            if ((int)array[i][j] == 0) {
                if (count_neighbors(i,j,w,h,array) == 3 || count_neighbors(i,j,w,h,array) == 2) {
                    new_pixels[i][j] = 0;
                } else {
                    new_pixels[i][j] = -1;
                }
            } else {
                if (count_neighbors(i,j,w,h,array) == 3) {
                    new_pixels[i][j] = 0;
                } else {
                    new_pixels[i][j] = array[i][j];
                }
            }
        }
    }


    for (int i = h - 1; i >= 0; i--) { // перенос пикселей из вспомогательного массива в основной
        for (int j = 0; j < w; j++) {
            if (array[i][j] != new_pixels[i][j]) {
                array[i][j] = new_pixels[i][j];
            }
        }
    }
}


int main(int argc, char **argv) {
    FILE *file;
    BMPFile *bmp = loadBMPFile(argv[2]);
    int maxiter, dumpfreq = 1;
    char *dirname;

    for (int i = 0; i < argc; i++){ // считывание информации из командной строки
        if (!strcmp("--input", argv[i])) {
            file = fopen(argv[2], "r+b");
        }
        if (!strcmp("--output", argv[i])) {
            dirname = argv[i+1];
        }
        if (!strcmp("--max_iter", argv[i])) {
            maxiter = strtol(argv[i+1], 0, 10);
        }
        if (!strcmp("--dump_freq", argv[i])) {
            dumpfreq = strtol(argv[i+1], 0, 10);
        }
    }


    for (int i=0; i<maxiter; i++){
        GameLife(bmp); // вызов игры

        if (i % dumpfreq == 0) { // запись изменений
            char* filename = (char*)malloc(maxiter * sizeof(char));
            char* way = (char*)malloc(100 * sizeof(char));
            strcpy(way, dirname);
            strcat(strcat(way, "\\"), strcat(itoa(i+1, filename, 10), ".bmp")); // создали путь чтобы сохранить наш файл

            FILE *life = fopen(way, "w+b"); // перезаписали изменения в файл
            fwrite(&bmp->head, sizeof(BMPHeader), 1, life);
            fwrite(&bmp->important, sizeof(DIBHeader), 1, life);
            fwrite(&bmp->colors, sizeof(bmp->colors), 1, life);

            int height=bmp->important.height;
            int width=bmp->important.width;
            for (int i = 0; i < height; i++) {
                int correct_width=width + (3*width % 4);
                for (int j = 0; j < correct_width; j++) {
                    fwrite(&bmp->arr[i][j], 1, 1, life); // перезаписали информацию о пикселях в файл, дабы появилась картинка
                }
            }
            fclose(life);
        }
    }


    fclose(file);
    free(bmp);
    return 0;
}