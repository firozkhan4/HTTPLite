#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include "include/httplite.h"

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


   struct sockaddr_in address, client;
    socklen_t client_len = sizeof(client);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if(bind(server->socketfd,(struct sockaddr*)&address,sizeof(address)) < 0){
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if(listen(server->socketfd, 5) < 0){
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    char buffer[1024] = {0};

    while(1){

        int clientfd = accept(server->socketfd,(struct sockaddr*)&client,&client_len);

        if(clientfd < 0){
            perror("Accept failed\n");
            close(server->socketfd);
            exit(EXIT_FAILURE);
        }

        const char* http_accept = 
            "HTTP/1.1 200\r\nDate: Fri, 24 Jan 2025 15:00:00 GMT\r\nContent-Type: text/html\r\nContent-Length: 42\r\nConnection: keep-alive\r\n\r\n<html><body>Hello, World!</body></html>\r\n";

        handle_client(clientfd);

    }


    close(server->socketfd);
}


