int listFilesExists() {

    int proof = 0;
    FILE *list;
    list = fopen("list.xml", "a+");
    if (fgetc(list) == EOF) {
        printf("\nСписок файлов пуст, либо не существует!\nСоздам список,если его нет.\nОбновил список файлов!\n\n");
        proof = 1;
        if ((send(sock, &proof, sizeof(proof), 0)) < 0) {
            perror("send[0.0]");
        }
        fileTransferRecv();
    } else {
        proof = 0;
        if ((send(sock, &proof, sizeof(proof), 0)) < 0) {
            perror("send[0.1]");
        }
    }
    fclose(list);
    return 0;
}