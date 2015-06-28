int fileTransferRecv(char pathToFile[]) {

    FILE *f;
    if (!(f = fopen(pathToFile, "wb+"))) {
        perror("fopen::");
        return 1;
    }

    long rcv_len = 0;
    char buffer[BUF_SIZE];
    long fsize = 0;

    if ((recv(sock, &fsize, sizeof(fsize), 0)) < 0) {
        perror("recv[10]");
    }

    usleep(1);

    int rc;
    fd_set fdr;
    FD_ZERO(&fdr);
    FD_SET(sock, &fdr);
    struct timeval timeout;
    timeout.tv_sec = 1;   ///зададим  структуру времени со значением 1 сек
    timeout.tv_usec = 0;

    do {
        rcv_len = recv(sock, buffer, BUF_SIZE, 0);
        fwrite(buffer, 1, (size_t) rcv_len, f);
        rc = select(sock + 1, &fdr, NULL, NULL, &timeout);    ///ждём данные для чтения в потоке 1 сек.
    } while (rc);     ///проверяем результат

    fclose(f);

    return 0;
}
