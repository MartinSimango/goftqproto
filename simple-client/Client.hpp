#pragma once
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../serialize.h"

namespace fileClient {


struct ServerPort {
    char * serverAddress;
    int port;
};


class FileClient {
    
    private:
    struct PacketHeader * packet;
    struct ServerPort * serverPort;
    bool isConnected;
    int sockfd;
    

    // TODO be able to have protocol specificied
    inline bool createServerAddress(struct sockaddr_in * servaddr) {

        bzero(servaddr, sizeof(servaddr));
        servaddr->sin_family = AF_INET;
        servaddr->sin_addr.s_addr = inet_addr(serverPort->serverAddress);
        servaddr->sin_port = htons(serverPort->port);
    }

    // connectToServer returns a socket file descripter connect to the socket specifed
    inline bool connectToServer(){
        
        struct sockaddr_in servaddr;

        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
            return false;
        }

        createServerAddress(&servaddr);
        
        if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
            return false;
        }
    
        return true;
    }


    public:

    // ServerPort represent the server the 
    FileClient(struct ServerPort * serverPort): serverPort(serverPort){}

    // Connect connects the client to the specific server
    bool Connect(){
        return (isConnected = connectToServer() == true);
    }

     // writeToServer writes to the server
    int WriteToServer(struct FilePacket * packet){
        if (!isConnected) {
            return -1;
        }  
        unsigned char buffer[sizeof(struct FilePacket)];  //buffer will point to the start of the array of data bytes to be written and is where data is stored
        unsigned char *ptr; //ptr will point to the end of the array of data bytes to be written 

        ptr = serialize_file_packet(buffer, packet);
        return write(sockfd, buffer, ptr - buffer);
    }
       
    void Close(){
        isConnected = false;
        if (!isConnected) {
            close(sockfd);
        }
        isConnected = false;

    }
};




};

