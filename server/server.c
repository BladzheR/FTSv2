/**
* @author: Sergey Kudryavtsev <bladzher@yandex.ru>
******************************************************
*#--Компиляция/Отобразить время компиляции/Запуск--
*alias Run_server='gcc server.c functions/addFile.c functions/downloadFile.c functions/fileTransferRecv.c functions/fileTransferSend.c functions/loadList.c functions/deleteFile.c functions/fileExitsts.c functions/listFilesExists.c functions/navigation.c -o server -lm && time gcc server.c functions/addFile.c functions/downloadFile.c functions/fileTransferRecv.c functions/fileTransferSend.c functions/loadList.c functions/deleteFile.c functions/fileExitsts.c functions/listFilesExists.c functions/navigation.c -o time && ./server'
*alias Run_client='gcc client.c -o client -lm && time gcc client.c -o time -lm && ./client'
*#--end--
 * ******************************************************
 */
#define textMenu "\n========================\nМЕНЮ:\n0)Отобразить список файлов\n1)Добавить файл\n2)Удалить файл\n3)Скачать файл\n4)Выход\n5)Выключить сервер\n6)Обновить список файлов\n7)Очистить экран\n8)Поиск\n========================\n"

int numberOfFiles = 0;


#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "functions/FTS_server.h"

void runDaemon() {
    pid_t pidDaemonFTS = daemon(0, 0); //     демон - запуск отдельно от терминала...
    if (pidDaemonFTS == -1) {
        perror("demonize error!\n");
    }
}

/*
 * Написать конфиг для настройки клиент-сервера
 */


void workingServer(int sock, int listener) {

    int counter = 0, number = 0, result = 0, *command = &number;

    while (result != ERROR_CLIENT_DISCONNECT || result != 1) { //для подкл.клиентов.

        if ((sock = accept(listener, NULL, NULL)) <
            0) {// принимаем входные подключение и создаем отделный сокет для каждого нового подключившегося клиента
            perror("accept");
            close(listener);
            exit(3);
        }

        int pid = fork();
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
                        if (*command < 7 && *command >= 0) {
                            break;
                        } else {
                            printf("Получена неверная команда!\n");
                        }
                    } while (1);
                    printf("Получена команда от клиента: %d\n", *command);

                    navigation(sock, number, pid);
                    result = 0;
                    printf("RESULT: %d \n", result);
                    if (result == 1) {
                        close(sock);
                        break;
                    } else if (result == 2) {
                        break;
                    } else if (result == ERROR_CLIENT_DISCONNECT) {
                        break;
                    }
                }
            default:
                close(sock);
        }
    }
    printf("Клиент завершил работу!\n");
}

int main(int argc, char *argv[]) {

    if (argc == 2 && strcmp(argv[1], "daemon") == 0) {
        printf("%s", argv[1]);
        runDaemon();
    }

    int sock = 0, listener = 0;// дескрипторы сокетов

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


    workingServer(sock, listener);

    return 0;
}














