#include <sys/socket.h>
#include <stdio.h>

int deleteFile(int sock) {

    int number = 0, i = 0;

    printf("Введите номер файла для удаления:");
    scanf("%d", &number);

    printf("%d\nОтправляю сообщение серверу.\n", number);

    if ((send(sock, &number, sizeof(number), 0)) < 0) {
        perror("send[3]");
    }

    recv(sock, &i, sizeof(i), 0);
    if (i == 1) {

        printf("\nСервер удалил файл!\n");

    } else if (i == 0) {

        printf("\nВ данный момент файла под данным номером не существует.Файл не удален!\n");
    }
    return 0;
}

