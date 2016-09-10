#include "zxz_server.h"
#include "zxz_threadpool.h"


void zxz_tcpserver_init(int thread_count)
{
	zxz_threadpool_create(thread_count);
}

int zxz_tcpserver_start()
{
//	printf("start\n");
	int listenfd;
	struct sockaddr_in addr_ser;
	//init addr_ser
	bzero(&addr_ser, sizeof(addr_ser));
	addr_ser.sin_family = AF_INET;
	addr_ser.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_ser.sin_port = htons(SERVER_PORT);
	//socket	
	listenfd = zxz_socket(AF_INET, SOCK_STREAM, 0);
	//bind
	zxz_bind(listenfd, (struct sockaddr *)&addr_ser, sizeof(addr_ser));
	//listen
	zxz_listen(listenfd, SERVER_BACKLOG);
	
	return listenfd;
}

zxz_tcpclient zxz_tcpserver_accept(int listenfd)
{
	//printf("accept\n");
	int connfd;
	struct sockaddr_in addr_cli;
	socklen_t clilen;
	zxz_tcpclient client;
	
	clilen = sizeof(addr_cli);
	//accept
	connfd = zxz_accept(listenfd, (struct sockaddr *)&addr_cli, &clilen);
	client.connfd = connfd;
	memcpy(&client.addr_cli, &addr_cli, sizeof(struct sockaddr_in));
	return client;
}

#if 0
#include <stdio.h>
#include <unistd.h>
void ser_do(void *arg)
{
	char buf[128];
	int len;
	zxz_tcpclient *p;
	if(arg != NULL)
		p = (zxz_tcpclient *)arg;
	len = read(p->connfd, buf, sizeof(buf));
	write(STDOUT_FILENO, buf, len);
}
#endif

void zxz_tcpserver_run(int listenfd, void (*pfun)(void *))
{
	zxz_tcpclient client;
	for(;;)
	{
		client = zxz_tcpserver_accept(listenfd);
//		printf("size=%d\n", sizeof(client));
		zxz_threadpool_waitingthread_run(pfun, (void *)&client, sizeof(client));
	}
	close(listenfd);
}	


#if 0
int main()
{
	int listenfd;
	zxz_tcpserver_init(5);
	listenfd = zxz_tcpserver_start();
	zxz_tcpserver_run(listenfd, ser_do);
}
#endif
