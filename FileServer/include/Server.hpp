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
#include <sys/stat.h>
#include <string>
#include <ServerException.hpp>

using namespace packet;

//TODO find duplicated methods in Server and Client and make that method in shared class
namespace fts {

    struct ServerPort {
        char serverAddress[16];
        int port;
    };

    struct ClientRequest {
        bool create;
        unsigned char status;

        ClientRequest(bool create, unsigned char status) {
            this->create = create;
            this->status = status;
        }
    };

    // TODO if error occurs sent request back to client

    class FileServer {
        
        private:

            FileReadWriter *frw;
            int sockfd, connfd, port, fileSize;
            bool mode, isRunning;
            char filepath[MAX_FILEPATH_LENGTH], rootFolder[20]; // TODO make 20 constant
        
            // TODO be able to have protocol specificied
            inline void bindServerSocketAddress() {
                struct sockaddr_in servaddr;

                servaddr.sin_family = AF_INET;
                servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //allow all address to connect
                servaddr.sin_port = htons(port);
                if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) 
                    throw new ServerException(FAILED_TO_BIND_SERVER_SOCKET);
            }

            // createAndBindServerSocket creates the server socket and binds the socket
            inline void createAndBindServerSocket() {
                if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
                    throw new ServerException(FAILED_TO_CREATE_SERVER_SOCKET);

                bindServerSocketAddress();
            }

            // writeToClient reads from the file request by the client and writes
            inline void writeToClient() {
                FileConfigPacket fileConfigPacket(connfd);
                char buffer[fileConfigPacket.numberOfBytesToRead];
                int bytesRead = readFromFile(buffer, &fileConfigPacket);

                FilePacket filePacket(connfd, buffer, bytesRead, fileConfigPacket.offset);
                filePacket.WritePacket();
            }
            
            inline void readFromClient() {
                FilePacket packet(connfd);
                packet.ReadIntoPacket();
                writeToFile(packet.data, packet.numberOfBytesRead, packet.offset);
            }

            inline int readFromFile(char * buffer, FileConfigPacket * fileConfigPacket) {
                return frw->ReadFromFile(buffer, fileConfigPacket->numberOfBytesToRead, fileConfigPacket->offset);
            }
            inline int writeToFile(char *buffer, int bytesToWrite, int offset) {
                return frw->WriteToFile(buffer, bytesToWrite, offset); 
            }
        
            // openFile opens the file for reading or writing
            inline void openFile(bool create = false) {
                frw = new FileReadWriter(filepath, mode, fileSize);
                frw->Open(create);
            }

            //handleClientRequest reads the clients request
            inline ClientRequest handleClientRequest(){
                
                RequestPacket requestPacket(connfd);
                requestPacket.ReadIntoPacket();

                this->mode = requestPacket.mode;

                // TODO convert c type strings to c++
                sprintf(this->filepath, "%s%s",this->rootFolder, requestPacket.filepath);

                ResponsePacket responsePacket(connfd);
                    

                responsePacket.status = FileReadWriter::CheckFile(requestPacket.filepath, requestPacket.mode);
                
                if (responsePacket.status == OK ) {

                    if (mode == WRITE) {
                        this->fileSize = requestPacket.fileSize;
                    }
                    else if (mode == READ) {
                        responsePacket.fileSize = FileReadWriter::GetFileSize(requestPacket.filepath);
                    }
                }
                
                responsePacket.WritePacket();
                struct ClientRequest clientRequest(requestPacket.createFile, responsePacket.status);

                return clientRequest;
            }
            
            inline void process(){
                mode == WRITE ? readFromClient(): writeToClient();
            }

        public:

        // ServerPort represent the server the 
        FileServer(int port, const char * rootFolder = ""): port(port), fileSize(-1){ 
            strncpy(this->rootFolder, rootFolder, sizeof(this->rootFolder));
        }

        ~FileServer() {
            delete frw;
            frw = NULL;
        }

        // StartServer
        void StartServer(int connections);

        bool Accept();

        int GetFileSize();

        void Close();

    };

};

