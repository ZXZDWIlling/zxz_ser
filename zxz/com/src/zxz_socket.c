#include "zxz_socket.h"

int zxz_socket(int domain, int type, int protocol)
{
	int ret;
	ret = socket(domain, type, protocol);
	if(ret < 0)
		sys_err(-1, "error: socket");
	return ret;
}

int zxz_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
	int ret;
	ret = bind(sockfd, addr, addrlen);
	if(ret < 0)
		sys_err(-1, "error: bind");
	return ret;
}

int zxz_listen(int sockfd, int backlog)
{
	int ret;
	ret = listen(sockfd, backlog);
	if(ret < 0)
		sys_err(-1, "error: listen");
	return ret;
}

int zxz_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
	int ret;
	ret = accept(sockfd, addr, addrlen);
	if(ret < 0)
		sys_err(-1, "error: accept");
	return ret;
}

int zxz_connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
	int ret;
	ret = connect(sockfd, addr, addrlen);
	if(ret < 0)
		sys_err(-1, "error: connect");
	return ret;
}

