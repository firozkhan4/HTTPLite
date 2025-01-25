#ifndef HTTPLITE_H
#define HTTPLITE_H

#include "request.h"
#include "request.h"
#include <stdint.h>

typedef void (*Callback)(HTTPRequest *req, HTTPResponse *res);


typedef struct{

    void (*httplisten)(unsigned int PORT, Callback callback);

}HTTPLite;


void handle_client(uint32_t clientfd);


#endif
