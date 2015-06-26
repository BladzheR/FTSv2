cmake_minimum_required(VERSION 3.1)
project(FileTransferSystem)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES trunk/server/server.c trunk/client/client.c )
add_executable(
 FileTransferSystem ${SOURCE_FILES}
 trunk/server/functions/addFile.h
 trunk/server/functions/deleteFile.h
 trunk/server/functions/downloadFile.h
 trunk/server/functions/fileTransferRecv.h
 trunk/server/functions/fileTransferSend.h
 trunk/server/functions/loadList.h
 trunk/server/functions/navigation.h

 trunk/client/functions/addFile.h
 trunk/client/functions/deleteFile.h
 trunk/client/functions/downloadFile.h
 trunk/client/functions/fileTransferRecv.h
 trunk/client/functions/fileTransferSend.h
 trunk/client/functions/navigation.h
 trunk/client/functions/displayListFiles.h

 trunk/server/server.c

 trunk/client/client.c
 )