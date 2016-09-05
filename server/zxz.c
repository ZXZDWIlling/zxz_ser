#include <sys/epoll.h>

static int epfd;

int zxz_init()
{
	epfd = epoll_create(1024);
}

int zxz_epoll_add(int fd)
{
	int ret;
	struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN;
	epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);
	return ret;
}

int zxz_epoll_wait(int fd)
{
	int ret;
	struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN;
	ret = epoll_wait(epfd, &event, 1024, -1);
	return ret;
}

