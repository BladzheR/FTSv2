//
// Created by ksergey on 29.07.15.
//

#ifndef FILETRANSFERSYSTEM_FTS_CLIENT_H
#define FILETRANSFERSYSTEM_FTS_CLIENT_H

enum {
    commandDisplayListFiles, commandAddFile,
    commandDeleteFile, commandListFilesExists, commandDisconnectClient,
    commandDisconnectServer, commandUpdateListFiles, commandClearScreen
};

#define PATH_TO_LOAD "Загрузки/"
#define sizeName 256
#define pathToList "list.xml"
#define BUF_SIZE 1024

extern int addFile(int sock);

extern int deleteFile();

extern int displayListFiles();

extern int downloadFile(int sock);

extern int fileExists(int sock);

extern int fileTransferRecv(int sock);

extern int fileTransferSend(int sock, char pathToFile[]);

extern int listFilesExists(int sock);

extern int navigation(int sock, int command);

#endif //FILETRANSFERSYSTEM_FTS_CLIENT_H
