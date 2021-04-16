#pragma once

#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <Packets.hpp>
#include <FileReadWriter.hpp>
#include <Error.h>
#include <sys/stat.h>

using namespace packet;

//TODO find duplicated methods in Server and Client and make that method in shared class
namespace fts {

    struct ServerPort {
        char * serverAddress;
        int port;
    };

    // TODO if error occurs sent request back to client

    class FileServer {
        
        private:
        FileReadWriter *frw;
        bool isRunning;
        int sockfd;
        int connfd;
        int port;
        bool mode;
        char filepath[MAX_FILEPATH_LENGTH];
        const char * errorMessage;
        int fileSize;

        

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
        inline int writeToClient(){
            FileConfigPacket fileConfigPacket(connfd);
            char buffer[fileConfigPacket.numberOfBytesToRead];
            int bytesRead = readFromFile(buffer, &fileConfigPacket);

            FilePacket filePacket(connfd, buffer, bytesRead, fileConfigPacket.offset);
            return filePacket.WritePacket();
        }
        
        inline int readFromClient(){
            FilePacket packet(connfd);
            packet.ReadIntoPacket();
            return writeToFile(packet.data, packet.numberOfBytesRead, packet.offset);
        }

        inline int readFromFile(char * buffer, FileConfigPacket * fileConfigPacket) {
            return frw->ReadFromFile(buffer, fileConfigPacket->numberOfBytesToRead, fileConfigPacket->offset);
        }
        inline int writeToFile(char *buffer, int bytesToWrite, int offset) {
            return frw->WriteToFile(buffer, bytesToWrite, offset); 
        }
    
        inline unsigned char checkFileForRead(char * filename){
            if (access(filename, F_OK) == 0) {
                return access(filename, R_OK) == 0 ? OK : NO_READ_PERMISSIONS;
            }
            else {
                return FILE_NOT_FOUND;
            }
        }    

        inline unsigned char checkFileForWrite(char * filename){
            if (access(filename, F_OK) == 0) {
                return access(filename, W_OK) == 0 ? OK : NO_WRITE_PERMISIONS;
            }
            return OK;
        }
        
        inline int getFileSize(char *filename){
            if (mode == READ){
                return 0;
            }
            struct stat st;
            char localFile[MAX_FILEPATH_LENGTH];
            strcpy(localFile, filename);
            if(stat(localFile, &st) != 0) {
                return 0;
            }
            return st.st_size;
        }
        // openFile opens the file for reading or writing
        inline bool openFile(){
            frw = new FileReadWriter(filepath, mode, fileSize);
            if (!frw->Open()) {
                errorMessage = FAILED_TO_OPEN_FILE;
                return false;
            }
            
            return true;
        }
        inline bool handleClientRequest(){

            RequestPacket requestPacket(connfd);
            requestPacket.ReadIntoPacket();

            this->mode = requestPacket.mode;
            strcpy(this->filepath, requestPacket.filepath); // TODO rather use strlcpy

            ResponsePacket responsePacket(connfd);
                  
            if(mode == WRITE) {
                this->fileSize = requestPacket.fileSize;
            }
            else if(mode == READ){
                responsePacket.fileSize = getFileSize(this->filepath);
            }


            responsePacket.status = (requestPacket.mode == READ) ? checkFileForRead(requestPacket.filepath)
                                                                : checkFileForWrite(requestPacket.filepath);

            return responsePacket.WritePacket() >= 0 && responsePacket.status == OK;
        }
        
        inline bool process(){
            return mode == WRITE ? readFromClient() >= 0: writeToClient() >= 0;
        }

        public:

        // ServerPort represent the server the 
        FileServer(int port): port(port){ 
            fileSize = 0;
        }

        ~FileServer() {
            if (frw) {
                delete frw;
            }
        }

        // Connect connects the client to the specific server
        bool StartServer(int connections);

        bool Accept();
        // writeToServer writes to the server

        bool Close();

        const char * getErrorMessage() { return errorMessage; }
    };




};

