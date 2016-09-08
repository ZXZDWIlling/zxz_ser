#include "zxz_list.h"

zxz_list *zxz_list_create(zxz_list *head)
{
	if (head == NULL)
		head = (zxz_list*)malloc(sizeof(zxz_list));
	head->data = NULL;
	head->next = NULL;
	return head;
}

zxz_list *zxz_list_add(zxz_list *head, void *data)
{
	zxz_list *pNet;
	zxz_list *pTmp;
	zxz_list *pCur;
	//create pTmp
	pTmp = (zxz_list *)malloc(sizeof(zxz_list));
	pTmp->data = data;
	pTmp->next = NULL;
	if (head == NULL || data == NULL){
		printf("zxz_list_init\n");
		return NULL;
	}
	pNet = head->next;
	pCur = head;
	while (pNet != NULL)
	{
		pCur = pNet;
		pNet = pNet->next;
	}
	//add at the tail
	pCur->next = pTmp;
	
	return head;
}


zxz_list *zxz_list_del(zxz_list *head, const void *data)
{
	zxz_list *pNet;
	zxz_list *pCur;
	zxz_list *pTmp;
	if (head == NULL || data == NULL){
		printf("zxz_list_del\n");
		return NULL;
	}
	pNet = head->next;
	pCur = head;
	while (pNet != NULL){
		if (pNet->data == data){
			//del
			pTmp = pNet;
			pNet = pNet->next;
			free(pTmp);
			pCur->next = pNet;
		}
		else{
			//next
			pCur = pNet;
			pNet = pNet->next;
		}
	}
	return head;
}

zxz_list *zxz_list_destory(zxz_list *head)
{
	zxz_list *pNet;
	zxz_list *pTmp;
	if (head == NULL){
		printf("zxz_list_init\n");
		return NULL;
	}
	pNet = head->next;
	pTmp = head;
	while (pNet != NULL){
		free(pTmp);
		pTmp = pNet;
		pNet = pNet->next;
	}
	return NULL;
}

void zxz_list_printf(zxz_list *head)
{
	head = head->next;
	while (head != NULL){
		printf("%d\n", (int)head->data);
		head = head->next;
	}
}

zxz_list *zxz_list_iterator(zxz_list *head)
{
	return head;
}

zxz_list *zxz_list_begin(zxz_list *head)
{
	return head;
}
	
zxz_list *zxz_list_end(zxz_list *head)
{
	zxz_list *pend;
	pend = head;
	while((pend = pend->next) != NULL);
	return pend;
}








