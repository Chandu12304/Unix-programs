#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

const int PORT = 8080;

int main() {
    // Create a socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Socket creation failed!" << std::endl;
        return 1;
    }

    // Define the server address
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        std::cerr << "Binding failed!" << std::endl;
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1) {
        std::cerr << "Listening failed!" << std::endl;
        return 1;
    }

    std::cout << "Server is running on port " << PORT << std::endl;

    // Accept a client connection
    int client_socket = accept(server_socket, nullptr, nullptr);
    if (client_socket == -1) {
        std::cerr << "Connection failed!" << std::endl;
        return 1;
    }

    // Send a simple HTML response
    const char* response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
                           "<html><body><h1>Hello, World!</h1></body></html>";
    send(client_socket, response, strlen(response), 0);

    // Close the client and server sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
