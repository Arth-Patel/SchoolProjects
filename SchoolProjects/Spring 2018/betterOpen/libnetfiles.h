#ifndef _LIBNETFILES_H
#define _LIBNETFILES_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>
#define PORT 42738

int sockOpen();
int netserverinit(char * hostname, int filemode);
int netopen(const char* pathname, int flags);
ssize_t netread(int fildes, void* buf, size_t nbyte);
ssize_t netwrite(int fildes, const void* buf, size_t nbyte);
int netclose(int fildes);

#endif
