#ifndef _ZXZ_SERVER_H
#define _ZXZ_SERVER_H

#include "zxz_socket.h"
#include <strings.h>
#include <string.h>

#define SERVER_PORT 9913 
#define SERVER_BACKLOG 20
typedef struct _zxz_tcpclient
{
	int connfd;
	struct sockaddr_in addr_cli;
}zxz_tcpclient;

int zxz_tcpserver_start();
zxz_tcpclient zxz_tcpserver_accept(int listenfd);
void zxz_tcpserver_run(void (*pfun)(void *));

#endif

