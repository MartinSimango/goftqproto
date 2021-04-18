#pragma once
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <Error.h>
#include <FileReadWriter.hpp>
#include <Packets.hpp>

using namespace packet;
namespace ftc {


    struct ServerPort {
        char serverAddress[16];
        int port;
    };


    class FileClient {
        
        private:
        bool isConnected;
        bool mode;
        int sockfd;
        const char * errorMessage;
        char requestFileName[MAX_FILEPATH_LENGTH];
        FileReadWriter *frw;

        

        // TODO be able to have protocol specificied

        // connectToServer to the connects to the server specified by serverPort
        inline bool connectToServer(struct ServerPort serverPort){
            
            struct sockaddr_in servaddr;

            if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
                errorMessage = FAILED_TO_CREATE_SOCKET;
                return false;
            }

            bzero(&servaddr, sizeof(servaddr));
            servaddr.sin_family = AF_INET;
            servaddr.sin_addr.s_addr = inet_addr(serverPort.serverAddress);
            servaddr.sin_port = htons(serverPort.port);
            
            if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
                errorMessage = FAILED_TO_CONNECT_TO_SERVER;
                return false;
            }
        
            return true;
            
        }

        // getWroteFileSize gets the size of the file when writing to th server
        // requestToServer makes a request to the server to see if it can read or write to the server
        inline bool requestToServer(){
            
            int fileSize = (mode == WRITE) ? FileReadWriter::getFileSize(frw->getFileName()): 0;

            RequestPacket requestPacket(sockfd, mode, requestFileName, fileSize);

            if (requestPacket.WritePacket() < 0){
                return false;
            }

            ResponsePacket responsePacket(sockfd);
            if (responsePacket.ReadIntoPacket() < 0){

                return false;
            }

            //read back what server says
            if (responsePacket.status == OK){
                return true;
            }
            //TODO accomodate for different status
            return false;

        }

        // opens the requestPacket file that you are reading from or writing to
        inline bool openFile(){
            if (!frw->Open()) {
                errorMessage = FAILED_TO_OPEN_FILE;
                return false;
            }
            return true;
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

            if ( (numberOfBytesRead = readFromFile(dataRead, fileConfigPacket) ) < 0) {
                return false;
            }
            //TODO accomdate for when data is finished being raed
            //write file packet to server
            FilePacket packet(sockfd, dataRead, numberOfBytesRead, fileConfigPacket->offset);    
            return packet.WritePacket();       
        }
        
        // ReadFromServer reads from the server and writes to the client, returns false upon failure

        inline int readFromServer(FileConfigPacket * fileConfigPacket){

            //write to server to tell where to start getting data from
            if (fileConfigPacket->WritePacket() < 0){
                return false;
            }           

            FilePacket packet(sockfd);            
            packet.ReadIntoPacket();
            //TODO accomodate for error

            return writeToFile(packet.data, packet.numberOfBytesRead, packet.offset);        
        }

        public:

        // if writing to server filename will be file we want to read from
        // if reading from server filename will be file we want to write to
        FileClient(bool mode, char * requestFileName, char * filename = nullptr): errorMessage(nullptr), mode(mode) {
            frw = new FileReadWriter( (!filename) ? requestFileName : filename, !mode); // ! request.mode because if you are writing to server you are reading from client
            strcpy(this->requestFileName, requestFileName);
        }

        ~FileClient() {
            if (frw) {
                delete frw;
            }
        }

        // Connect connects the client to the specific server specified by the ServerPort 
        // returns false if connect failed and errorMessage is set
        bool Connect(struct ServerPort serverPort);
        
        // Process either reads or writes to the server depending on what mode the FileClient is in
        // returns the number of bits written or read to the server depending on the mode
        int Process(int offset, int numberOfBytesRead);

        // GetErrorMessge returns the errorMessage 
        const char * GetErrorMessage() const;
        
        // Close closes the connection to the server, returns false upon failure
        bool Close();
    };


};

