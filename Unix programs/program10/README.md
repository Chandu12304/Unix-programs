This simple C++ web server program allows a basic understanding of how a web server works. Here's a step-by-step explanation of the theory behind it.

### Theory:
This program is a basic web server that listens on a port (8080) for incoming connections, accepts a connection from a client (like a browser), and sends back a simple HTML "Hello, World!" message. It demonstrates how to create a socket, bind it to an address, listen for connections, accept a connection, and send a response.

---

### 1. **What is a Web Server?**
A web server is a program that listens for requests from clients (like web browsers) and responds by sending them some content, like an HTML webpage. This program is a minimal web server that responds with a simple HTML message ("Hello, World!") when a client connects to it.

### 2. **Key Concepts Used in the Program**
- **Socket**: A socket is a way to establish a connection between two devices (your server and the client). Think of it like a phone call where both parties (server and client) can send and receive messages.
- **Port**: A port is like a door that helps the server listen for incoming connections. In this program, we are using port `8080`, which is a common port for local servers.
- **Client-Server Communication**: The client (e.g., a browser) sends a request to the server, and the server responds with some data (in our case, a webpage).

### 3. **How the Program Works**

#### **Step 1: Create a Socket**
```cpp
int server_socket = socket(AF_INET, SOCK_STREAM, 0);
```
- This creates a communication endpoint, called a socket. It’s like opening a line for communication. 
- `AF_INET`: This means we’re using the Internet protocol (IPv4).
- `SOCK_STREAM`: We want a reliable connection using TCP (Transmission Control Protocol), which ensures that data is sent and received in the right order.

#### **Step 2: Bind the Socket to an Address**
```cpp
bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));
```
- This step assigns the socket to a specific IP address and port (in this case, port 8080). 
- Think of this as making your server "listen" on a specific door (the port) for incoming requests.

#### **Step 3: Listen for Incoming Connections**
```cpp
listen(server_socket, 5);
```
- The server now waits for a client to connect. It's like the server saying, "I'm ready to accept up to 5 client connections at a time."

#### **Step 4: Accept a Client Connection**
```cpp
int client_socket = accept(server_socket, nullptr, nullptr);
```
- When a client (like a web browser) tries to connect, this line accepts the connection. It’s like answering the phone when someone calls.

#### **Step 5: Send a Response to the Client**
```cpp
send(client_socket, response, strlen(response), 0);
```
- After accepting the connection, the server sends a response. In this case, it's sending an HTTP response containing a simple HTML message ("Hello, World!").
- HTTP is the protocol used by web servers and browsers to communicate.

#### **Step 6: Close the Connection**
```cpp
close(client_socket);
close(server_socket);
```
- Once the message is sent, the connection is closed, which is like hanging up the phone.
### 4. **What Happens When You Run the Program?**
- When you run the server, it starts listening for incoming connections.
- If you open a browser and go to `http://localhost:8080`, the browser connects to the server.
- The server sends a simple HTML page to the browser with the message "Hello, World!".
- After sending the message, the server closes the connection.

---


### Code Explanation:

```cpp
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
```
- These are header files:
  - `iostream` is for input and output (like `std::cout` for printing).
  - `cstring` is for string manipulation functions like `strlen`.
  - `unistd.h` provides access to the POSIX operating system API, which includes `close()`.
  - `sys/socket.h` is for working with sockets (a way to communicate between computers).
  - `netinet/in.h` contains structures for handling IP addresses.

---

```cpp
const int PORT = 8080;
```
- This defines the port number where the server will listen for incoming connections. Port 8080 is often used for web services.

---

```cpp
int server_socket = socket(AF_INET, SOCK_STREAM, 0);
```
- `socket(AF_INET, SOCK_STREAM, 0)` creates a **TCP** socket using the **IPv4** protocol. It returns a socket file descriptor (`server_socket`), which is used to identify the socket.
  - `AF_INET`: IPv4 protocol.
  - `SOCK_STREAM`: TCP connection.
  - `0`: Automatically select the correct protocol (TCP in this case).

---

```cpp
if (server_socket == -1) {
    std::cerr << "Socket creation failed!" << std::endl;
    return 1;
}
```
- This checks if the socket was successfully created. If it failed (returned `-1`), an error message is printed, and the program exits.

---

```cpp
sockaddr_in server_address{};
server_address.sin_family = AF_INET;
server_address.sin_addr.s_addr = INADDR_ANY;
server_address.sin_port = htons(PORT);
```
- **`sockaddr_in`** is a structure used to specify the address and port the server will use.
  - `sin_family = AF_INET`: Uses the IPv4 address family.
  - `sin_addr.s_addr = INADDR_ANY`: Binds the socket to all available network interfaces (like Wi-Fi, Ethernet).
  - `sin_port = htons(PORT)`: Converts the port number to the correct format using `htons()`.

---

```cpp
if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
    std::cerr << "Binding failed!" << std::endl;
    return 1;
}
```
- **`bind()`** attaches the socket (`server_socket`) to the specified address (`server_address`) and port (`8080`).
  - If binding fails, it prints an error and exits.

---

```cpp
if (listen(server_socket, 5) == -1) {
    std::cerr << "Listening failed!" << std::endl;
    return 1;
}
```
- **`listen()`** puts the socket in a listening state, ready to accept incoming connections.
  - `5` is the maximum number of pending connections allowed in the queue.
  - If listening fails, an error message is shown, and the program exits.

---

```cpp
std::cout << "Server is running on port " << PORT << std::endl;
```
- This simply prints a message indicating that the server is up and running on port 8080.

---

```cpp
int client_socket = accept(server_socket, nullptr, nullptr);
```
- **`accept()`** waits for a client (like a browser) to connect. When a client connects, it returns a new socket file descriptor (`client_socket`) to communicate with the client.
  - The two `nullptr`s mean we're not interested in getting the client's address information.
  - If `accept()` fails, an error message is printed.

---

```cpp
const char* response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
                       "<html><body><h1>Hello, World!</h1></body></html>";
```
- This is the **HTTP response** the server will send to the client:
  - `"HTTP/1.1 200 OK"`: HTTP protocol version and status code 200 (successful).
  - `"Content-Type: text/html"`: Specifies that the response contains HTML content.
  - `"<!DOCTYPE html>...`" is the actual HTML content displayed by the client (a simple webpage with "Hello, World!").

---

```cpp
send(client_socket, response, strlen(response), 0);
```
- **`send()`** sends the response to the connected client through `client_socket`.
  - `response`: The content to be sent.
  - `strlen(response)`: The length of the content.
  - `0`: No special flags are used here.

---

```cpp
close(client_socket);
close(server_socket);
```
- **`close()`** closes the connections:
  - `client_socket`: Ends the connection with the client after sending the response.
  - `server_socket`: Shuts down the server after the program ends.
