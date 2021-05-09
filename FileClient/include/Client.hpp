#pragma once
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <FileReadWriter.hpp>
#include <ClientException.hpp>
#include <Request.hpp>

using namespace request;
using namespace request;

namespace ftc {


    struct ServerPort {
        char serverAddress[16];
        int port;
    };


    class FileClient {
        
        private:
        bool isConnected, mode;
        int sockfd, fileSize;
        const char * errorMessage;
        char requestFileName[MAX_FILEPATH_LENGTH], filename[MAX_FILEPATH_LENGTH];
    

        // TODO be able to have protocol specificied

        // connectToServer to the connects to the server specified by serverPort
        inline void connectToServer(struct ServerPort serverPort){
            
            struct sockaddr_in servaddr;

            if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
                throw new ClientException(FAILED_TO_CREATE_CLIENT_SOCKET);
            }

            bzero(&servaddr, sizeof(servaddr));
            servaddr.sin_family = AF_INET;
            servaddr.sin_addr.s_addr = inet_addr(serverPort.serverAddress);
            servaddr.sin_port = htons(serverPort.port);
            
            if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
                throw new ClientException(FAILED_TO_CONNECT_TO_SERVER);
            }
        
            
        }

        // requestToServer makes a request to the server to see if it can read or write to the server
        inline bool requestToServer(bool create = false){
            
            this->fileSize = (this->mode == WRITE) ? FileReadWriter::GetFileSize(this->filename): -1;

            RequestPacket requestPacket(sockfd, mode, requestFileName, this->fileSize, create);
            requestPacket.WriteRequest();
    

            ResponsePacket responsePacket(sockfd);
            responsePacket.ReadRequest();
            
            //read back what server says
            if (this->mode == READ){
                this->fileSize = responsePacket.fileSize;
            }

            if (responsePacket.status == OK){
                return true;
            }

            //TODO accomodate for different status
            return false;

        }

     
        inline void createFile(char *filename){

        }

      

         // writeToServer writes to the server and reads from the client, returns false upon failure
        inline int writeToServer(FileReadWriter * frw, char * filepath,int numberOfBytesToWrite, int offset) {
            char dataRead[numberOfBytesToWrite];

            int numberOfBytesRead = frw->ReadFromFile(dataRead, numberOfBytesToWrite, offset);
           
            WriteRequest writeRequest(sockfd, dataRead, offset, numberOfBytesRead, filepath);    
            writeRequest.WriteRequest(); 

            return numberOfBytesRead;
        }
        
        // ReadFromServer reads from the server and writes to the client, returns false upon failure

        inline int readFromServer(FileReadWriter * frw, char * filepath, int numberOfBytesToRead, int offset){

            //write to server to tell where to start getting data from
            //    ReadRequest(int fd, int offset, int numberOfBytesToRead):
            ReadRequest readRequest(sockfd, filepath, offset, numberOfBytesToRead);
            readRequest.WriteRequest();
            //request.ReadRequest();

           // int numberOfBytesWritten =  writeToFile(request.data, request.numberOfBytesRead, request.offset);        
        }

        public:

        // if writing to server filename will be file we want to read from
        // if reading from server filename will be file we want to write to
        FileClient() {}

        ~FileClient() {}

        // Connect connects the client to the specific server specified by the ServerPort 
        // returns false if connect failed and errorMessage is set
        void Connect(struct ServerPort serverPort);
        
        void SendCreateRequest(std::vector<request::File> * files);

        void SendGetRequest(char * filepath);

        void SendReadRequest(int numberOfBytesToRead, int offset, char *readFile, char * writeFile);

        void SendWriteRequest(int numberOfBytesToWrite, int offset, char *readFile, char * writeFile);
        
        void Send(Request * request);


        void Read(Request * request);
        // Process either reads or writes to the server depending on what mode the FileClient is in
        // returns the number of bits written or read to the server depending on the mode
        int Process(int offset, int numberOfBytesRead);

        int GetFileSize();
        
        // Close closes the connection to the server, returns false upon failure
        void Close();
    };


};

