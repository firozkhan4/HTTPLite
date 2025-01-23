#ifndef HTTPLITE_H
#define HTTPLITE_H

typedef struct{

}HTTPRequest;

typedef struct{

}HTTPResponse;


typedef void (*Callback)(HTTPRequest *req, HTTPResponse *res);


typedef struct{

    void (*listen)(unsigned int PORT, Callback callback);

}HTTPLite;


#endif
