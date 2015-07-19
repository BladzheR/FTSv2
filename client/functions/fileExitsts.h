int fileExists() {

    int i = 0;

    if ((recv(sock, &i, sizeof(i), 0)) < 0) {
        perror("recv[0]");
    }

    if (i == 1) {
        printf("\nФайл с данным именем уже существует на сервере!\nПерезаписать?[Да:0;Нет:1]:");
        scanf("%d", &i);
        printf("\n");
        if ((send(sock, &i, sizeof(i), 0)) < 0) {
            perror("send[0]");
        }
        if (i == 1) {
            return i;
        }
    }

    return 0;
}