#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include "FTS_client.h"

int addFile(int sock) {

    /*
     * Доработать 2)Ввести свой путь!!!
     */

    int i = 0, check = 0, result = 0;
    char fileName[sizeName];

    printf("\nВыбрерите вариант загрузки файла на сервер:\n1)Из папки клиента PushOnServer.\n"
                   "2)Ввести свой путь.\n");
    scanf("%d", &check);

    if ((send(sock, &check, sizeof(check), 0)) < 0) {
        perror("send[0]");
    }

    if (check == 1) {

        char pathToFile[] = "/home/ksergey/projects/clion/FileTransferSystem_v2/trunk/client/pushOnServer/";
        printf("Введите имя файла с расширением.В имени фала не должно быть пробелов![text.txt]:");
        scanf("%s", fileName);

        strcat(pathToFile, fileName);

        printf("Путь до файла:%s\n\n", pathToFile);

        FILE *f;
        if (!(f = fopen(pathToFile, "r"))) {
            perror("Файл не найден!");
            i++;
        } else if ((send(sock, &i, sizeof(i), 0)) < 0) {
            perror("send[1]");
        }
        fclose(f);

        if (i == 0) {

            if ((send(sock, fileName, sizeof(fileName), 0)) < 0) {
                perror("send[2]");
            }

            result = fileExists(sock);
            if (result == 1) {

                return 0;

            } else if (result == 0) {

                fileTransferSend(sock, pathToFile);
                printf("\nФайл успешно добавлен на сервер!\n");

            } else {
                perror("fileExitst:");
            }
        }


    } else if (check == 2) {

        char pathToFile[sizeName];

        printf("Введите путь к файлу[/home/bladzher/Загрузки/]:");
        scanf("%s", pathToFile);

        printf("Введите имя файла с расширением(Пробелы замените на '_')[Mr.Probz-Waves(Robin_Schulz_Radio_Edit)(Europa_Plus).mp3]:");
        scanf("%s", fileName);

        strcat(pathToFile, fileName);

        FILE *f;
        if (!(f = fopen(pathToFile, "r"))) {
            printf("Файл не найден!\n");
            i++;
        }

        if ((send(sock, &i, sizeof(i), 0)) < 0) {
            perror("send[1]");
        }

        if (i == 0) {

            if ((send(sock, fileName, sizeof(fileName), 0)) < 0) {
                perror("send[2]");
            }

            result = fileExists(sock);
            if (result == 1) {
                fclose(f);
                return 0;

            } else if (result == 0) {

                fileTransferSend(sock, pathToFile);

                printf("Файл успешно добавлен!\n");

            } else {
                perror("fileExitst:");
            }
        }
        fclose(f);
    }

    return 0;
}
