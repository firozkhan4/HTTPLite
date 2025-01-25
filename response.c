#include "include/response.h"

void set_status(HTTPResponse *res, uint16_t code){
    if(code < 100 || code > 599){
        printf("Invalid Status Code!\n");
        exit(EXIT_FAILURE);
    }
    res->status = code;
}

void httpsend(HTTPResponse *res, HTTPRequest *req){
   send(req->fd, res->to_string(res), strlen(res->to_string(res)), 0); 
}

char *to_string(HTTPResponse *res){
    return "hello";
}

