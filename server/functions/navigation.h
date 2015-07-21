enum {
    commandDisplayListFiles, commandAddFile, commandDeleteFile,
    commandListFilesExists, commandFour, commandFive, commandSix
};

static const int ERROR_CLIENT_DISCONNECT = 99999;

int navigation(int getCommand) {
    if (getCommand == commandDisplayListFiles) {

        if (listFilesExists() != 0) {
            perror("fileExists:");
        }

        if (loadList() != 0) {
            perror("loadList:");
        }

        if (fileTransferSend(pathToList) != 0) {
            perror("fileTransferSend:");
        }

    }
    else if (getCommand == commandAddFile) {

        if (loadList() != 0) {
            perror("loadList");
        }

        if (addFile() != 0) {
            perror("addFile:");
        }
    }
    else if (getCommand == commandDeleteFile) {

        if (deleteFile() != 0) {
            perror("deleteFile:");
        }
        if (loadList() != 0) {
            perror("loadList:");
        }
    }
    else if (getCommand == commandListFilesExists) {

        if (listFilesExists() != 0) {
            perror("fileExists:");
        }

        int proof = 0;
        if ((recv(sock, &proof, sizeof(proof), 0)) < 0) {
            perror("recv[0]");
        }
        if (proof == 1) {

            if (fileTransferSend(pathToList) != 0) {
                perror("fileTransferSend:");
            }
        }
        if (loadList() != 0) {
            perror("loadList:");
        }

        int result = downloadFile();
        if (result == 1) {
            printf("Клиент покинул нас...\n");
            return ERROR_CLIENT_DISCONNECT;
        }

    }
    else if (getCommand == commandFour) {
        system("clear");
        printf("Клиент отключился!\n");
        printf("\nОжидание подключения:\n");
        return 1;
    }
    else if (getCommand == commandFive) {
        system("clear");
        printf("Получена команда на принудительное завершение работы сервера!\n");
        kill(pid, SIGTERM);
    }
    else if (getCommand == commandSix) {
        if (loadList() != 0) {
            perror("loadList:");
        }
    }
    return 0;
}
