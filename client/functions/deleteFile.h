int deleteFile() {

    int number, i = 0;

    printf("Введите номер файла для удаления:");
    scanf("%d", &number);

    printf("%d\nОтправляю сообщение серверу.\n", number);

    if ((send(sock, (char *) &number, 4, 0)) < 0) {
        perror("send[3]");
    }

    recv(sock, &i, 4, 0);
    if (i != 0) {
        printf("В данный момент файла под данным номером не существует.Файл не удален!\n");
    } else {
        recv(sock, message, sizeof(message), 0);
        printf("%s\n", message);
        //displayListFiles(sock);
    }
    return 0;
}

