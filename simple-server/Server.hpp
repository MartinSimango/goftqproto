#pragma once
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "../serialize.h"
#include "../simple-file-read-writer/FileReadWriter.hpp"
#include "../error.h"

namespace fts {


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
    struct RequestPacket clientRequest;
    const char * errorMessage;

    

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
            errorMessage = FAILED_TO_CREATE_SOCKET;
            return false;
        }

        return createAndBindServerAddress(&servaddr);
    }


    //read from server, then write to client
    inline int writeToClient(char *filename){

        
        struct FileReadPacket rw_packet;

        unsigned char buffer[sizeof(rw_packet)];
		bzero(buffer, sizeof(buffer)); 

        read(connfd, buffer, sizeof(buffer));

        
        frw = new FileReadWriter(filename, READ);
        if(frw->Open() < 0){
            return -1; // TODO add error to file packet to speficy error message
        }


		// read the message from client and copy it in buffer
		read(connfd, buff, sizeof(struct FilePacket));
        
        deserialize_file_packet(buff, &packet);
    

        

      
        if ((packet.bytes_rw = frw->ReadFromFile(packet.data, sizeof(packet.data), packet.offset)) < 0 ){
            errorMessage = FAILED_TO_READ_FROM_FILE;
            return -1;
        }
        
        unsigned char buffer[sizeof(struct FilePacket)];  //buffer will point to the start of the array of data bytes to be written and is where data is stored
        unsigned char *ptr; //ptr will point to the end of the array of data bytes to be written 

        ptr = serialize_file_packet(buffer, &packet);
        return WriteToClient(&packet);
       
    }

 
    inline int checkFileForRead(char * filename, struct ResponsePacket *response){
        if (access(filename, F_OK) == 0) {
            response->status = access(filename, R_OK) == 0 ? OK : PERMISION_DENIED;
        }
        else {
            response->status = FILE_NOT_FOUND;
        }
    }    

    inline int checkFileForWrite(char * filename, struct ResponsePacket *response){
        response->status = access(filename, W_OK) == 0 ? OK : PERMISION_DENIED;
    }
      

    
    inline bool handleClientRequst(struct ResponsePacket *response){

        struct ResponsePacket response;
        unsigned char buffer[get_size_of_request_packet(&clientRequest)];
        unsigned char * ptr;
        
        if (read(connfd, buffer, sizeof(buffer))) {
            return false;
        }

        deserialize_request_packet(buffer, &clientRequest);
        if (clientRequest.mode == READ) {
             checkFileForRead(clientRequest.filename, response);
        } 
        else {
             checkFileForWrite(clientRequest.filename, response);

        }

        bzero(&buffer, sizeof(buffer));
        ptr = serialize_response_packet(buffer, response);
        if (write_serialized_data(connfd, buffer, ptr) < 0) {
            errorMessage = FAILED_TO_WRITE_TO_CLIENT_SOCKET;
            return false;
        }

        return true;
    }

    public:

    // ServerPort represent the server the 
    FileServer(int port): port(port){}

    // Connect connects the client to the specific server
    bool StartServer(int connections);

    bool Accept(){
        if(!isRunning){
            errorMessage = SERVER_NOT_RUNNING;
            return false;
        }

        struct sockaddr_in client;
        int len = sizeof(client);
        connfd = accept(sockfd, (struct sockaddr*)&client, (socklen_t *) &len);
        
        struct ResponsePacket response;

        if(!handleClientRequst(&response)) {
            errorMessage = FAILED_TO_READ_CLIENT_REQUEST;
            return false;
        }
        if(response.status == OK){
            if(clientRequest.mode == READ){
                writeToClient(clientRequest.filename); //read from server file and send to server
            }

        }

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

