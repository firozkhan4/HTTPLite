#ifndef RESPONSE_H
#define RESPONSE_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "request.h"

typedef enum {
    CONTINUE = 100,
    SWITCH_PROTOCOL = 101,
    PROCESSING = 102,
    OK = 200,
    CREATED = 201,
    ACCEPTED = 202,
    BAD_REQUEST = 400,
    UNAUTHORIZED = 401,
    FORBIDDEN = 403,
    NOT_FOUND = 404,
    INTERNAL_SERVER_ERROR = 500,
    NOT_IMPLEMENTED = 501
} StatusCode;


typedef struct HTTPResponse{
    uint16_t status;

    // Methods
    char* (*to_string)(struct HTTPResponse *self);
}HTTPResponse;


#endif
