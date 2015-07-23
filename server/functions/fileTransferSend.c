#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include "FTS_server.h"

int fileTransferSend(int sock, char pathToFile[]) {

    FILE *f;
    if (!(f = fopen(pathToFile, "rb"))) {
        perror("fopen");
        return 1;
    }

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    rewind(f);

    printf("Размер сообщения: %lu\n", fsize);

    long info = (fsize / BUF_SIZE) + 1;
    printf("%lu пакетов будет отправлено.\n", info);

    char buffer[BUF_SIZE];

    if ((send(sock, &fsize, sizeof(fsize), 0)) < 0) {
        perror("send[10]");
    }

    usleep(1);

    int packages_sends = 0;
    while (1) {
        long result = fread(buffer, 1, BUF_SIZE, f);

        if (ferror(f)) {
            puts("Ошибка чтения!");
        }

        if ((send(sock, buffer, (size_t) result, 0)) < 0) {
            perror("send[7]");
            return 1;
        }

        packages_sends++;
        printf("Отправлен пакет %d (%lu)\n", packages_sends, info);

        if (feof(f)) {
            break;
        }
    }

    printf("Отправлено пакетов %d из %lu\n", packages_sends, info);
    fclose(f);

    return 0;
}
