/**
* @author: Sergey Kudryavtsev <bladzher@yandex.ru>
*  HELP:
* ...........PC name: /ksergey/
* ...........Ultrabook name: /bladzher/
*******************************************************************************
 */
#define pathToLoad "Загрузки/"
#define sizeName 256
#define pathToList "list.xml"
#define BUF_SIZE 1024

char message[1024];
int sock;                // дескриптор сокета

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include "functions/fileTransferRecv.h"
#include "functions/fileTransferSend.h"
#include "functions/displayListFiles.h"
#include "functions/deleteFile.h"
#include "functions/downloadFile.h"
#include "functions/addFile.h"
#include "functions/navigation.h"

void settingsClient(){

    /*     Указываем параметры сервера    */
    struct sockaddr_in addr; // структура с адресом
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET; // домены Internet
    addr.sin_port = htons(3425); // Порт
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");    //addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    /*END*/

    int check;
    if ((check = inet_pton(addr.sin_family, "127.0.0.1", &addr.sin_addr)) < 0) {
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

}

void workingClient(){

    int counter = 0, number = 0, *getTeam = &number;
    while (1) {

        if (counter == 0) {
            recv(sock, message, sizeof(message), 0);
            counter++;
        }

        printf("%s\n", message);

        do {
            printf("Введите команду серверу[0-7]:");
            if((scanf("%d", &number)) == 0){
                printf("\n Ошибока ввода :) Как-нибудь в другой раз ...\nЖду 2 секунды и закругляюсь...\n");
                number = 4;
                sleep(2);
            }

        } while (number > 7 || number < 0);

        printf("Отправляю сообщение серверу.\n");

        if ((send(sock, &number, sizeof(int), 0)) < 0) {
            perror("send[0]");
        }

        printf("%d\n", *getTeam);

        if (navigation(*getTeam) == 1) {
            remove(pathToList);
            break;
        }
    }
    close(sock);
}

int main() {

    settingsClient();
    workingClient();

    return 0;
}
