#include <stdio.h>
#include "FTS_server.h"

int listFilesExists() {

    FILE *list;
    list = fopen("list.xml", "a+");
    if (fgetc(list) == EOF) {
        printf("\nСписок файлов пуст, либо не существует!\nСоздам список,если его нет.\n\n");
        if (loadList() != 0) {
            perror("loadList:");
        } else {
            printf("Обновил список файлов!\n");
        }
    }
    fclose(list);
    return 0;
}