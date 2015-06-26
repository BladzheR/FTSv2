int addFile() {

    int i = 0;
    char pathToFile[] = pathToFolers, fileName[sizeName];

    if ((recv(sock, &i, 4, 0)) < 0) {
        perror("recv[1]");
    }
    if (i == 0) {

        if ((recv(sock, fileName, sizeof(fileName), 0)) < 0) {
            perror("recv[2]");
        }
        strcat(pathToFile, fileName);

        fileTransferRecv(pathToFile);

        printf("\n\nКлиент успешно добавил файл на сервер:%s\n\n", pathToFile);
    } else {
        return 1;
    }
    return 0;
}
