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

namespace ftc {


    struct ServerPort {
        char * serverAddress;
        int port;
    };


    class FileClient {
        
        private:

        struct ServerPort * serverPort;
        struct RequestPacket requestPacket;
        bool isConnected;
        int sockfd;
        const char * errorMessage;
        FileReadWriter *frw;
        

        // TODO be able to have protocol specificied

        // connectToServer to the connects to the server specified by serverPort
        inline bool connectToServer(){
            
            struct sockaddr_in servaddr;

            if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
                errorMessage = FAILED_TO_CREATE_SOCKET;
                return false;
            }

            bzero(&servaddr, sizeof(servaddr));
            servaddr.sin_family = AF_INET;
            servaddr.sin_addr.s_addr = inet_addr(serverPort->serverAddress);
            servaddr.sin_port = htons(serverPort->port);
            
            if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
                errorMessage = FAILED_TO_CONNECT_TO_SERVER;
                return false;
            }
        
            return true;
        }
        // requestToServer makes a request to the server to see if it can read or write to the server
        inline bool requestToServer(){
            
            struct ResponsePacket responsePacket;

            write_serialized_request_packet
            bzero(&buffer, sizeof(buffer));

            //read back what server says
            read(sockfd, buffer, sizeof(struct ResponsePacket));

            deserialize_response_packet(buffer, &responsePacket);

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

        inline int readFromFile(char * buffer, struct FileReadPacket *readPacket) {
            return frw->ReadFromFile(buffer, readPacket->numberOfBytesToRead, readPacket->offset);
        }
        inline int writeToFile(char *buffer, struct FileReadPacket *writePacket) {
            return frw->WriteToFile(buffer, sizeof(buffer), writePacket->offset); 
        }

         // writeToServer writes to the server and reads from the client, returns false upon failure
        inline bool writeToServer(struct FileReadPacket *readPacket){

            char dataRead[readPacket->numberOfBytesToRead];
            int numberOfBytesRead;

            if ( (numberOfBytesRead = readFromFile(dataRead, readPacket) ) < 0)  {
                return false;
            }

            //TODO accomdate for when data is finished being raed

            struct FilePacket packet(dataRead, readPacket->offset, numberOfBytesRead);

            if (write_serialized_file_packet(sockfd, &packet) < 0) {
                return false;
            }

            // TODO add check for when server responds
            return true;
        }
        
        // ReadFromServer reads from the server and writes to the client, returns false upon failure

        inline bool FileClient::readFromServer(struct FileReadPacket * readPacket){

            //write to server to tell where to start getting data from
            if(write_serialized_file_read_packet(sockfd, readPacket) < 0){
                return false;
            }
    
            struct FilePacket packet;
            if(read_and_deserialize_file_packet(sockfd, &packet) < 0) {
                return false;
            }


            return writeToFile(packet.data, readPacket);        

        }

        public:

        // if writing to server filename will be file we want to read from
        // if reading from server filename will be file we want to write to
        FileClient(struct RequestPacket requestPacket, char * filename = nullptr): errorMessage(nullptr), requestPacket(requestPacket) {
            frw = new FileReadWriter( (!filename) ? requestPacket.filename : filename, !requestPacket.mode); // ! request.mode because if you are writing to server you are reading from client
           
        }

        ~FileClient() {
            if (frw) {
                delete frw;
            }
        }
        // Connect connects the client to the specific server specified by the ServerPort 
        // returns false if connect failed and errorMessage is set
        bool Connect(struct ServerPort *serverPort);
        
        // Process either reads or writes to the server depending on what mode the FileClient is in
        bool Process(struct FileReadPacket * packet);

        // GetErrorMessge returns the errorMessage 
        const char * GetErrorMessage() const;
        
        // Close closes the connection to the server, returns false upon failure
        bool Close();
    };




};

