cmake_minimum_required(VERSION 3.1)
project(FileTransferSystem)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES server/server.c client/client.c)
add_executable(
 FileTransferSystem ${SOURCE_FILES}
 server/functions/addFile.c
 server/functions/deleteFile.c
 server/functions/downloadFile.c
 server/functions/fileTransferRecv.c
 server/functions/fileTransferSend.c
 server/functions/loadList.c
 server/functions/navigation.c
 server/functions/listFilesExists.c
 server/functions/fileExitsts.c

 client/functions/addFile.h
 client/functions/deleteFile.h
 client/functions/downloadFile.h
 client/functions/fileTransferRecv.h
 client/functions/fileTransferSend.h
 client/functions/navigation.h
 client/functions/displayListFiles.h
 client/functions/listFilesExists.h
 client/functions/fileExitsts.h

 server/server.c

 client/client.c

 server/functions/FTS_server.h)