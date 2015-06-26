int deleteFile() {

    int number = 0, i = 0;
    int numberOfFiles = 0;
    if ((recv(sock, &number, 4, 0)) < 0) {
        perror("recv[3]");
    }
    printf("Получен номер файла для удаления: %d\n", number);

    if (number < 0 || number >= numberOfFiles) {
        i++;

        if ((send(sock, (char *) &i, sizeof(i), 0)) < 0) {
            perror("send[0]");
        }

    } else {

        if ((send(sock, (char *) &i, sizeof(i), 0)) < 0) {
            perror("send[1]");
        }

        FILE *f0;
        if (!(f0 = fopen(pathToList, "rb"))) {
            perror("fopen:");
            return 1;
        }
        i = 0;
        int k = 0;
        char fileName[sizeName];
        while ((fileName[i] = (char) fgetc(f0)) != EOF) {

            if (fileName[i] == '\n') {
                fileName[i] = '\0';
                i = 0;
                if (k == number) {break;}
                k++;
            }
            else {
                i++;
            }
        }
        fileName[i] = '\0';

        for (k = 1, i = 0; fileName[i] != ')'; i++) {
            k++;
        }
        fclose(f0);
        char pathToFile[] = pathToFolers;
        strcpy(fileName, &fileName[k]);
        strcat(pathToFile, fileName);

        if (remove(pathToFile) == -1) {

            if ((send(sock, "Ошибка при удалении файла.Сервер не удалил файл!", sizeof("Ошибка при удалении файла.Сервер не удалил файл!"), 0)) < 0) {
                perror("send[2]");
            }

        } else {
            printf("\nС сервера удалён файл:%s\n\n", pathToFile);
            if ((send(sock, "Сервер удалил файл!", sizeof("Сервер удалил файл!"), 0)) < 0) {
                perror("send[3]");
            }
        }
        loadList();
        fileTransferRecv(pathToList);
    }
    return 0;
}
