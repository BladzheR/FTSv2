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

 client/functions/addFile.c
 client/functions/deleteFile.c
 client/functions/downloadFile.c
 client/functions/fileTransferRecv.c
 client/functions/fileTransferSend.c
 client/functions/navigation.c
 client/functions/displayListFiles.c
 client/functions/listFilesExists.c
 client/functions/fileExists.c

 server/server.c

 client/client.c

 server/functions/FTS_server.h client/functions/FTS_client.h)