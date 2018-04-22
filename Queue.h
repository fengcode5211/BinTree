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
void QueueInit(Queue* q);				//��ʼ������
void QueuePush(Queue* q, QDataType data);//����
void QueuePop(Queue* q);					//����ɾ��
int QueueEmpty(Queue* q);					//�����п�
int QueueSize(Queue* q);					//���д�С
QDataType QueueFront(Queue* q);					//����ͷԪ��
QDataType QueueBack(Queue* q);					//����βԪ��
void QueueDestory(Queue*q);						//��������

void TestQueue();
