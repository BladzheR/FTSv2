int loadList() {

    printf("\nИдёт обновления списка файлов...\n");

    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(pathToFolder))) {
        perror("diropen");
        return 1;
    }

    FILE *f;
    if (!(f = fopen(pathToList, "wb+"))) {
        perror("fopen");
        return 1;
    }

    int i = 0;
    while ((entry = readdir(dir)) != NULL) {

        if (strcmp(entry->d_name, ".") == 0 ||
                strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        fprintf(f, "%d)%s\n", i, entry->d_name);
        i++;

    }
    numberOfFiles = i;

    fclose(f);
    closedir(dir);

    printf("Список файлов обновлен!\n\n");

    //Задержка
    usleep(1);
    //

    return 0;
}
