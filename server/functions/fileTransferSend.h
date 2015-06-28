int fileTransferSend(char pathToFile[]) {

    FILE *f;
    if (!(f = fopen(pathToFile, "rb"))) {
        perror("fopen");
        return 1;
    }
    fseek(f, 0, SEEK_END);
    long fsize = (int) ftell(f);
    rewind(f);

    printf("Размер сообщения: %lu\n", fsize);

    long info = (fsize / BUF_SIZE) + 1;
    printf("%lu пакетов будет отправлено.\n", info);

    char buffer[BUF_SIZE];
    long sended = 0, readed = 0;

    if ((send(sock, (char *) &fsize, sizeof(int), 0)) < 0) {
        perror("send[10]");
    }

    usleep(1);

    int i = 0;
    do {
        readed = fread(buffer, 1, BUF_SIZE, f);

        if ((send(sock, buffer, (size_t) readed, 0)) < 0) {
            perror("send[7]");
        }
        sended += readed;
        i++;
    } while (sended != fsize);
    printf("Отправлено пакетов:%d.Всего:%lu\n",i , info);
    fclose(f);

    return 0;
}
