#include <string.h>
#include <stdio.h>
#include "../header/http.h"

void handleHome(Request *req, Response *res) {
  if(strcmp("POST", req->method) == 0 && strcmp("/", req->url) == 0){
    char *data = "Hello World!";
    printf("%ld\n%s\n",strlen(req->body),req->body);
    http_send(res,data, strlen(data));
  }
}

int main() {
  start_server(8000,handleHome);
  return 0;
}
