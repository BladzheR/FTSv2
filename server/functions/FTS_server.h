//
// Created by ksergey on 23.07.15.
//

#ifndef FILETRANSFERSYSTEM_FTS_SERVER_H
#define FILETRANSFERSYSTEM_FTS_SERVER_H

enum {
    commandDisplayListFiles, commandAddFile, commandDeleteFile,
    commandListFilesExists, commandDisconnectClient, commandDisconnectServer, commandUpdateListFiles
};

static const int ERROR_CLIENT_DISCONNECT = 99999;

#define pathToFolder "files"
#define pathToFolders "files/"
#define pathToList "list.xml"
static const int SIZE_NAME = 256;
static const int BUF_SIZE = 1024;


extern int navigation(int sock, int command, int pid);

extern int addFile(int sock);

extern int deleteFile(int sock);

extern int downloadFile(int sock);

extern int fileExists(int sock, char *fileName_go);

extern int fileTransferRecv(int sock, char pathToFile[]);

extern int fileTransferSend(int sock, char pathToFile[]);

extern int listFilesExists();

extern int loadList();

extern void clrscr(void);


#endif //FILETRANSFERSYSTEM_FTS_SERVER_H
