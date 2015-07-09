cmake_minimum_required(VERSION 3.1)
project(FileTransferSystem)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES server/server.c client/client.c)
add_executable(
 FileTransferSystem ${SOURCE_FILES}
 server/functions/addFile.h
 server/functions/deleteFile.h
 server/functions/downloadFile.h
 server/functions/fileTransferRecv.h
 server/functions/fileTransferSend.h
 server/functions/loadList.h
 server/functions/navigation.h

 client/functions/addFile.h
 client/functions/deleteFile.h
 client/functions/downloadFile.h
 client/functions/fileTransferRecv.h
 client/functions/fileTransferSend.h
 client/functions/navigation.h
 client/functions/displayListFiles.h

 server/server.c

 client/client.c)