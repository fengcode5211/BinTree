#include "BinTree.h"
#include "Queue.h"
#include <stdio.h>
#include <assert.h>
#include <malloc.h>


void QueueInit(Queue* q)
{
	assert(q);
	q->_pHead = NULL;
	q->_pTail = NULL;
}

PNode BuyNode(QDataType data)
{
	PNode pNewNode;

	pNewNode = (PNode)malloc(sizeof(Node));

	if (NULL == pNewNode)
	{
		return NULL;
	}
	pNewNode->_data = data;
	pNewNode->_pNext = NULL;

	return pNewNode;
}

void QueuePush(Queue* q, QDataType data)
{
	assert(q);
	if (NULL == q)
	{
		return;
	}
	PNode pCur = BuyNode(data);

	if (NULL == q->_pHead && NULL == q->_pTail)
	{
		q->_pHead = pCur;
		q->_pTail = pCur;
	}
	else
	{
		q->_pTail->_pNext = pCur;
		q->_pTail = q->_pTail->_pNext;
	}
}

void QueuePop(Queue* q)
{
	assert(q);

	if (NULL == q->_pHead)
	{
		printf("�ӿ�\n");
		return;
	}
	else if (q->_pHead == q->_pTail)		//ֻ�ж�ͷ
	{
		free(q->_pHead);
		q->_pHead = NULL;
		q->_pTail = NULL;
	}
	else
	{
		PNode pDel = q->_pHead;			//��Ƕ�ͷ
		q->_pHead = pDel->_pNext;		//�ƶ���ͷ
		free(pDel);
	}

}

QDataType QueueFront(Queue* q)
{
	assert(q && q->_pHead);

	return q->_pHead->_data;
}

QDataType QueueBack(Queue* q)
{
	assert(q && q->_pHead);

	return q->_pTail->_data;
}

int QueueSize(Queue* q)
{
	int count = 0;
	PNode pcur = q->_pHead;
	assert(q);
	while (pcur)
	{
		count++;
		pcur = pcur->_pNext;
	}
	return count;
}

int QueueEmpty(Queue* q)
{
	assert(q);
	return NULL == q->_pHead;
}

void QueueDestory(Queue*q)
{
	assert(q);
	PNode pcur = q->_pHead;
	while (pcur)
	{
		q->_pHead = pcur->_pNext;
		free(pcur);
		pcur = q->_pHead;
	}
	q->_pTail = NULL;
}
