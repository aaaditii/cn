#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];
    int bytes_received;

    // Create socket file descriptor
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Setup address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // Listen for connections
    listen(server_fd, 3);

    printf("Server is waiting for a connection...\n");

    // Accept a connection
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    // Open file to write the incoming data
    int file = open("received_file.txt", O_WRONLY | O_CREAT, 0666);
    if (file < 0) {
        perror("File open error");
        exit(EXIT_FAILURE);
    }

    // Receive data and write to file
    while ((bytes_received = read(new_socket, buffer, BUFFER_SIZE)) > 0) {
        write(file, buffer, bytes_received);
    }

    printf("File received successfully.\n");

    close(file);
    close(new_socket);
    close(server_fd);

    return 0;
}
