#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include "FTS_server.h"

int downloadFile(int sock) {

    extern int numberOfFiles;
    int i = 0, k = 0, q = 0, number = 0;
    char fileName[SIZE_NAME]; //pathToFile[] = pathToFolders;

    char *pathToFile = (char *) malloc(sizeof(pathToFolders) * sizeof(char));
    if (!pathToFile) {
        printf("Allocation failure.");
        exit(1);
    }
    strcpy(pathToFile, pathToFolders);

    int j = 0;
    printf("pathToFile:");
    for (j = 0; j < sizeof(pathToFile); j++) {
        printf("%c", pathToFile[j]);
    }
    printf("\n");
    if ((recv(sock, (void *) &number, sizeof(int), 0)) < 0) {
        perror("recv[4]");
    }

    printf("%d кол-во файлов на сервере.\n", numberOfFiles);

    printf("number:%d\nnumberOfFiles:%d\n", number, numberOfFiles);
    if (number >= 0 && number <= numberOfFiles) {
        i++;
        if ((send(sock, &i, sizeof(i), 0)) < 0) {
            perror("send[5.0]");
        }

        printf("Клиент скачал файл под номером:%d\n", number);
        number--;

        FILE *fo;
        if (!(fo = fopen(pathToList, "r"))) {
            perror("fopen");
            return 1;
        }

        while ((fileName[i] = (char) fgetc(fo)) != EOF) {
            if (fileName[i] == '\n') {
                fileName[i] = '\0';
                i = 0;
                q = k - 1;
                if (q == number) {
                    break;
                }
                k++;
            } else {
                i++;
            }
        }
        fileName[i] = '\0';
        printf("%s\n", fileName);

        for (k = 1, i = 0; fileName[i] != ')'; i++) {
            k++;
        }

        strcpy(fileName, &fileName[k]);

        pathToFile = (char *) realloc(pathToFile, sizeof(fileName) * sizeof(char));

        if (!pathToFile) {
            printf("Allocation failure.");
            exit(1);
        }

        strcat(pathToFile, fileName);

        printf("pathToFile: %s\n", pathToFile);

        fclose(fo);

        if (fileTransferSend(sock, pathToFile) == 1) {
            free(pathToFile);
            return 1;
        }

        printf("\nКлиент скачал файл:%s\n", pathToFile);

    } else {
        i = 0;
        if ((send(sock, &i, sizeof(i), 0)) < 0) {
            perror("send[5.1]");
        }
    }
    free(pathToFile);

    return 0;
}
