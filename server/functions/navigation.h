enum {
    commandZero, commandOne, commandTwo, commandTree, commandFour, commandFive, commandSix
};

int navigation(int getCommand) {
    if (getCommand == commandZero) {

        if(listFilesExists() != 0){
            perror("fileExists:");
        }

        if (loadList() != 0) {
            perror("loadList:");
        }

        if (fileTransferSend(pathToList) != 0) {
            perror("fileTransferSend:");
        }

    }
    else if (getCommand == commandOne) {

        if(loadList() != 0){
            perror("loadList");
        }

        if (addFile() != 0) {
            perror("addFile:");
        }
    }
    else if (getCommand == commandTwo) {
        if (deleteFile() != 0) {
            perror("deleteFile:");
        }
        if(loadList() != 0){
            perror("loadList:");
        }
    }
    else if (getCommand == commandTree) {

        if(listFilesExists() != 0){
            perror("fileExists:");
        }

        int proof = 0;
        if ((recv(sock, &proof, sizeof(proof), 0)) < 0) {
            perror("recv[0]");
        }
        if(proof == 1) {

            if (fileTransferSend(pathToList) != 0) {
                perror("fileTransferSend:");
            }
        }
        if (loadList() != 0) {
            perror("loadList:");
        }

        if (downloadFile() != 0) {
            perror("downloadFile:");
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
        kill (pid,SIGTERM );
    }
    else if (getCommand == commandSix) {
        if (loadList() != 0) {
            perror("loadList:");
        }
    }
    return 0;
}
