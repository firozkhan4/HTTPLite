#include "./http.c"
#include <stdio.h>
#include <string.h>

void handleHome(Request *req, Response *res) {
  if(strcmp("GET", req->method) == 0 && strcmp("/", req->url) == 0){
    char data[] = "Hello, World\n";
    http_send(res,data, sizeof(data));
  }
}

int main() {
  start_server(8000,handleHome);
  return 0;
}
