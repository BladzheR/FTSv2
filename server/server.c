/**
* @author: Sergey Kudryavtsev <bladzher@yandex.ru>
*  HELP:
* ...........PC name: /ksergey/
* ...........Ultrabook name: /bladzher/
*******************************************************************************
 */
#define textMenu "\n========================\nМЕНЮ:\n0)Отобразить список файлов\n1)Добавить файл\n2)Удалить файл\n3)Скачать файл\n4)Выход\n5)Выключить сервер\n6)Обновить список файлов\n7)Очистить экран\n8)Поиск\n========================\n"
#define pathToFolder "files"
#define pathToFolders "files/"
#define pathToList "list.xml"
#define sizeName 256
#define BUF_SIZE 1024

int numberOfFiles = 0;
int sock, listener;      // дескрипторы сокетов
int pid;

#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include "functions/loadList.h"
#include "functions/fileTransferRecv.h"
#include <signal.h>
#include <stdlib.h>
#include "functions/fileTransferSend.h"
#include "functions/fileExitsts.h"
#include "functions/addFile.h"
#include "functions/deleteFile.h"
#include "functions/downloadFile.h"
#include "functions/listFilesExists.h"
#include "functions/navigation.h"

void runDaemon() {
    pid_t pidDaemonFTS = daemon(0, 0); //     демон - запуск отдельно от терминала...
    if (pidDaemonFTS == -1) {
        //close(ls);
        perror("demonize error!\n");
    }
}

void settingsServer() {

    if ((listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {// создаем сокет для входных подключений
        perror("socket");
        exit(1);
    }

    /*     Указываем параметры сервера    */
    struct sockaddr_in addr; // структура с адресом
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");    //addr.sin_addr.s_addr = htonl(INADDR_ANY);
    /*    END block    */

    int check, yes = 1;
    if ((check = inet_pton(addr.sin_family, "127.0.0.1", &addr.sin_addr)) < 0) {
        perror("Error: первый параметр не относится к категории корректных адресов.");
    } else if (!check) {
        perror("Error: второй параметр не содержит корректного IP-адреса.");
    }

    setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);

    if (bind(listener, (struct sockaddr *) &addr, sizeof(struct sockaddr_in)) <
        0) { // связываемся с сетевым устройство. Сейчас это устройство lo - "петля", которое используется для отладки сетевых приложений
        perror("bind");
        close(listener);
        exit(2);
    }

    if ((listen(listener, 1)) == -1) { // очередь входных подключений
        perror("listen");
        close(listener);
        exit(0);
    }

    printf("Сервер запущен!\n\nОжидание подключения:\n");
}

void workingServer() {

    int counter = 0, number = 0, result = 0, *getCommand = &number;


    while (result != 1) { //для подкл.клиентов.

        if ((sock = accept(listener, NULL, NULL)) <
            0) {// принимаем входные подключение и создаем отделный сокет для каждого нового подключившегося клиента
            perror("accept");
            close(listener);
            exit(3);
        }

        pid = fork();
        switch (pid) {
            case -1:
                perror("fork");
                exit(1);
            case 0:
                close(listener);

                printf("К серверу подключился клиент!\n");

                while (1) {
                    if (counter == 0) {
                        send(sock, textMenu, sizeof(textMenu), 0);
                        counter++;
                    }
                    do {
                        printf("Ожидаем команду:\n");
                        if ((recv(sock, &number, sizeof(number), 0)) < 0) {
                            perror("recv[0]");
                        }
                        if (*getCommand < 7 && *getCommand >= 0) {
                            break;
                        } else {
                            printf("Получена неверная команда!\n");
                        }
                    } while (1);
                    printf("Получена команда от клиента: %d\n", *getCommand);

                    result = navigation(*getCommand);
                    if (result == 1) {
                        close(sock);
                        break;
                    } else if (result == 2) {
                        break;
                    }
                }
            default:
                close(sock);
        }
    }
}

int main(int argc, char *argv[]) {

    if (argc == 2 && strcmp(argv[1], "daemon") == 0) {
        printf("%s", argv[1]);
        runDaemon();
    }

    settingsServer();
    workingServer();

    return 0;
}














