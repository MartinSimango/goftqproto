#pragma once
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../serialize.h"
#include "../FileReadWriter.hpp"

namespace fileServer {


struct ServerPort {
    char * serverAddress;
    int port;
};


class FileServer {
    
    private:
    FileReadWriter *frw;
    bool isRunning;
    int sockfd;
    int connfd;
    int port;
    

    // TODO be able to have protocol specificied
    inline bool createAndBindServerAddress(struct sockaddr_in * servaddr) {
        
        bzero(servaddr, sizeof(*servaddr));
        servaddr->sin_family = AF_INET;
        servaddr->sin_addr.s_addr = htonl(INADDR_ANY); //allow address to connect
        servaddr->sin_port = htons(port);

        // Binding newly created socket to given IP and verification
	    if (bind(sockfd, (struct sockaddr *)servaddr, sizeof(*servaddr)) != 0){
            return false;
        }
        return true;

    }

    // createServer returns a socket file descripter connect to the socket specifed
    inline bool createServer(){
        
        struct sockaddr_in servaddr;

        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
            return false;
        }

        return createAndBindServerAddress(&servaddr);
    }

    inline int readFromClient(){
        
        struct FilePacket packet;

        unsigned char buff[sizeof(struct FilePacket)];
		bzero(buff, sizeof(struct FilePacket));

		// read the message from client and copy it in buffer
		read(connfd, buff, sizeof(struct FilePacket));
        
        deserialize_file_packet(buff, &packet);
        
        printf("\nOVER\n");
        printf("HER: %i\n", packet.bytes_rw);
        printf("HER: %s\n", packet.data);
        printf("HER: %s\n", packet.filename);
        printf("HER: %d\n", packet.mode);
        printf("HER: %d\n", packet.offset);

        frw = new FileReadWriter("test.txt", packet.mode);
        if(frw->Open() < 0){
            return -1; // TODO add error to file packet to speficy error message
        }

        if (packet.mode == READ){
            //read data from file then write back to cleint
          
            if ((packet.bytes_rw = frw->ReadFromFile(packet.data, sizeof(packet.data), packet.offset)) < 0 ){
                return -1;
            }
            return WriteToClient(&packet);
        }
        else {
            printf("SDF!!");
            frw->WriteToFile(packet.data, packet.bytes_rw, packet.offset);
            frw->Close();
            //write data baxk to client to tell it what was done 
            return WriteToClient(&packet);
        }
    }



    public:

    // ServerPort represent the server the 
    FileServer(int port): port(port){}

    // Connect connects the client to the specific server
    bool StartServer(int connections){
        return isRunning = createServer() && !listen(sockfd, connections);
    }

    bool Accept(){
        struct sockaddr_in  client;
        int len = sizeof(client);
        connfd = accept(sockfd, (struct sockaddr*)&client,(socklen_t *) &len);
        printf("CET");
        return readFromClient() == -1;
    }
     // writeToServer writes to the server

     // TODO allow for multiple clients (will have to source ip adddress in packet)
    int WriteToClient(struct FilePacket * packet){
        if (!isRunning) {
            return -1;
        }  
        unsigned char buffer[sizeof(struct FilePacket)];  //buffer will point to the start of the array of data bytes to be written and is where data is stored
        unsigned char *ptr; //ptr will point to the end of the array of data bytes to be written 

        ptr = serialize_file_packet(buffer, packet);
        return write(sockfd, buffer, ptr - buffer);
    }

    
    int Close(){
        if (isRunning) {
            isRunning = false;
            return close(sockfd);
        }
        return -2;
    }
};




};

