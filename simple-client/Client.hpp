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
#include "../error.h"

namespace ftc {


    struct ServerPort {
        char * serverAddress;
        int port;
    };


    class FileClient {
        
        private:

        struct ServerPort * serverPort;
        bool isConnected;
        int sockfd;
        const char * errorMessage;
        

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
        inline bool requestToServer(bool mode, char * filepath){
            
            struct RequestPacket requestPacket;
            struct ResponsePacket responsePacket;


            requestPacket.mode = mode;
            strcpy(requestPacket.filename, filepath);

            unsigned char buffer[get_size_of_request_packet(&requestPacket)];
            unsigned char *ptr;

            serialize_request_packet(buffer ,&requestPacket);
            if (write_serialized_data(sockfd, buffer, ptr) < 0) {
                return false;
            }
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

        public:

        FileClient(): errorMessage(nullptr) {}
        // Connect connects the client to the specific server specified by the ServerPort 
        // returns false if connect failed and errorMessage is set
        bool Connect(struct ServerPort *serverPort);
        
        // WriteToServer writes to the server and reads from the client, returns false upon failure
        bool WriteToServer(struct FileReadWritePacket * readPacket, char * serverFileName);
        
        // ReadFromServer reads from the server and writes to the client, returns false upon failure
        bool ReadFromServer(struct FileReadWritePacket * writePacket, char * serverFileName);

        // GetErrorMessge returns the errorMessage 
        const char * GetErrorMessage() const;
        
        // Close closes the connection to the server, returns false upon failure
        bool Close();
    };




};

