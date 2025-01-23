#include <stdio.h>
#include <stdlib.h>
#include "httplite.h"

void listen(unsigned int PORT, Callback callback){
    printf("Server is running on PORT:%d\n",PORT);
    callback(NULL,NULL);
}


void hello(HTTPRequest *req, HTTPResponse *res){
    printf("Hello world!\n");
}

int main(){
    HTTPLite *http = malloc(sizeof(HTTPLite));
    http->listen = listen;

    http->listen(8000,hello);
    return 0;
}
