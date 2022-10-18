#include <stdio.h>
#include <string.h>

int main(void) {

    char line1[100], line2[100], s1[100], s2[100];
    printf("Enter first line: ");
    gets(line1);

    printf("Enter second line: ");
    gets(line2);

    int n=4; //пускай в условии n=4
    strcpy(s1,line1);
    strcpy(s2,line1);

    strncat(line1,line2,n);
    printf("1. %s\n", line1);

    strcpy(line1,line2);
    printf("2. %s\n",line1);

    strncpy(s1,line2,n);
    printf("3. %s\n",s1);

    char *symvl;
    int ch='g';

    symvl = strrchr(line2,ch); //Пускай мы будем искать последнее вхождение символа 'g' во вторую строку

    if (symvl==NULL)
        printf("4. There are not symbols 'g' in your line\n");
    else
        printf("4. Last index of 'g' in your line is: %lld\n", symvl-line2+1);

    int a;
    a = strcspn (s2,line2);
    printf("5. The length of a segment of one line that does not contain characters from the second: %d\n",a);
    //Поиск учитывает и завершающий нуль-символов, поэтому, если функция возвращает длину строки
    // line1, это значит, что  ни один из символов строки line2 не входит в состав line1.


    return 0;
}
