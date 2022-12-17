#include <stdio.h>
#include <math.h>
#include <string.h>
typedef enum {false, true} bool;

#pragma pack(1) // выравниваем структуры и создаем их
typedef struct {
    char ID3[3];
    unsigned char vers[2];
    unsigned char flags;
    unsigned char sizeBytes[4];
} MP3_head;

typedef struct {
    char frameID[4];
    unsigned char sizeBytes[4];
    short flags;
} frame_head;

typedef struct {
    unsigned char sizeBytes[4];
    unsigned char flags[2];
    unsigned char sizeBytes2[4];
} dop_head;

typedef struct {
    MP3_head header;
    unsigned int headerSize;
    dop_head exHeader;
    frame_head frameHeader;
    unsigned int frameSize;
} all_MP3;
#pragma pop


int areStringsEqual(const char* string1, const char* string2, int length){ // сравниваем строки
    int i = 0;
    while (i!=length){
        if (string1[i]!=string2[i]){
            return 0;
        }
        if (string1[i]==0){
            return 1;
        }
        i++;
    }
    return 1;
}


int getSize(char* byteArr) { // получаем размер фрейма для вывода тегов
    int size = 0;
    unsigned char ch;
    for (int i = 0; i < 4; i++) {
        ch = byteArr[i];
        size += ch * pow(2, 7 * (3-i));
    }
    return size;
}

int get_correct_Size(char* byteArr) { // из-за кривой корректности фрейма, нам необходимо чуть по-другому равнять его размер
    int size = 0;                     //  для этого берем 8 бит а не 7
    unsigned char ch;
    for (int i = 0; i < 4; i++) {
        ch = byteArr[i];
        size += ch * pow(2, 8 * (3-i));
    }
    return size;
}


void show_or_get(FILE* f, char* search) {
    all_MP3 mp3;
    fseek(f,0,SEEK_SET); // перемещает указатель позиции в потоке
    fread(&mp3.header, sizeof(MP3_head), 1, f); // возвращает количество действительно считанных объектов

    long long tagSize = getSize(mp3.header.sizeBytes);
    long long counter = 0;

    while (counter <= tagSize) {

        fread(&mp3.frameHeader, sizeof(frame_head), 1, f);
        long long frameSize = get_correct_Size(mp3.frameHeader.sizeBytes);
        counter += 10 + frameSize;

        if (search==NULL && mp3.frameHeader.frameID[0] == 'T') {
            printf("%s ", mp3.frameHeader.frameID);
            while(frameSize--) {
                char ch = fgetc(f); // Функция fgetc() возвращает символ, взятый из входного потока stream и
                if (ch >= 32 && ch <= 126) { // находящийся сразу после текущей позиции, а также увеличивает указатель текущей позиции файла
                    printf("%c", ch);
                }
            }
            printf("\n");
        } else if (search!=NULL && areStringsEqual(mp3.frameHeader.frameID, search, 4)){ // поиск тэга по названию (функция get)
            printf("%s ", mp3.frameHeader.frameID);
            while(frameSize--) {
                char ch = fgetc(f);
                if (ch >= 32 && ch <= 126) {
                    printf("%c", ch);
                }
            }
        } else if (search!=NULL){ // в случае если на предыдущем шаге не найден наш тэг, свдигаемся дальше
            fseek(f, get_correct_Size(mp3.frameHeader.sizeBytes), SEEK_CUR);
        }
    }
}


void read_head(all_MP3 *mp3, FILE*fl) { // чтение заголовков файла
    fseek(fl,0,SEEK_SET);
    fread(&mp3->header,sizeof(MP3_head),1,fl);
    mp3->headerSize=getSize(mp3->header.sizeBytes);
    /*printf("%d",mp3->headerSize);*/
    if (mp3->header.flags &64) {
        fread(&mp3->exHeader, sizeof(dop_head), 1, fl);
        return;
    }
    return;
}


int find(FILE*fl, char *name) { //нахождение определноого фрейма, точнее его индекса
    /*fl= fopen(fl,"r+b");*/
    all_MP3 mp3;
    fseek(fl,0,SEEK_SET);
    read_head(&mp3, fl);

    while (ftell(fl)<=mp3.headerSize) { // функция возвращает значение указателя текущего положения потока
        fread(&mp3.frameHeader, sizeof(frame_head), 1, fl);
        if ((int)mp3.frameHeader.frameID[0]==0){
            return 0;
        }
        mp3.frameSize=get_correct_Size(mp3.frameHeader.sizeBytes);
        if (memcmp(mp3.frameHeader.frameID, name, strlen(name))){ // memcmp: Функция сравнивает первые num байтов блока памяти указателя memptr1 с
            fseek(fl,mp3.frameSize,SEEK_CUR);                     // первыми num байтами блока памяти memptr2
        } else{
            return (ftell(fl) - sizeof(frame_head));
        }
    }
    return 0;
}


