int fileTransferSend(char pathToFile[]) {

    long sended = 0, readed = 0;
    char buffer[BUF_SIZE];
    FILE *f;
    if (!(f = fopen(pathToFile, "rb"))) {
        perror("fopen:");
        return 1;
    }

    fseek(f, 0, SEEK_END);
    int fsize = (int) ftell(f);
    rewind(f);

    if ((send(sock, (char *) &fsize, sizeof(int), 0)) < 0) {
        perror("send[10]");
    }

    usleep(1);

    do {
        readed = fread(buffer, 1, BUF_SIZE, f);

        if ((send(sock, buffer, (size_t) readed, 0)) < 0) {
            perror("send[0]");
        }
        sended += readed;
    } while (sended != fsize);
    fclose(f);

    return 0;
}
