#ifndef _ZXZ_THREADPOOL_H
#define _ZXZ_THREADPOOL_H

#include "zxz_thread.h"
#include "zxz_list.h"
#include <sys/epoll.h>

typedef struct zxz_threadpool_t
{
	zxz_list *thr_list;
	zxz_list *thr_work;
	zxz_list *thr_wait;
	int size;
}zxz_threadpool;

zxz_threadpool pool;
int epfd;
struct epoll_event ep[1024];

void zxz_threadpool_manager_create();
int zxz_threadpool_create(int size);
zxz_thread *zxz_threadpool_findbyfd0(int fd0);
void zxz_threadpool_waitingthread_run(void (*pfun)(void *), void *arg, ssize_t size);
void *zxz_threadpool_agent(void *);

#endif