void new_size(char *what, char *new, int old){
    if (what=="frame"){
        char size_old[sizeof(old)];
        memcpy(size_old, &old, sizeof(old)); // Функция memcpy копирует num байтов первого блока памяти, на который ссылается указатель srcptr,
        for (int i=0; i<4; i++) {            // во второй блок памяти, на который ссылается указатель destptr
            new[i]=size_old[3-i];
        }
        return;
    } else if (what=="head"){
        for (int i=3; i>=0; i--) {
            new[i]=old&127; // побитовое "И"
            old>>=7; // операция побитового свдига
        }
        return;
    }
}


void set_val(char *filepath, char *frame, char *value, int value_size) {
    all_MP3 mp3;
    rename(filepath, "NEWF.mp3");
    FILE *of=fopen("NEWF.mp3", "r+b");
    FILE *nf=fopen(filepath, "w+b");

    int index_of_frame=find(of, frame); //ищем индекс необходимого тега
    read_head(&mp3,of);
    fseek(of, index_of_frame, SEEK_SET);
    fread(&mp3.frameHeader, sizeof(frame_head), 1, of);
    mp3.frameSize=get_correct_Size(mp3.frameHeader.sizeBytes);

    fseek(of,0,SEEK_SET);
    fseek(nf,0,SEEK_SET);

    while (feof(of)==0) { // проверяет, достигнут ли конец файла, связанного с потоком,
        char ch;
        fread(&ch,1,1,of);
        if (feof(of)!=0) {
            break;
        }
        fseek(of,-1,SEEK_CUR);

        if (ftell(of)==sizeof(MP3_head) - sizeof(mp3.header.sizeBytes)) {
            new_size("head",mp3.header.sizeBytes, (int)(mp3.headerSize + (value_size - mp3.frameSize)));
            fwrite(&mp3.header.sizeBytes, sizeof(mp3.header.sizeBytes), 1, nf); // Функция fwrite записывает массив размером — count элементов, каждый из которых
            fseek(of, sizeof(mp3.header.sizeBytes), SEEK_CUR);                  // имеет размер size байт, в блок памяти, на который указывает ptrvoid — текущая позиция в потоке
        } else if (ftell(of)==index_of_frame) {
            new_size("frame",mp3.frameHeader.sizeBytes, value_size);
            fwrite(&mp3.frameHeader, sizeof(frame_head), 1, nf);
            fseek(of, mp3.frameSize + sizeof(frame_head), SEEK_CUR);
            for (int i=0; i<value_size; i++) {
                fwrite(&value[i], 1, 1, nf);
            }
        } else {
            fread(&ch, 1, 1, of);
            fwrite(&ch, 1, 1, nf);
        }
    }

    printf("New frame: %s", frame);
    fclose(of); // закрываем ранее откртые файла, для исключения будущих каких-либо конфликтов
    fclose(nf);
    remove("NEWF.mp3"); // Функция remove удаляет файл, имя которого указано в параметре fname
    return;
}


int main(int argc, char* argv[]) {
    FILE *mp3;
    char *filePath = NULL; // в данные переменные запишем значения, которые идут после них
    char isShow = 0;
    char *get = NULL;
    char *set = NULL;
    char *value = NULL;


    for (int i = 1; i < argc; i++) { // считываем значения после введенных аргументов
        if (areStringsEqual(argv[i], "--filepath", 10)) {
            filePath = argv[i] + 11;
        } else if (areStringsEqual(argv[i], "--show", 6)) {
            isShow = 1;
        } else if (areStringsEqual(argv[i], "--get", 5)) {
            get = argv[i] + 6;
        } else if (areStringsEqual(argv[i], "--set", 5)) {
            set = argv[i] + 6;
        } else if (areStringsEqual(argv[i], "--value", 7)) {
            value = argv[i] + 8;
        }
    }

    if (filePath == NULL) {
        printf("Cannot find the file\n");
        return 0;
    }


    if (isShow != 0) { // --show
        mp3 = fopen(filePath, "r+b");
        show_or_get(mp3, get);
        fclose(mp3);
    } else if (get != NULL) { // --get=" "
        mp3 = fopen(filePath, "r+b");
        show_or_get(mp3, get);
        fclose(mp3);
    } else if (set != NULL) { // --set" " --value=" "
        if (value == NULL) {
            printf("Not value argument");
            return 0;
        }
        set_val(filePath, set, value, strlen(value));
    }

    return 0;
}