#include "zxz_socket.h"

void sys_err(const int exitcode, const char *desc)
{
	perror(desc);
	exit(exitcode);
}

int z_socket(int domain, int type, int protocol)
{
	int ret;
	ret = socket(domain, type, protocol);
	if(ret < 0)
		sys_err(errno, "socket");
	return ret;
}

int z_bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen)
{
	int ret;
	ret = bind(sockfd, addr, addrlen);
	if(ret < 0)
		sys_err(errno, "bind");
	return ret;
}

int z_listen(int sockfd, int backlog)
{
	int ret;
	ret = listen(sockfd, backlog);
	if(ret < 0)
		sys_err(errno, "bind");
	return ret;
}
