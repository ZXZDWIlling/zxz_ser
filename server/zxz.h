#ifndef _ZXZ_H
#define _ZXZ_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/epoll.h>
#include <sys/types.h>  
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>

#include "zxz_socket.h"


static int epfd;

int zxz_init();
int zxz_epoll_add(int fd);
int zxz_epoll_wait(int fd);

#endif
