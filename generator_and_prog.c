#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    int index; // Индефикатор
    int level; // Уровень важности
    char text[81]; // Текст
}Data;

// Компораторы

int compIndex(const Data *r1, const Data *r2){
    return r1->index - r2->index;
}

int compLevel(const Data *r1, const Data *r2){
    return r1->level - r2->level;
}

int compText(const Data *r1, const Data *r2){
    return strcmp(r1->text,r2->text);
}

int revcompText(const Data *r1, const Data *r2){
    return strcmp(r2->text,r1->text);
}

int revcompLevel(const Data *r1, const Data *r2){
    return r2->level - r1->level;
}

int revcompIndex(const Data *r1, const Data *r2){
    return r2->index - r1->index;
}

// Вспомогательные функции
void swap(void* v1, void* v2, int size)
{
    char buffer[size];
    memcpy(buffer, v1, size);
    memcpy(v1, v2, size);
    memcpy(v2, buffer, size);
}

// Сортировки:

void myqsort(void* v, int size, int left, int right ,int (*comp)(void*, void*))
{
    void *vt, *v3;
    int i, last;
    int mid = (left + right) / 2;
    if (left >= right) {
        return;
    }
    void* vl = (char*)(v + (left * size));
    void* vr = (char*)(v + (mid * size));
    swap(vl, vr, size);
    last = left;
    for (i = left + 1; i <= right; i++) {

        vt = (char*)(v + (i * size));
        if ((*comp)(vl, vt) > 0) {
            ++last;
            v3 = (char*)(v + (last * size));
            swap(vt, v3, size);
        }
    }
    v3 = (char*)(v + (last * size));
    swap(vl, v3, size);
    myqsort(v, size, left, last - 1, comp);
    myqsort(v, size, last + 1, right, comp);
}

void myshellSort(Data *array, int n, int sort){
    Data temp1;
    int size1;
    switch (sort) {
        case 1:
            for (int interval = n / 2; interval > 0; interval /= 2) {
                for (int i = interval; i < n; i += 1) {
                    int temp;
                    temp = array[i].index;
                    int j;
                    for (j = i; j >= interval && array[j - interval].index > temp; j -= interval) {
                        array[j].index = array[j - interval].index;
                    }
                    array[j].index = temp;
                }
            }
            break;
        case 2:
            for (int interval = n / 2; interval > 0; interval /= 2) {
                for (int i = interval; i < n; i += 1) {
                    int temp;
                    temp = array[i].level;
                    int j;
                    for (j = i; j >= interval && array[j - interval].level > temp; j -= interval) {
                        array[j].level = array[j - interval].level;
                    }
                    array[j].level = temp;
                }
            }
            break;
        case 3:
            for(int interval = n / 2; interval > 0; interval /= 2) {
                for (int i = interval; i < n; i += 1) {
                    temp1 = array[i];
                    int j;
                    for (j = i; j >= interval && strcmp(array[i - interval].text, array[i].text) > 0; j -= interval) {
                        array[j] = array[j - interval];
                    }
                    array[j] = temp1;
                }
            }
            break;
    }
}

void myshellSortrev(Data *array, int n, int sort){
    Data temp1;
    int size1;
    switch (sort) {
        case 1:
            for (int interval = n / 2; interval > 0; interval /= 2) {
                for (int i = interval; i < n; i += 1) {
                    int temp;
                    temp = array[i].index;
                    int j;
                    for (j = i; j >= interval && array[j - interval].index < temp; j -= interval) {
                        array[j].index = array[j - interval].index;
                    }
                    array[j].index = temp;
                }
            }
            break;
        case 2:
            for (int interval = n / 2; interval > 0; interval /= 2) {
                for (int i = interval; i < n; i += 1) {
                    int temp;
                    temp = array[i].level;
                    int j;
                    for (j = i; j >= interval && array[j - interval].level < temp; j -= interval) {
                        array[j].level = array[j - interval].level;
                    }
                    array[j].level = temp;
                }
            }
            break;
        case 3:
            for(int interval = n / 2; interval > 0; interval /= 2) {
                for (int i = interval; i < n; i += 1) {
                    temp1 = array[i];
                    int j;
                    for (j = i; j >= interval && strcmp(array[i].text, array[i - interval].text) > 0; j -= interval) {
                        array[j] = array[j - interval];
                    }
                    array[j] = temp1;
                }
            }
            break;
    }
}

// Мейн

