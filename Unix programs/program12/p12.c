// server.cpp

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);
    
    bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 1);
    
    std::cout << "Waiting for connection..." << std::endl;

    int clientSocket = accept(serverSocket, nullptr, nullptr);
    
    char buffer[1024] = {0};
    recv(clientSocket, buffer, 1024, 0);
    std::cout << "Received: " << buffer << std::endl;
    
    close(clientSocket);
    close(serverSocket);

    return 0;
}

// client.cpp


#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
    
    connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    
    const char* message = "Hello from client";
    send(clientSocket, message, strlen(message), 0);
    
    close(clientSocket);

    return 0;
}
