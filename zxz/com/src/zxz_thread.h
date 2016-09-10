#ifndef _ZXZ_THREAD_H
#define _ZXZ_THREAD_H

#include "zxz.h"
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

typedef struct zxz_thread_t
{
	pthread_t pthr;
	int id;
	int fd0; //main use
	int fd1; //thread use
	void (*pfun)(void *);
	void *parg;
}zxz_thread;

zxz_thread *zxz_thread_create(zxz_thread *thr, int id);
void *zxz_thread_start(void *arg);
void zxz_thread_wait(zxz_thread *thr);
void zxz_thread_work(zxz_thread *thr, void(*fun)(void *arg), void *arg, ssize_t size);

#endif
