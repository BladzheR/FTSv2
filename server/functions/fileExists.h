int fileExists() {

    FILE *list;
    list = fopen("list.xml", "a+");
    if (fgetc(list) == EOF) {
        printf("\nСписок файлов пуст, либо не существует!\nСоздам список,если его нет.\nОбновил список файлов!\n\n");
        loadList();
    }
    fclose(list);
    return 0;
}