int main(){
    clock_t start,end;
    long double time;
    FILE* output;
    //srand(time(NULL));
    int menu = 0;
    int sort = 0;
    int reverse = 0;
    int size_str = 2; // тут ошибка
    int kolvo;
    printf("Print kolvo:\n");
    scanf("%d",&kolvo);
    Data *r = calloc(kolvo,sizeof(Data));
        for(int i = 0; i<kolvo; i++){
            r[i].index = rand()%1000; // index
            r[i].level= 1 + rand()%5; // level
            //
            size_t nameLen = 4 + (size_t)rand() % 33;
            char nameBuf[nameLen];
            char *buf;

            //char *nameBuf = calloc(nameLen,sizeof(char));
            for(size_t f = 0; f < nameLen; f++){
                nameBuf[f] = (char) (rand() % (122 - 97+1) + 97);
            }
            nameBuf[nameLen - 1] = '\0';
            buf = strdup(nameBuf);
            strcpy(r[i].text,buf);
            free(buf);

            printf("%d %d %s\n", r[i].index, r[i].level, r[i].text);
        }
        int i = kolvo;
        int test = 0;
        while(menu >= 0 && menu < 4 && test != -1) {
            printf("Select your sort: \n1 - original qsort,\n2 - personal qsort,\n3 - shell sort.\n ");
            test = scanf("%d", &menu);
            while (menu > 3) {
                printf("You have mistake,please repeat:\n");
                scanf("%d", &menu);
            }
            start = clock();
            switch (menu) {
                case 1: // qsort original
                    printf("Select item:\n1 - Index,\n2 - Level,\n3 - Text.\n");
                    scanf("%d", &sort);
                    while (sort < 0 || sort > 3) {
                        printf("You have mistake,please repeat:\n");
                        scanf("%d", &sort);
                    }
                    printf("Select type of reverse:\n0 - no,\n1 - yes.\n");
                    scanf("%d", &reverse);
                    while (reverse < 0 || reverse > 3) {
                        printf("You have mistake,please repeat:\n");
                        scanf("%d", &reverse);
                    }
                    if (reverse == 0) { // обычный порядок сортировки
                        if (sort == 1) {
                            qsort(r, i, sizeof(Data), (int (*)(const void *, const void *)) compIndex);
                        }
                        if (sort == 2) {
                            qsort(r, i, sizeof(Data), (int (*)(const void *, const void *)) compLevel);
                        }
                        if (sort == 3) {
                            qsort(r, i, sizeof(Data), (int (*)(const void *, const void *)) compText);
                        }
                    }
                    if (reverse == 1) { // обратный порядок сортировки
                        if (sort == 4) {
                            qsort(r, i, sizeof(Data), (int (*)(const void *, const void *)) revcompIndex);
                        }
                        if (sort == 5) {
                            qsort(r, i, sizeof(Data), (int (*)(const void *, const void *)) revcompLevel);
                        }
                        if (sort == 6) {
                            qsort(r, i, sizeof(Data), (int (*)(const void *, const void *)) revcompText);
                        }
                    }
                    break;

                case 2: // personal qsort
                    printf("Select item:\n1 - Index,\n2 - Level,\n3 - Text.\n");
                    scanf("%d", &sort);
                    while (sort < 0 || sort > 4) {
                        printf("You have mistake,please repeat:\n");
                        scanf("%d", &sort);
                    }
                    printf("Select type of reverse:\n0 - no,\n1 - yes.\n");
                    scanf("%d", &reverse);
                    while (reverse < 0 || reverse > 3) {
                        printf("You have mistake,please repeat:\n");
                        scanf("%d", &reverse);
                    }
                    if (reverse == 0) { // обычный порядок сортировки
                        if (sort == 1) {
                            myqsort(r, sizeof(Data), 0, 3, (int (*)(void *, void *)) compIndex);
                        }
                        if (sort == 2) {
                            myqsort(r, sizeof(Data), 0, 3, (int (*)(void *, void *)) compLevel);
                        }
                        if (sort == 3) {
                            myqsort(r, sizeof(Data), 0, 3, (int (*)(void *, void *)) compText);
                        }
                    }
                    if (reverse == 1) { // обратный порядок сортировки
                        if (sort == 1) {
                            myqsort(r, sizeof(Data), 0, 3, (int (*)(void *, void *)) revcompIndex);
                        }
                        if (sort == 2) {
                            myqsort(r, sizeof(Data), 0, 3, (int (*)(void *, void *)) revcompLevel);
                        }
                        if (sort == 3) {
                            myqsort(r, sizeof(Data), 0, 3, (int (*)(void *, void *)) revcompText);
                        }

                    }
                    break;
                case 3:
                    printf("Select item:\n1 - Index,\n2 - Level,\n3 - Text.\n");
                    scanf("%d", &sort);
                    while (sort < 1 || sort > 7) {
                        printf("You have mistake,please repeat:\n");
                        scanf("%d", &sort);
                    }
                    printf("Select type of reverse:\n0 - no,\n1 - yes.\n");
                    scanf("%d", &reverse);
                    while (reverse < 0 || reverse > 3) {
                        printf("You have mistake,please repeat:\n");
                        scanf("%d", &reverse);
                    }
                    if (reverse == 0) { // обычный порядок сортировки
                        if (sort == 1) {
                            myshellSort(r, i, sort);
                        }
                        if (sort == 2) {
                            myshellSort(r, i, sort);
                        }
                        if (sort == 3) {
                            myshellSort(r, i, sort);
                        }
                    }
                    if (reverse == 1) { // обратный порядок сортировки
                        if (sort == 1) {
                            myshellSortrev(r, i, sort);
                        }
                        if (sort == 2) {
                            myshellSortrev(r, i, sort);
                        }
                        if (sort == 3) {
                            myshellSortrev(r, i, sort);
                        }
                    }
                    end = clock();
                    time = (long double) (end - start) / (CLOCKS_PER_SEC);
                    printf("Sort time:%LF\nCheck your result in file.\n", time);
            }
            end = clock();
            time = (long double)(end-start)/(CLOCKS_PER_SEC);
            printf("%LF\n",time);
        }
    output = fopen("text1.txt", "w+");
    for(int d = 0; d < kolvo; d++) {
        fprintf(output, "%d %d %s\n", r[d].index, r[d].level, r[d].text);
    }

    fclose(output);

    free(r);

    return 0;
}

