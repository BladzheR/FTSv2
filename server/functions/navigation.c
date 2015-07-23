#include <stdio.h>
#include <sys/socket.h>
#include <signal.h>
#include "FTS_server.h"

void clrscr(void) {
    printf("\033[2J");            /* Clear the entire screen.             */
    printf("\033[0;0f");          /* Move cursor to the top left hand corner*/
}


int navigation(int sock, int command, int pid) {

    switch (command) {
        case commandDisplayListFiles:
            if (listFilesExists() != 0) {
                perror("fileExists:");
            }

            if (loadList() != 0) {
                perror("loadList:");
            }

            if (fileTransferSend(sock, pathToList) != 0) {
                perror("fileTransferSend:");
            }
            break;
        case commandAddFile:
            if (loadList() != 0) {
                perror("loadList");
            }

            if (addFile(sock) != 0) {
                perror("addFile:");
            }
            break;
        case commandDeleteFile:
            if (deleteFile(sock) != 0) {
                perror("deleteFile:");
            }
            if (loadList() != 0) {
                perror("loadList:");
            }
            break;
        case commandListFilesExists:
            if (listFilesExists() != 0) {
                perror("fileExists:");
            }

            int proof = 0;
            if ((recv(sock, &proof, sizeof(proof), 0)) < 0) {
                perror("recv[0]");
            }
            if (proof == 1) {

                if (fileTransferSend(sock, pathToList) != 0) {
                    perror("fileTransferSend:");
                }
            }
            if (loadList() != 0) {
                perror("loadList:");
            }

            int result = downloadFile(sock);
            if (result == 1) {
                printf("Клиент покинул нас...\n");
                return ERROR_CLIENT_DISCONNECT;
            }
            break;
        case commandDisconnectClient:
            clrscr();
            printf("Клиент отключился!\n");
            printf("\nОжидание подключения:\n");
            return 1;
        case commandDisconnectServer:
            clrscr();
            printf("Получена команда на принудительное завершение работы сервера!\n");
            kill(pid, SIGTERM);
        case commandUpdateListFiles:
            if (loadList() != 0) {
                perror("loadList:");
            }
            break;
        default:
            break;
    }
    return 0;
}
