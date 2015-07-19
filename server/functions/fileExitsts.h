int fileExists(char *fileName_go) {

    int i = 0, check = 0;

    FILE *f;
    if (!(f = fopen(pathToList, "r"))) {
        perror("fopen");
        return 1;
    }

    char fileName[1024];
    while ((fileName[i] = (char) fgetc(f)) != EOF) {

        if (fileName[i] == '\n') {
            fileName[i] = '\0';

            for (check = 1, i = 0; fileName[i] != ')'; i++) {
                check++;
            }
            strcpy(fileName, &fileName[check]);

            if (strcmp(fileName, fileName_go) == 0) {
                printf("\n%s\n", fileName);
                check = 1;
                break;
            }

            i = 0;
        }
        else {
            i++;
        }
    }
    fclose(f);

    if (check == 1) {

        if ((send(sock, &check, sizeof(check), 0)) < 0) {
            perror("send[0]");
        }

        if ((recv(sock, &check, sizeof(check), 0)) < 0) {
            perror("recv[2]");
        }

        if (check == 1) {
            return 1;
        }
    }

    return 0;
}