#pragma once
//typedef int QDataType;
//#include "BinTree.h"
extern struct BTNode;
typedef pBTNode QDataType;

typedef struct Node
{
	QDataType _data;
	struct Node* _pNext;
}Node, *PNode;

typedef struct Queue
{
	PNode _pHead;
	PNode _pTail;
}Queue;

PNode BuyNode(QDataType data);
void QueueInit(Queue* q);				//初始化队列
void QueuePush(Queue* q, QDataType data);//插入
void QueuePop(Queue* q);					//队列删除
int QueueEmpty(Queue* q);					//队列判空
int QueueSize(Queue* q);					//队列大小
QDataType QueueFront(Queue* q);					//队列头元素
QDataType QueueBack(Queue* q);					//队列尾元素
void QueueDestory(Queue*q);						//队列销毁

void TestQueue();
