int displayListFiles() {

    fileTransferRecv();

    FILE *f;
    if (!(f = fopen(pathToList, "rb"))) {
        perror("fopen");
        return 1;
    }

    fseek(f, 0, SEEK_END);
    long lSize = ftell(f);
    rewind(f);

    if (lSize == 0) {
        printf("\nДанные не получены!Пожалуйста,попробуйте еще раз.\n");
    } else {

        char buffer[BUF_SIZE * 4];
        memset(buffer, 0, sizeof buffer);

        long result = fread(buffer, 1, (size_t) lSize, f);
        if (result != lSize) {
            perror("Ошибка чтения");
            return 1;
        }

        printf("\nСписок файлов:\n%s\n", buffer);
    }
    fclose(f);
    return 0;
}
