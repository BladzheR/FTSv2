enum {
    commandZero, commandOne, commandTwo, commandTree, commandFour, commandFive, commandSix, commandSeven
};

int fileExists() {

    int proof = 0;
    FILE *list;
    list = fopen("list.xml", "a+");
    if (fgetc(list) == EOF) {
        printf("\nСписок файлов пуст, либо не существует!\nСоздам список,если его нет.\nОбновил список файлов!\n\n");
        proof = 1;
        if ((send(sock, &proof, sizeof(proof), 0)) < 0) {
            perror("send[0.0]");
        }
        fileTransferRecv();
    }else{
        proof = 0;
        if ((send(sock, &proof, sizeof(proof), 0)) < 0) {
            perror("send[0.1]");
        }
    }
    fclose(list);
    return 0;
}

int navigation(int getTeam) {
    if (getTeam == commandZero) {
        if (displayListFiles() != 0) {
            perror("displayListFiles:");
        }
    }
    else if (getTeam == commandOne) {
        if (addFile() != 0) {
            perror("addFiles:");
        }
    }
    else if (getTeam == commandTwo) {
        if (deleteFile() != 0) {
            perror("deleteFile:");
        }
    }
    else if (getTeam == commandTree) {

        if (fileExists() != 0) {
            perror("fileExists");
        }

        if (downloadFile() != 0) {
            perror("downloadFile");
        }

    }
    else if (getTeam == commandFour) {
        system("clear");
        printf("Вы успешно завершили работу программы клиент!\n");
        return 1;
    }
    else if (getTeam == commandFive) {
        system("clear");
        printf("Вы успешно завершили работу сервера и программы клиент!\n");
        return 1;
    }
    else if (getTeam == commandSix) {
        printf("\nСписок файлов обновлен!\n");
    } else if (getTeam == commandSeven) {
        system("clear");
    }
    return 0;
}
