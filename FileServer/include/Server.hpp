#pragma once

#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <RequestHeader.hpp>
#include <Requests.hpp>
#include <FileReadWriter.hpp>
#include <sys/stat.h>
#include <string>
#include <ServerException.hpp>
#include <Responses.hpp>
#include <sys/ioctl.h>

using namespace request;
using namespace response;
using namespace frw;

//TODO find duplicated methods in Server and Client and make that method in shared class
namespace fts {

    struct ServerPort {
        char serverAddress[16];
        int port;
    };

    // TODO if error occurs sent request back to client

    class FileServer {
        
        private:

            FileReadWriter *frw;
            int sockfd, connfd, port;
            Mode::Type mode;
            bool isRunning;
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
                ioctl(sockfd, FIONBIO, 0);
                bindServerSocketAddress();
            }    

            void handleRequest(CreateRequest* request) {
                //todo test code when this variable is not a pointer
                std::vector<request::File> * filesCreated = new std::vector<request::File>();
                 // create all the files client has requested to make
                for (int i=0; i< request->numFiles; i++) {
                    request::File file;
                    try {

                        sprintf(file.filename, "%s%s",this->rootFolder, request->files->at(i).filename);

                        file.fileSize = request->files->at(i).fileSize;

                        ResponseStatus::Type status = FileReadWriter::CheckFile(file.filename, Mode::WRITE);
                        if (status == ResponseStatus::OK) {
                            FileReadWriter::CreateFile(file.filename, file.fileSize); 
                            filesCreated->push_back(file);
                        }
                        else {
                            throw new FRWException(FAILED_TO_CREATE_FILE, file.filename);
                        }
                    }
                    catch(FRWException * e) {
                        //todo log exceptions (proper logging)
                        char message[100];
                        std::cerr << "[Server...]" << e->getErrorMessage(message) << std::endl;
                        delete e;
                    }
                }
                CreateResponse response(connfd, filesCreated);
                response.Write();
            }

            void handleRequest(GetRequest *request) {
                // todo: to implement
            }

            void handleRequest(ReadRequest *request){
                char filepath[MAX_FILEPATH_LENGTH];
                sprintf(filepath, "%s%s",this->rootFolder, request->filename);

                FileReadWriter frw(filepath, Mode::READ);
                int numberOfBytesToRead = request->numberOfBytesToRead;
                int offset = request->offset;
                char buffer[numberOfBytesToRead];

                ResponseStatus::Type status = FileReadWriter::CheckFile(filepath, Mode::READ);
                int bytesRead = 0;
                if (status == ResponseStatus::OK) {
                    frw.Open();
                    bytesRead = frw.ReadFromFile(buffer, numberOfBytesToRead, offset);
                    frw.Close();
                }

                ReadResponse response(connfd, bytesRead, buffer);
                response.Write();
            }

            void handleRequest(WriteRequest *request){
                char filepath[MAX_FILEPATH_LENGTH];
                sprintf(filepath, "%s%s",this->rootFolder, request->filepath);
                
                FileReadWriter frw(filepath, Mode::WRITE);
                int numberOfBytesToWrite = request->numberOfBytesToWrite;
                int offset = request->offset;
                
                int bytesWritten = 0;
                ResponseStatus::Type status = FileReadWriter::CheckFile(filepath, Mode::WRITE);
                if (status == ResponseStatus::OK) {
                    frw.Open();
                    bytesWritten = frw.WriteToFile(request->data, numberOfBytesToWrite, offset); 
                    frw.Close();
                }            

                WriteResponse response(connfd, bytesWritten, status);
                response.Write();

            }
            
        public:

        // ServerPort represent the server the 
        FileServer(int port, const char * rootFolder = ""): port(port) { 
            strncpy(this->rootFolder, rootFolder, sizeof(this->rootFolder));
        }

        ~FileServer() {
            delete frw;
            frw = NULL;
        }

        // StartServer
        void StartServer(int connections);

        void Accept();

        bool HandleClientRequest();

        bool IsServerRunning();

        void Close();

    };

};

