#include <string.h>


char *strtrim(char *str) {
    while (*str == ' ' || *str == '\t' || *str == '\r' || *str == '\n') str++;
    char *end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n')) end--;
    *(end + 1) = '\0';
    return str;
}
