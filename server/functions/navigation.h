enum {
    commandZero, commandOne, commandTwo, commandTree, commandFour, commandFive, commandSix
};

void fileExists(){

    FILE *list;
    list = fopen("list.xml", "a+");
    if(fgetc(list) == EOF){
        printf("\nСписок файлов пуст, либо не существует!\nСоздам список,если его нет.\nОбновил список файлов!\n\n");
        loadList();
    }
    fclose(list);
}

int navigation(int getCommand) {
    if (getCommand == commandZero) {

        fileExists();

        if (fileTransferSend(pathToList) != 0) {
            perror("fileTransferSend:");
        }

        if (loadList() != 0) {
            perror("loadList:");
        }

    }
    else if (getCommand == commandOne) {
        if (addFile() != 0) {
            perror("addFile:");
        }
    }
    else if (getCommand == commandTwo) {
        if (deleteFile() != 0) {
            perror("deleteFile:");
        }
    }
    else if (getCommand == commandTree) {

        fileExists();

        if (fileTransferSend(pathToList) != 0) {
            perror("fileTransferSend:");
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
        return 2;
    }
    else if (getCommand == commandFive) {
        system("clear");
        kill (getppid(),SIGKILL);
        printf("Получена команда на завершение работы сервера!\nРабота сервера завершена!\n");
        return 1;
    }
    else if (getCommand == commandSix) {
        if (loadList() != 0) {
            perror("loadList:");
        }
    }
    return 0;
}
