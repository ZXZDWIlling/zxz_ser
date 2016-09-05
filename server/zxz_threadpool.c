#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include "zxz.c"

typedef struct _zxz_thread_t
{
	pthread_t tid;
	int fd[2];	
}zxz_thread_t;

typedef struct _zxz_threadpool_t
{
	int min_running_count;
	int max_running_count;
	int running_count;
	int poolsize;

	zxz_thread_t thr[20];

}zxz_threadpool_t;


void *zxz_thr_run(void *arg)
{
	char buf = 1;
	int len;
	zxz_thread_t *pthr = (zxz_thread_t *)arg;
	printf("before\n");
	write(pthr->fd[1], &buf, 1);
	read(pthr->fd[1], &buf, 1);
	printf("after\n");
	return NULL;
}

zxz_threadpool_t *zxz_threadpool_init(zxz_threadpool_t *tpool)
{
	zxz_threadpool_t *ppool = tpool;
	int i, pfd[2];
	if(tpool == NULL){
		ppool = malloc(sizeof(zxz_threadpool_t));
		ppool->min_running_count = 5;
		ppool->max_running_count = 10;
		ppool->running_count = 0;
		ppool->poolsize = 20;
	}
	
	//create thread
	for(i = 0; i < ppool->min_running_count; i++){
		socketpair(AF_LOCAL, SOCK_STREAM, 0, ppool->thr[i].fd);
		//add to epoll
		zxz_epoll_add(ppool->thr[i].fd[0]);
		pthread_create(&ppool->thr[i].tid, NULL, zxz_thr_run, &ppool->thr[i]);
		pthread_detach(ppool->thr[i].tid);	
	}
	return ppool;
}



int main()
{
	int ret;
	zxz_threadpool_t *tpool = NULL;
	zxz_init();
	tpool = zxz_threadpool_init(NULL);
	printf("wait\n");
	ret = zxz_epoll_wait(tpool->thr[0].fd[0]);
	printf("ret=%d\n", ret);
	pthread_exit(NULL);
	return 0;
}
