#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "../header/http.h"
#include "../header/utils.h"


static void init_request(Request *req, char *buffer, size_t size){
  req->method = strtok(buffer, " ");
  req->url = strtok(NULL, " ");

  while (1) {
    char *line = strtok(NULL, "\r\n");
    if (line == NULL || strlen(line) == 0) {
      break;
    }
    if (strstr(line, "Content-Length:") != NULL) {
      req->body = strtrim(strtok(NULL, ""));
      char *content_length = strtok(line, " ");
      printf("%s\n", content_length);
    }
  }
}


void http_sendFile(Response *res, const char *filepath) {

  int file_fd = open(filepath, O_RDONLY);
  if (file_fd == -1) {
    perror("Failed to open HTML file");
    res->status_code = 404;
    const char *not_found_response =
        "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\nConnection: "
        "close\r\n\r\n";
    send(res->fd, not_found_response, strlen(not_found_response), 0);
    return;
  }

  char buffer[1024];
  memset(buffer, 0, sizeof(buffer));

  off_t file_size = lseek(file_fd, 0, SEEK_END);
  lseek(file_fd, 0, SEEK_SET);

  snprintf(buffer, sizeof(buffer),
           "HTTP/1.1 %u OK\r\n"
           "Content-Type: text/html\r\n"
           "Content-Length: %ld\r\n"
           "Connection: close\r\n\r\n",
           res->status_code ? res->status_code : 200, file_size);

  send(res->fd, buffer, strlen(buffer), 0);

  ssize_t bytes_read;
  while ((bytes_read = read(file_fd, buffer, sizeof(buffer))) > 0) {
    send(res->fd, buffer, bytes_read, 0);
  }

  close(file_fd);
}

void http_send(Response *res, char *buffer, size_t size) {

  char *header = malloc(1024);
  memset(header,0,1024);

  snprintf(header, (size_t)1024,
           "HTTP/1.1 %u OK\r\n"
           "Content-Type: application/json\r\n"
           "Content-Length: %ld\r\n",
           res->status_code ? res->status_code : 200, size);

  send(res->fd, header, strlen(header), 0);
  send(res->fd, buffer, size, 0);
}

void start_server(uint32_t PORT, callback func) {
  int serverfd = socket(AF_INET, SOCK_STREAM, 0);
  if (serverfd == -1) {
    perror("Socket creation failed");
    exit(1);
  }

  struct sockaddr_in address, client_addr;
  address.sin_family = AF_INET;
  address.sin_port = htons(PORT);
  address.sin_addr.s_addr = INADDR_ANY;

  if (bind(serverfd, (struct sockaddr *)&address, sizeof(address)) == -1) {
    perror("Binding failed");
    close(serverfd);
    exit(1);
  }

  if (listen(serverfd, 10) == -1) {
    perror("Listen failed");
    close(serverfd);
    exit(1);
  }

  printf("Server is listening on http://localhost:%u\n", PORT);

  socklen_t clientLen = sizeof(client_addr);

  while (1) {
    int clientfd =
        accept(serverfd, (struct sockaddr *)&client_addr, &clientLen);
    if (clientfd == -1) {
      perror("Accept failed");
      continue;
    }

    printf("Client connected\n");

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    ssize_t bytes_read = read(clientfd, buffer, sizeof(buffer) - 1);
    if (bytes_read <= 0) {
      perror("Read failed");
      close(clientfd);
      continue;
    }
    buffer[bytes_read] = '\0';


    Request *req = malloc(sizeof(Request));
    if (!req) {
      perror("Memory allocation failed");
      close(clientfd);
      continue;
    }

    init_request(req,buffer,bytes_read);

    Response *res = malloc(sizeof(Response));
    if (!res) {
      perror("Memory allocation failed");
      free(req->method);
      free(req->url);
      free(req);
      close(clientfd);
      continue;
    }
    res->fd = clientfd;

    func(req, res);

    // Cleanup
    free(req);
    free(res);
    close(clientfd);
  }
}
