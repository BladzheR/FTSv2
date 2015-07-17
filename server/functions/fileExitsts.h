int fileExists(char *fileName){

    int i = 0, k = 0, q = 0;

    FILE *f;
    if (!(f = fopen(pathToList, "r"))) {
        perror("fopen");
        return 1;
    }

//    while ((fileName[i] = (char) fgetc(f)) != EOF) {
//
//        if (fileName[i] == '\n') {
//            fileName[i] = '\0';
//            i = 0;
//            q = k - 1;
//            if (q == number) {
//                break;
//            }
//            k++;
//        } else {
//            i++;
//        }
//    }
//    fileName[i] = '\0';
//    printf("%s\n", fileName);
//
//    for (k = 1, i = 0; fileName[i] != ')'; i++) {
//        k++;
//    }
//
//    strcpy(fileName, &fileName[k]);

    fclose(f);

    return 0;
}