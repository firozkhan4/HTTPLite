#ifndef HTTP_H
#define HTTP_H

#include <stdint.h>
#include <stdlib.h>


struct Request {
  uint16_t fd;
  char *method;
  char *url;
  char *body;
};

struct Response {
  uint16_t fd;
  uint32_t status_code;
};

typedef struct Request Request;
typedef struct Response Response;

typedef void (*callback)(Request *, Response *);

void http_sendFile(Response *res, const char *filepath);
void http_send(Response *res, char *buffer, size_t size); 
void start_server(uint32_t PORT, callback func); 
#endif
