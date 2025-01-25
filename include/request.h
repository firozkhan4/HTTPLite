#ifndef REQUEST_H
#define REQUEST_H

#include <stdint.h>



typedef struct{
    uint32_t fd;
    char *method;
    char *data;
    char *url;
}HTTPRequest;

#endif
