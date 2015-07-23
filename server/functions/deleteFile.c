#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include "FTS_server.h"

int deleteFile(int sock) {

    int number = 0, i = 0;

    if ((recv(sock, &number, sizeof(number), 0)) < 0) {
        perror("recv[0]");
    }
    printf("Получен номер файла для удаления: %d\n", number);

    if (number < 0 && number > numberOfFiles) {
        i++;

        if ((send(sock, &i, sizeof(i), 0)) < 0) {
            perror("send[0]");
        }

    } else {

        FILE *f0;
        if (!(f0 = fopen(pathToList, "rb"))) {
            perror("fopen:");
            return 1;
        }
        i = 0;
        int k = 0;
        char fileName[sizeName];
        while ((fileName[i] = (char) fgetc(f0)) != EOF) {

            if (fileName[i] == '\n') {
                fileName[i] = '\0';
                i = 0;
                if (k == number) { break; }
                k++;
            }
            else {
                i++;
            }
        }
        fclose(f0);
        fileName[i] = '\0';

        for (k = 1, i = 0; fileName[i] != ')'; i++) {
            k++;
        }

        char pathToFile[] = pathToFolders;
        strcpy(fileName, &fileName[k]);
        strcat(pathToFolder, fileName);

        if (remove(pathToFile) == -1) {
            i = 0;
            if ((send(sock, &i, sizeof(i), 0)) < 0) {
                perror("send[1.0]");
            }
            printf("Ошибка при удалении файла.Сервер не удалил файл!\n");

        } else {
            i = 1;
            if ((send(sock, &i, sizeof(i), 0)) < 0) {
                perror("send[1.1]");
            }
            printf("\nС сервера удалён файл:%s\n\n", pathToFile);
        }
    }
    return 0;
}
