#include "zxz_threadpool.h"
#include <stdio.h>

zxz_thread *zxz_thread_create(zxz_thread *thr, int id)
{	
	if(thr == NULL)
		thr = malloc(sizeof(zxz_thread));
	int fd[2], ret;
	socketpair(AF_LOCAL, SOCK_STREAM, 0, fd);
	thr->id = id;
	thr->fd0 = fd[0];
	thr->fd1 = fd[1];
	thr->pfun = NULL;
	thr->parg = NULL;
	ret = pthread_create(&thr->pthr, NULL, zxz_thread_start, (void *)thr);
	pthread_detach(thr->pthr);
	return thr;
}

void *zxz_thread_start(void *arg)
{
	zxz_thread *thr = NULL;
	printf("thread start\n");
	if(arg != NULL)
		thr = (zxz_thread *)arg;
	while(1)
		zxz_thread_wait(thr);
	return NULL;
}

void zxz_thread_wait(zxz_thread *thr)
{
	char c = 'z';
	write(thr->fd1, &c, 1);
	if(read(thr->fd1, &c, 1) == 1)
	{
		thr->pfun(thr->parg);	
		thr->pfun = NULL;
		if(thr->parg != NULL)
			free(thr->parg);
		thr->parg = NULL;
	}
	
}

void zxz_thread_work(zxz_thread *thr, void (*fun)(void *), void *arg, ssize_t size)
{
	char c;
	thr->pfun = fun;	
	if(size > 0)
	{
		thr->parg = malloc(sizeof(size));
		memcpy(thr->parg, arg, size);
	}
	write(thr->fd0, "z", 1);
	read(thr->fd0, &c, 1);
}

#if 0
#include <stdio.h>
void do_thr(void *arg)
{
	int *a = (int *)arg;
	printf("%d\n", *a);
}

int main()
{
	zxz_thread tid[5];
	char c;
	int i;
	int a = 5;
for(i = 0; i < 5; i++)
	zxz_thread_create(&tid[i], 1);
for(i = 0; i < 5; i++)
{
	if(read(tid[i].fd0, &c, 1) == 1)
	{
		printf("read\n");
		zxz_thread_work(&tid[i], do_thr, (void *)&a, sizeof(a));	
	}
}
	sleep(5);//when the main thread exits, a will be lost
	pthread_exit(NULL);
	return 0;
} 

#endif


