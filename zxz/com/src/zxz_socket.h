#ifndef _ZXZ_SOCKET_H
#define _ZXZ_SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "zxz.h"

int zxz_socket(int domain, int type, int protocol);
int zxz_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int zxz_listen(int sockfd, int backlog);
int zxz_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int zxz_connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

#endif

