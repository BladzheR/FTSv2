int downloadFile() {

    int i = 0, k = 0, q = 0, number = 0;
    char fileName[sizeName], pathToFile[] = pathToFolers;

    if ((recv(sock, (void *) &number, 4, 0)) < 0) {
        perror("recv[4]");
    }

    printf("%d кол-во файлов на сервере.\n", numberOfFiles);

    if (number < 0 || number > numberOfFiles) { //>=
        i++;

        if ((send(sock, (char *) &i, sizeof(i), 0)) < 0) {
            perror("send[4]");
        }
    } else {

        if ((send(sock, (char *) &i, sizeof(i), 0)) < 0) {
            perror("send[5]");
        }
        printf("Клиент скачал файл под номером:%d\n", number);
        number--;

        FILE *fo;
        if (!(fo = fopen(pathToList, "r"))) {
            perror("fopen");
            return 1;
        }

        while ((fileName[i] = (char) fgetc(fo)) != EOF) {

            if (fileName[i] == '\n') {
                fileName[i] = '\0';
                i = 0;
                q = k - 1;
                if (q == number) {
                    break;
                }
                k++;
            } else {
                i++;
            }
        }
        fileName[i] = '\0';
        printf("%s\n", fileName);

        for (k = 1, i = 0; fileName[i] != ')'; i++) {
            k++;
        }

        strcpy(fileName, &fileName[k]);
        strcat(pathToFile, fileName);

        fclose(fo);

        struct stat st;

        stat(pathToFile, &st);
        printf("Size: %d bytes\n\n", (int) st.st_size);

        fileTransferSend(pathToFile);

        printf("\nКлиент скачал файл:%s\n", pathToFile);
    }
    return 0;
}
