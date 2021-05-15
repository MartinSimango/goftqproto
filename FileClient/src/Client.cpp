#include <Client.hpp>
#include <Requests.hpp>
#include <Responses.hpp>

using namespace ftc;

void FileClient::Connect(struct ServerPort serverPort) {
    if (isConnected)
        throw new ClientException(CLIENT_ALREADY_CONNECTED);
    
    connectToServer(serverPort);
    isConnected = true;
}


GetResponse FileClient::SendGetRequest(char * filepath){
    if (!isConnected)
        throw new ClientException(CLIENT_NOT_CONNECTED);

    GetRequest req(sockfd, filepath);
    GetResponse response(sockfd);

    req.Write();
    return response;
}

CreateResponse FileClient::SendCreateRequest(std::vector<request::File> * files) {
    if (!isConnected)
        throw new ClientException(CLIENT_NOT_CONNECTED);

    CreateRequest request(sockfd, files);
    CreateResponse response(sockfd);

    request.Write();
    response.Read();

    std::cout << "FILENUM?: frepposne" << response.numFiles << std::endl;

    //todo rather call Read within the response constructor in order to not expose the read method one the response is returned
    return response;
}

ReadResponse FileClient::SendReadRequest(int numberOfBytesToRead, int offset, char *readFile, char * writeFile) {
    if (!isConnected)
        throw new ClientException(CLIENT_NOT_CONNECTED);
    
    ReadRequest request(sockfd, readFile, offset, numberOfBytesToRead);
    ReadResponse response(sockfd);

    request.Write();
    response.Read();

    FileReadWriter frw(writeFile, Mode::WRITE);
    frw.Open();
    frw.WriteToFile(response.data, response.numberOfBytesRead, offset);
    frw.Close();

    return response;
}

WriteResponse FileClient::SendWriteRequest(int numberOfBytesToWrite, int offset, char *readFile, char * writeFile) {
    if (!isConnected)
        throw new ClientException(CLIENT_NOT_CONNECTED);

    FileReadWriter frw(readFile, Mode::READ);
    frw.Open();
    int bytes_written = writeToServer(&frw, writeFile, numberOfBytesToWrite, offset);
    frw.Close();

    WriteResponse response(sockfd);
    response.Read();

    return response;
}


void FileClient::Close() {
    if (!isConnected)
        throw new ClientException(CLIENT_NOT_CONNECTED);
    if (close(sockfd) < 0) 
        throw new ClientException(FAILED_TO_CLOSE_CLIENT_SOCKET);

    isConnected = false;
}