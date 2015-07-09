int downloadFile() {

    int k = 0, i = 0, number = 0, check = 0;
    char pathToFile[] = pathToLoad;
    char fileName[sizeName];

    printf("Введите номер файла который желаете скачать:");
    scanf("%d", &number);

    if ((send(sock, &number, sizeof(number), 0)) < 0) {
        perror("send[4]");
    }

    recv(sock, &check, sizeof(check), 0);
    if (check == 0) {
        printf("В данный момент файла под данным номером не существует.Файл не скачен!\n");
    } else {
        FILE *f0;
        if (!(f0 = fopen(pathToList, "rb"))) {
            perror("fopen:");
            return 1;
        }

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

        strcpy(fileName, &fileName[k]);
        strcat(pathToFile, fileName);

        fclose(f0);

        long buffer[BUF_SIZE], rcv_len = 0;

        FILE *f;
        if (!(f = fopen(pathToFile, "wb"))) {
            perror("fopen");
            return 1;
        }

        long fsize = 0;
        if ((recv(sock, &fsize, sizeof(fsize), 0)) < 0) {
            perror("recv[10]");
        }

        //usleep(1);

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
        printf("\nФайл успешно скачен!\n");
    }
    return 0;
}
