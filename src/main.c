#include <stdio.h>      // For printf and fprintf
#include <sys/socket.h> // For socket creation
#include <netinet/in.h> // For sockaddr_in
#include <unistd.h>     // For close
#include <string.h>     // For memset

#define PORT 8080

int main() {
    int server_fd, new_socket;                      // Socket file descriptors
    struct sockaddr_in address;                     // Address structure for the server
    int addr_len = sizeof(address);
    char buffer[1024] = {0};                        // Buffer to read the incoming message
    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return -1;
    }

    // Bind the socket to the specified port 8080
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        return -1;
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        return -1;
    }

    // Accept an incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addr_len))<0) {
        perror("accept");
        return -1;
    }

    // Read the message from client and send a response
    read(new_socket, buffer, 1024);
    printf("%s\n",buffer);
    send(new_socket, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    // Close the socket
    close(new_socket);
    close(server_fd);

    return 0;
}
