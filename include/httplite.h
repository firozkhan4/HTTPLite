#ifndef HTTPLITE_H
#define HTTPLITE_H

#include "../request.c"
typedef struct{

}HTTPResponse;


typedef void (*Callback)(HTTPRequest *req, HTTPResponse *res);


typedef struct{

    void (*httplisten)(unsigned int PORT, Callback callback);

}HTTPLite;


#endif
