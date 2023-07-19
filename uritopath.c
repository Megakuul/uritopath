#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char* FILEPREFIX = "file://";

int decodeURI(const char *uri, char *output, size_t outputSize) {
    if (strncmp(uri, FILEPREFIX, strlen(FILEPREFIX)) != 0) {
        return 1;
    }
    size_t requiredSize = strlen(FILEPREFIX) + 1;
    if (requiredSize > outputSize) {
        return 1;
    }
    uri += strlen(FILEPREFIX);
    outputSize -= strlen(FILEPREFIX);
    char c;
    while ((c = *uri) != '\0') {
        requiredSize = 1 + 1;
        if (requiredSize > outputSize) {
            return 1;
        }
        if (c == '%') {
            int value;
            if (isxdigit(*(uri + 1)) && isxdigit(*(uri + 2)) && sscanf(uri + 1, "%02x", &value) == 1) {
                requiredSize = 3 + 1;
                if (requiredSize > outputSize) {
                    return 1;
                }
                *output++ = value;
                uri += 3;
                outputSize -= 3;
            } else {
                *output++ = c;
                uri++;
                outputSize--;
            }
        } else if (c == '+') {
            *output++ = ' ';
            uri++;
            outputSize--;
        } else {
            *output++ = c;
            uri++;
            outputSize--;
        }
    }
    *output = '\0';
    return 0;
}

int encodePath(const char *path, char *output, size_t outputSize) {
    size_t requiredSize = strlen(FILEPREFIX) + 1;
    if (requiredSize > outputSize) {
        return 1;
    }
    strcpy(output, FILEPREFIX);
    output += strlen(FILEPREFIX);
    outputSize -= strlen(FILEPREFIX);
    char c;
    while ((c = *path) != '\0') {
        if (!isalnum(c) && c != '/' && c != '.') {
            requiredSize = 3 + 1;
            if (requiredSize > outputSize) {
                return 1;
            }
            sprintf(output, "%%%02X", (unsigned char)c);
            output += 3;
            outputSize -= 3;
        } else {
            requiredSize = 1 + 1;
            if (requiredSize > outputSize) {
                return 1;
            }
            *output++ = c;
            --outputSize;
        }
        path++;
    }
    *output = '\0';
    return 0;
}
