#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <errno.h>

#define SOCKET_PATH "/tmp/my_socket"

int main() {
    int server_fd, client_fd;
    struct sockaddr_un addr;
    char buffer[100];
    unlink(SOCKET_PATH);
    // Create a Unix domain socket
    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Define the address of the socket
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    // Bind the socket to the address
    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 5) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening...\n");
    // Accept a connection from a client
    client_fd = accept(server_fd, NULL, NULL);
    if (client_fd < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("client connected\n");
    // Read data from the client

    while(1) {
    ssize_t num_bytes = read(client_fd, buffer, sizeof(buffer) - 1);
    if (num_bytes < 0) {
        perror("read");
        close(client_fd);
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    else if(num_bytes==0){
		    printf("Client disconnected\n");
		    break;}
    buffer[num_bytes]='\0';

    printf("Received: %s\n", buffer);
    if (buffer[num_bytes] == 'q'){ // Null-terminate the string
    printf("terminating connection");
    break;}
	}
    // Clean up
    close(client_fd);
    close(server_fd);
    unlink(SOCKET_PATH); // Remove the socket file

    return 0;
}

