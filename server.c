#include <stdio.h>
#include <sys/types.h>  
#include <sys/socket.h>
#include <strings.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <string.h>

#define OPEN_MAX 5

#define ZXZ_SERVER_PORT	9913

int main()
{
	int listenfd, nready, client[OPEN_MAX];
	int epfd, i, len, j;
	struct sockaddr_in addr_ser, addr_cli;
	struct epoll_event event, revent[OPEN_MAX];
	socklen_t clilen;
	char buf[128];
	//init
	bzero(&addr_ser, sizeof(addr_ser));
	addr_ser.sin_family = AF_INET;
	addr_ser.sin_port = htons(ZXZ_SERVER_PORT);
	addr_ser.sin_addr.s_addr = htonl(INADDR_ANY);
	for(i = 0; i < OPEN_MAX; i++){
		client[i] = -1;
	}

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	//bind	
	bind(listenfd, (struct sockaddr *)&addr_ser, sizeof(addr_ser));
	//listen
	listen(listenfd, 20);

	event.events = EPOLLIN;
	event.data.fd = listenfd;
	epfd = epoll_create(OPEN_MAX);
	epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &event);
	for(;;){
		nready = epoll_wait(epfd, revent, OPEN_MAX, -1);		
		if(nready < 0)
			continue;
		for(i = 0; i < nready; i++){
			if(revent[i].events & EPOLLIN){
				for(j = 1; j < OPEN_MAX; j++){
					if(client[j] == -1)	
						break;
				}
				if(j >= OPEN_MAX)
					break;
				if(revent[i].data.fd == listenfd){
					printf("connect\n");
					clilen = sizeof(addr_cli);
					client[j] = accept(listenfd, (struct sockaddr *)&addr_cli, &clilen);
					event.events = EPOLLIN;
					event.data.fd = client[j];
					epoll_ctl(epfd, EPOLL_CTL_ADD, client[j], &event);
				}else{
					printf("accept\n");
					for(j = 1; j < OPEN_MAX; j++){
						if(revent[i].data.fd == client[j]){
							len = read(client[j], buf, sizeof(buf));	
							write(client[j], buf, len);
							if(strncmp(buf, "exit", strlen("exit")) == 0){
								close(client[j]);			
								client[j] = -1;
							}
						}
					}
				}
			}
		}
	}
	close(listenfd);
	return 0;
}
