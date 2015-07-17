enum {
    commandZero, commandOne, commandTwo, commandTree, commandFour, commandFive, commandSix, commandSeven
};

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
