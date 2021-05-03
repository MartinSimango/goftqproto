#pragma once
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <FileReadWriter.hpp>
#include <Packets.hpp>
#include <ClientException.hpp>

using namespace packet;
namespace ftc {


    struct ServerPort {
        char serverAddress[16];
        int port;
    };


    class FileClient {
        
        private:
        bool isConnected, mode;
        int sockfd;
        const char * errorMessage;
        char requestFileName[MAX_FILEPATH_LENGTH], filename[MAX_FILEPATH_LENGTH];
        FileReadWriter *frw;
    

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
            
            int fileSize = (mode == WRITE) ? FileReadWriter::GetFileSize(this->filename): -1;

            RequestPacket requestPacket(sockfd, mode, requestFileName, fileSize, create);
            requestPacket.WritePacket();
    

            ResponsePacket responsePacket(sockfd);
            responsePacket.ReadIntoPacket();

            //read back what server says
            if (responsePacket.status == OK){
                return true;
            }
            //TODO accomodate for different status
            return false;

        }

        // opens the requestPacket file that you are reading from or writing to
        inline void openFile(bool create = false){
            frw->Open(create);
        }

        inline int readFromFile(char * buffer, FileConfigPacket * fileConfigPacket) {
            return frw->ReadFromFile(buffer, fileConfigPacket->numberOfBytesToRead, fileConfigPacket->offset);
        }
        inline int writeToFile(char *buffer, int bytesToWrite, int offset) {
            return frw->WriteToFile(buffer, bytesToWrite, offset); 
        }

         // writeToServer writes to the server and reads from the client, returns false upon failure
        inline int writeToServer(FileConfigPacket *fileConfigPacket){
            char dataRead[fileConfigPacket->numberOfBytesToRead];
            int numberOfBytesRead;

            numberOfBytesRead = readFromFile(dataRead, fileConfigPacket);
            
            //TODO accomdate for when data is finished being raed
            //write file packet to server
            FilePacket packet(sockfd, dataRead, numberOfBytesRead, fileConfigPacket->offset);    
            packet.WritePacket(); 

            return numberOfBytesRead;      
        }
        
        // ReadFromServer reads from the server and writes to the client, returns false upon failure

        inline int readFromServer(FileConfigPacket * fileConfigPacket){

            //write to server to tell where to start getting data from
            fileConfigPacket->WritePacket();          

            FilePacket packet(sockfd);            
            packet.ReadIntoPacket();

            return writeToFile(packet.data, packet.numberOfBytesRead, packet.offset);        
        }

        public:

        // if writing to server filename will be file we want to read from
        // if reading from server filename will be file we want to write to
        FileClient(bool mode, char * requestFileName, char * filename): errorMessage(NULL), mode(mode) {
            frw = new FileReadWriter(filename, !mode); // ! request.mode because if you are writing to server you are reading from client
            strncpy(this->filename, filename, sizeof(this->filename));
            strncpy(this->requestFileName, requestFileName, sizeof(this->requestFileName));
        }

        ~FileClient() {
            delete frw;
            frw = NULL;
        }

        // Connect connects the client to the specific server specified by the ServerPort 
        // returns false if connect failed and errorMessage is set
        void Connect(struct ServerPort serverPort, bool create = false);
        
        // Process either reads or writes to the server depending on what mode the FileClient is in
        // returns the number of bits written or read to the server depending on the mode
        int Process(int offset, int numberOfBytesRead);

        // GetErrorMessge returns the errorMessage 
        const char * GetErrorMessage() const;
        
        // Close closes the connection to the server, returns false upon failure
        void Close();
    };


};

