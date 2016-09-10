#ifndef _ZXZ_LIST_H
#define _ZXZ_LIST_H

#include <stdlib.h>
#include <stdio.h>

typedef struct _zxz_list
{
	void *data;
	struct _zxz_list *next;
}zxz_list;


zxz_list *zxz_list_create(zxz_list *head);
zxz_list *zxz_list_add(zxz_list *head, void *data);
zxz_list *zxz_list_del(zxz_list *head, const void *data);
zxz_list *zxz_list_destory(zxz_list *head);
void zxz_list_printf(zxz_list *head);
zxz_list *zxz_list_iterator(zxz_list *head);
zxz_list *zxz_list_begin(zxz_list *head);
zxz_list *zxz_list_end(zxz_list *head);
int zxz_list_contain(zxz_list *head, void *data);

#endif

#if 0
int main()
{
	zxz_list *head;
	head = zxz_list_create(NULL);
	
	head = zxz_list_add(head, (void *)1);
	head = zxz_list_add(head, (void *)2);
	head = zxz_list_add(head, (void *)3);
	head = zxz_list_add(head, (void *)4);
	
	zxz_list_printf(head);

	head = zxz_list_destory(head);
	return 0;
}
#endif
















