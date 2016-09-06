#ifndef _ZXZ_SOCKET_H
#define _ZXZ_SOCKET_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>  
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>

void sys_err(const int exitcode, const char *desc);

int z_socket(int domain, int type, int protocol);

int z_bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);

int z_listen(int sockfd, int backlog);

#endif
