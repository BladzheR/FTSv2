/**
* @author: Sergey Kudryavtsev <bladzher@yandex.ru>
******************************************************
*#--Компиляция/Отобразить время компиляции/Запуск--
alias Run_server='gcc functions/navigation.c server.c functions/addFile.c functions/downloadFile.c functions/fileTransferRecv.c functions/fileTransferSend.c functions/loadList.c functions/deleteFile.c functions/fileExitsts.c functions/listFilesExists.c  -o server -lm && time gcc server.c functions/addFile.c functions/downloadFile.c functions/fileTransferRecv.c functions/fileTransferSend.c functions/loadList.c functions/deleteFile.c functions/fileExitsts.c functions/listFilesExists.c functions/navigation.c -o time && ./server'
alias Run_client='gcc client.c functions/addFile.c functions/deleteFile.c functions/displayListFiles.c functions/downloadFile.c functions/fileExists.c functions/fileTransferRecv.c functions/fileTransferSend.c functions/listFilesExists.c functions/navigation.c -o client -lm && time gcc client.c functions/addFile.c functions/deleteFile.c functions/displayListFiles.c functions/downloadFile.c functions/fileExists.c functions/fileTransferRecv.c functions/fileTransferSend.c functions/listFilesExists.c functions/navigation.c -o time -lm && ./client'
*#--end--
 * ******************************************************
 */

static char *const SERVER_ADDRESS = "127.0.0.1";
static const int SERVER_PORT = 3425;

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include "functions/FTS_client.h"

void workingClient(int sock, int root) {

    int counter = 0, number = 0, *command = &number;
    char message[1024];
    while (1) {

        if (counter == 0) {
            recv(sock, message, sizeof(message), 0);
            counter++;
        }

        printf("%s\n", message);

        do {
            printf("Введите команду серверу[0-7]:");
            if (scanf("%d", &number) == 0) {
                printf("\n Ошибока ввода :) Как-нибудь в другой раз ...\nЖду 2 секунды и закругляюсь...\n");
                number = 4;
                sleep(2);
            }

        } while (number > 7 && number < 0);

        if ((number == 5) && (root != 1)) {
            printf("У вас недостаточно прав для совершения данного действия!\n");
            number = -1;
            if ((send(sock, &number, sizeof(number), 0)) < 0) {
                perror("send[0]");
            }
        }

        printf("Отправляю сообщение серверу.\n");

        if ((send(sock, &number, sizeof(number), 0)) < 0) {
            perror("send[0]");
        }

        printf("%d\n", *command);

        if (navigation(sock, *command, root) == 1) {
            remove(pathToList);
            break;
        }
    }
    close(sock);
}

int main(int argc, char *argv[]) {

    int root = 0;
    if ((argc == 3) && (((strcmp(argv[1], "admin")) && (strcmp(argv[2], "admin"))) == 0)) {
        root = 1;
        printf("\nВы вошли под правами Администратора!\n\n");
    } else {
        root = 0;
    }

    int sock = NULL;

    /*     Указываем параметры сервера    */
    struct sockaddr_in addr; // структура с адресом
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET; // домены Internet
    addr.sin_port = htons(SERVER_PORT); // Порт
    addr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);    //addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    /*END*/
    int check;
    if ((check = inet_pton(addr.sin_family, SERVER_ADDRESS, &addr.sin_addr)) < 0) {
        perror("Error: первый параметр не относится к категории корректных адресов.");
    } else if (!check) {
        perror("Error: второй параметр не содержит корректного IP-адреса.");
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {// создание TCP-сокета
        perror("socket");
        exit(1);
    }

    if (connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) { // установка соединения с сервером
        perror("connet");
        printf("Возможно, сервер не запущен!\n");
        close(sock);
        exit(2);
    } else {
        printf("Вы успешно подключились к системе передачи файлов!\n");
    }

    workingClient(sock, root);

    return 0;
}
