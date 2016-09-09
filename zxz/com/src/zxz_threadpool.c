#include "zxz_threadpool.h"
#if 1
void test(void *agr)
{
	printf("hello\n");
}
#endif
void zxz_threadpool_manager_create()
{
	pthread_t tid;
	pthread_create(&tid, NULL, zxz_threadpool_agent, NULL);
	pthread_detach(tid);
}

int zxz_threadpool_create(int size)
{
	int i;
	zxz_thread *thr;
	struct epoll_event event;

	epfd = epoll_create(1024);
	zxz_threadpool_manager_create();
	
	if(size <= 0)
		size = 5;
	pool.size = size;
	pool.thr_list = zxz_list_create(NULL);
	pool.thr_work = zxz_list_create(NULL);
	pool.thr_wait = zxz_list_create(NULL);
	for(i = 0; i < size; i++)
	{
		thr = NULL;
		thr = zxz_thread_create(thr, i);
		event.data.fd = thr->fd0;
		event.events = EPOLLIN;
		epoll_ctl(epfd, EPOLL_CTL_ADD, thr->fd0, &event);
		pool.thr_list = zxz_list_add(pool.thr_list, thr);
	}
	return 0;
}

zxz_thread *zxz_threadpool_findbyfd0(int fd0)
{
	zxz_thread *pthr = NULL;
	zxz_list *plist = zxz_list_iterator(pool.thr_list);
	for(; plist != zxz_list_end(pool.thr_list); plist = plist->next)
	{
		pthr = (zxz_thread *)plist->data;
		if(pthr != NULL && pthr->fd0 == fd0)
			return pthr;
	}
	return pthr;
}

void zxz_threadpool_waitingthread_run(void (*pfun)(void *), void *arg, ssize_t size)
{
	zxz_list *pwait = zxz_list_begin(pool.thr_wait);
	pwait = pwait->next;
	zxz_thread *p = (zxz_thread *)pwait->data;
//	printf("id=%d\n", p->id);
//	printf("run\n");
	if(pwait != NULL)
	{
	//	printf("not NULL\n");
	//	count++;
		zxz_thread_work(p, pfun, arg, size);
		pool.thr_work = zxz_list_add(pool.thr_work, p);
		pool.thr_wait = zxz_list_del(pool.thr_wait, p);
	}
}

#if 0
void test(void *agr)
{
	printf("hello\n");
}
#endif

void *zxz_threadpool_agent(void *arg)
{
	int ret, i;
	int fd;
	zxz_thread *pthr;
	while(1)
	{
		ret = epoll_wait(epfd, ep, 1024, -1);	
///		printf("ret = %d\n", ret);
		for(i = 0; i < ret; i++)
		{
			fd = ep[i].data.fd;
			if(ep[i].events & EPOLLIN)
			{
				if((pthr = zxz_threadpool_findbyfd0(fd)) != NULL)
				{
					pool.thr_wait = zxz_list_add(pool.thr_wait, pthr);
//					zxz_thread_work(pthr, test, NULL, 0);
					epoll_ctl(epfd, EPOLL_CTL_DEL, pthr->fd0, NULL);
				}
			}
		}
	}

}
#if 0
int main()
{

	zxz_threadpool_create(5);
	zxz_threadpool_agent();
	pthread_exit(NULL);
	return 0;
}
#endif
#if 0
int main()
{
	zxz_threadpool_create(5);
	pthread_exit(NULL);
	return 0;
}
#endif
