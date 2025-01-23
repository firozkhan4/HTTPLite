#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>

typedef struct{
    unsigned int PORT;
    int socketfd;
}Server;

void start_server(unsigned int PORT,Server *server){

    server->socketfd = socket(AF_INET, SOCK_STREAM, 0);
    server->PORT = PORT;
    
    if(server->socketfd < 0){
        perror("open");
        exit(EXIT_FAILURE);
    }



}
