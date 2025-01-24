#include "include/httplite.h"
#include "server.c"
#include <stdio.h>
#include <stdlib.h>

void httplisten(unsigned int PORT, Callback callback) {
  Server *ser = malloc(sizeof(Server));
  start_server(PORT, ser);
  callback(NULL, NULL);
}

void hello(HTTPRequest *req, HTTPResponse *res) { printf("Hello world!\n"); }

int main() {
  HTTPLite *http = malloc(sizeof(HTTPLite));
  http->httplisten = httplisten;

  http->httplisten(8000, hello);
  return 0;
}


void get(const char *path,Callback *callback){
     
}
