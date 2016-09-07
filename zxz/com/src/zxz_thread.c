#include "zxz_thread.h"

int zxz_thread_create(zxz_thread *thr, int id)
{	
	int fd[2], ret;
	socketpair(AF_LOCAL, SOCK_STREAM, 0, fd);
	thr->id = id;
	thr->fd0 = fd[0];
	thr->fd1 = fd[1];
	thr->pfun = NULL;
	thr->parg = NULL;
	ret = pthread_create(&thr->pthr, NULL, zxz_thread_start, (void *)thr);
	pthread_detach(thr->pthr);
	return ret;
}

void *zxz_thread_start(void *arg)
{
	zxz_thread *thr = NULL;
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

void test(void)
{
	zxz_thread tid;
	char c;
	int a = 5;
	zxz_thread_create(&tid, 1);
	if(read(tid.fd0, &c, 1) == 1)
	{
		printf("read\n");
		zxz_thread_work(&tid, do_thr, (void *)&a, sizeof(a));	
	}
}
int main()
{
	test();
	//sleep(5);//when the main thread exits, a will be lost
	pthread_exit(NULL);
	return 0;
} 

#endif


