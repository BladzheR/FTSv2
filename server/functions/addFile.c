#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include "FTS_server.h"

int addFile(int sock) {

    int i = 0, result = 0;
    char pathToFile[] = pathToFolders, fileName[SIZE_NAME];

    if ((recv(sock, &i, sizeof(i), 0)) < 0) {
        perror("recv[1]");
    }
    if (i == 1) {

        if ((recv(sock, &i, sizeof(i), 0)) < 0) {
            perror("recv[1]");
        }
        if (i == 0) {

            if ((recv(sock, fileName, sizeof(fileName), 0)) < 0) {
                perror("recv[2]");
            }

            result = fileExists(sock, fileName);
            if (result == 1) {

                if ((send(sock, &result, sizeof(result), 0)) < 0) {
                    perror("send[0]");
                }

            } else if (result == 0) {

                strcat(pathToFile, fileName);

                ///

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

                long info = (fsize / BUF_SIZE) + 1;
                printf("Размер файла:%lu\n%lu пакетов будет получено.\n", fsize, info);

                //usleep(1);

                int rc;
                fd_set fdr;
                FD_ZERO(&fdr);
                FD_SET(sock, &fdr);
                struct timeval timeout;
                timeout.tv_sec = 1;   ///зададим  структуру времени со значением 1 сек
                timeout.tv_usec = 0;

                fsize = 0;
                do {
                    rcv_len = recv(sock, buffer, BUF_SIZE, 0);
                    fsize += rcv_len;
                    printf("\n%lu\n%lu\n", fsize, rcv_len);
                    fwrite(buffer, 1, (size_t) rcv_len, f);
                    rc = select(sock + 5, &fdr, NULL, NULL, &timeout);    ///ждём данные для чтения в потоке 1 сек.
                } while (fsize != info && rc);     ///проверяем результат

                fclose(f);

                ///

                printf("\n\nКлиент успешно добавил файл на сервер:%s\n\n", pathToFile);
            } else {
                perror("fileExists:");
            }
        } else {
            return 1;
        }

    } else if (i == 2) {

        if ((recv(sock, &i, sizeof(i), 0)) < 0) {
            perror("recv[1]");
        }
        if (i == 0) {

            if ((recv(sock, fileName, sizeof(fileName), 0)) < 0) {
                perror("recv[2]");
            }

            result = fileExists(sock, fileName);
            if (result == 1) {

                if ((send(sock, &result, sizeof(result), 0)) < 0) {
                    perror("send[0]");
                }

            } else if (result == 0) {

                strcat(pathToFile, fileName);

                fileTransferRecv(sock, pathToFile);

                printf("\n\nКлиент успешно добавил файл на сервер:%s\n\n", pathToFile);
            } else {
                perror("fileExists:");
            }
        } else {
            return 1;
        }
    }
    return 0;
}
