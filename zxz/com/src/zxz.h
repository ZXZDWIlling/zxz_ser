#ifndef _ZXZ_H
#define _ZXZ_H 

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/epoll.h>

int epfd;
struct epoll_event ep[1024];
void sys_err(int exitcode, const char *desc);

#endif


