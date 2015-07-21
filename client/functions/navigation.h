enum {
    commandDisplayListFiles, commandAddFile,
    commandDeleteFile, commandListFilesExists, commandFour, commandFive, commandSix, commandSeven
};

int navigation(int command) {
    if (command == commandDisplayListFiles) {
        if (displayListFiles() != 0) {
            perror("displayListFiles:");
        }
    }
    else if (command == commandAddFile) {
        if (addFile() != 0) {
            perror("addFiles:");
        }
    }
    else if (command == commandDeleteFile) {
        if (deleteFile() != 0) {
            perror("deleteFile:");
        }
    }
    else if (command == commandListFilesExists) {

        if (listFilesExists() != 0) {
            perror("fileExists");
        }

        int result = downloadFile();

        if (result != 0) {
            perror("downloadFile");
        }

    }
    else if (command == commandFour) {
        system("clear");
        printf("Вы успешно завершили работу программы клиент!\n");
        return 1;
    }
    else if (command == commandFive) {
        system("clear");
        printf("Вы успешно завершили работу сервера и программы клиент!\n");
        return 1;
    }
    else if (command == commandSix) {
        printf("\nСписок файлов обновлен!\n");
    } else if (command == commandSeven) {
        system("clear");
    }
    return 0;
}
