#ifndef URITOPATH_H
#define URITOPATH_H

#include <string.h>

/**
 * Converts a file uri in format "file://C:\Users\User%201" or "file:///home/User%201"
 * to a system path like "C:\Users\User 1" or "/home/User 1"
 * 
 * @param uri URI to decode
 * @param output Output buffer
 * @param outputSize Output buffer size
 * @return Returns 0 if everything went fine and 1 if the output buffer is not large enough for the path
 * or if the file:// Prefix is missing
*/
int decodeURI(const char *uri, char *output, size_t outputSize);

/**
 * Converts a path string in format "C:\Users\User 1" or "/home/User 1"
 * into a file uri like "file://C:\Users\User%201" or "file:///home/User%201"
 * 
 * @param path Path to encode
 * @param output Output buffer
 * @param outputSize Output buffer size
 * @return Returns 0 if everything went fine and 1 if the output buffer is not large enough for the URI
*/
int encodePath(const char *path, char *output, size_t outputSize);

#endif