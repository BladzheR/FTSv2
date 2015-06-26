int fileTransferRecv() {

    char buffer[BUF_SIZE];
    long rcv_len = 0;
    memset(buffer, 0, sizeof buffer);

    FILE *f;
    if (!(f = fopen(pathToList, "wb+"))) {
        perror("fopen");
        return 1;
    }

    long fsize = 0;
    if ((recv(sock, &fsize, sizeof(fsize), 0)) < 0) {
        perror("recv[10]");
    }
    printf("Размер сообщения: %lu\n", fsize);

    long info = (fsize / BUF_SIZE) + 1;
    printf("%lu пакетов будет получено.\n", info);

    sleep(2);

    int rc;
    fd_set fdr;
    FD_ZERO(&fdr);
    FD_SET(sock, &fdr);
    struct timeval timeout;
    timeout.tv_sec = 1;   ///зададим  структуру времени со значением 1 сек
    timeout.tv_usec = 0;

    int i = 0;
    do {
        rcv_len = recv(sock, buffer, BUF_SIZE, 0);
        fwrite(buffer, 1, (size_t) rcv_len, f);
        rc = select(sock + 1, &fdr, NULL, NULL, &timeout);    ///ждём данные для чтения в потоке 1 сек.
        i++;
    } while (rc);     ///проверяем результат
    printf("Получено пакетов:%d.Всего:%lu\n",i , info);
    fclose(f);

    return 0;
}
