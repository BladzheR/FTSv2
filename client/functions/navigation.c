#include <stdio.h>
#include "FTS_client.h"

void clrscr(void) {
    printf("\033[2J");            /* Clear the entire screen.             */
    printf("\033[0;0f");          /* Move cursor to the top left hand corner*/
}

int navigation(int sock, int command) {

    switch (command) {
        case commandDisplayListFiles:

            fileTransferRecv(sock);

            if (displayListFiles() != 0) {
                perror("displayListFiles:");
            }
            break;
        case commandAddFile:
            if (addFile(sock) != 0) {
                perror("addFiles:");
            }
            break;
        case commandDeleteFile:
            if (deleteFile() != 0) {
                perror("deleteFile:");
            }
            break;
        case commandListFilesExists:
            if (listFilesExists(sock) != 0) {
                perror("fileExists");
            }

            int result = downloadFile(sock);

            if (result != 0) {
                perror("downloadFile");
            }
            break;
        case commandDisconnectClient:
            clrscr();
            printf("Вы успешно завершили работу программы клиент!\n");
            return 1;
        case commandDisconnectServer:
            clrscr();
            printf("Вы успешно завершили работу сервера и программы клиент!\n");
            return 1;
        case commandUpdateListFiles:
            printf("\nСписок файлов обновлен!\n");
            //Добавить проверку!!!
            break;
        case commandClearScreen:
            clrscr();
            break;
        default:
            break;
    }
    return 0;
}

