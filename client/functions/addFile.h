int addFile() {

    int i = 0;
    char pathToFile[sizeName], fileName[sizeName];

    printf("Введите путь к файлу[/home/bladzher/Загрузки/]:");
    scanf("%s", pathToFile);

    printf("Введите имя файла с расширением(Пробелы замените на '_')[Mr.Probz-Waves(Robin_Schulz_Radio_Edit)(Europa_Plus).mp3]:");
    scanf("%s", fileName);

    strcat(pathToFile, fileName);

    FILE *f;
    if (!(f = fopen(pathToFile, "r"))) {
        printf("Файл не найден!\n");
        i++;
    }

    if ((send(sock, (char *) &i, 4, 0)) < 0) {
        perror("send[1]");
    }

    if (i == 0) {

        if ((send(sock, fileName, sizeof(fileName), 0)) < 0) {
            perror("send[2]");
        }

        fileTransferSend(pathToFile);

        fclose(f);
        printf("Файл успешно добавлен!\n");
    }
    return 0;
}
