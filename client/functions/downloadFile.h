#include <math.h>

int downloadFile() {

    int k = 0, i = 0, number = 0, check = 0;
    char pathToFile[] = PATH_TO_LOAD;
    char fileName[sizeName];

    printf("Введите номер файла который желаете скачать:");
    scanf("%d", &number);

    if ((send(sock, &number, sizeof(number), 0)) < 0) {
        perror("send[4]");
    }
    printf("check:%d\n", check);
    recv(sock, &check, sizeof(check), 0);
    printf("check:%d\n", check);
    if (check != 0) {

        FILE *f0;
        if (!(f0 = fopen(pathToList, "rb"))) {
            perror("fopen:");
            return 1;
        }

        while ((fileName[i] = (char) fgetc(f0)) != EOF) {

            if (fileName[i] == '\n') {
                fileName[i] = '\0';
                i = 0;
                if (k == number) {break;}
                k++;
            }
            else {
                i++;
            }
        }

        fileName[i] = '\0';

        for (k = 1, i = 0; fileName[i] != ')'; i++) {
            k++;
        }

        strcpy(fileName, &fileName[k]);
        strcat(pathToFile, fileName);


        fclose(f0);

        long buffer[BUF_SIZE], rcv_len = 0;

        FILE *f;
        if (!(f = fopen(pathToFile, "wb"))) {
            perror("fopen");
            return 1;
        }

        long fsize = 0;
        if ((recv(sock, &fsize, sizeof(fsize), 0)) < 0) {
            perror("recv[10]");
        }

        long info = (long) ceil((float) fsize / 1024);
        printf("Размер файла:%lu\n%lu пакетов будет получено.\n", fsize, info);


        long fsizenow = 0;
        do {
            rcv_len = recv(sock, buffer, BUF_SIZE, 0);
            if (rcv_len == 0) {
                printf("Ошибка, не удалось полностью получить файл!\n");
                break;
            }
            fsizenow += rcv_len;
            printf("всего: %lu; получено сейчас: %lu; всего сейчас: %lu \n", fsize, rcv_len, fsizenow);
            fwrite(buffer, 1, (size_t) rcv_len, f);
        } while (fsizenow < fsize);     ///проверяем результат

        fclose(f);
        printf("Cкачен!(%s)\n", fileName);
    } else {
        printf("В данный момент файла под данным номером не существует.Файл не скачен!\n");
    }
    return 0;
}
