#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#define SOCKET_PATH "/tmp/my_socket"
#define BUF_SIZE 256
int main() {
    int client_fd;
    struct sockaddr_un addr;
    //coinst char *message = "Hello, Unix domain socket!";
    char buffer[BUF_SIZE];
    // Create a Unix domain socket
    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Define the address of the socket
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    // Connect to the server
    if (connect(client_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("connect");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    // Send a message to the server
    while(true){

    if(fgets(buffer,sizeof(buffer),stdin)==NULL){
	perror("fgets");
	close(client_fd);
	exit(EXIT_FAILURE);}
   
    if(buffer[0]=='q') break; 

    if (write(client_fd, buffer, strlen(buffer)) < 0) {
        perror("write");
        close(client_fd);
        exit(EXIT_FAILURE);}

   }
    


    // Clean up
    close(client_fd);

    return 0;
}

