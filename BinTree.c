#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>

#include "BinTree.h"
#include "Queue.h"
#include "Stack.h"


pBTNode BTBuyNode(BTDataType data)
{
	pBTNode pNewNode = (pBTNode)malloc(sizeof(BTNode));
	assert(pNewNode);
	pNewNode->_data = data;
	pNewNode->_pLeft = NULL;
	pNewNode->_pRight = NULL;
	
	return pNewNode;
}

void InitBinTree(pBTNode *root)
{
	assert(root);
	*root = NULL;
}


void _CreateBinTree(pBTNode *pRoot, BTDataType array[], int size, int *index, BTDataType invalid)
	//ǰ�����
{
	assert(index);		
	assert(size > 0);
	if ( *index < size && invalid != array[*index]) //�����߽磬��ǰλ��Ϊ��Чֵ
	{
		/* �������ڵ� */
		*pRoot = BTBuyNode(array[*index]);

		++(*index);
		_CreateBinTree(&(*pRoot)->_pLeft, array, size, index, invalid);    //������
		
		++(*index);
		_CreateBinTree(&(*pRoot)->_pRight, array, size, index,invalid);   //������
	}
}

void CreateBinTree(pBTNode* pRoot, BTDataType array[], int size, BTDataType invalid)
{
	int index = 0;	//ÿ�εݹ��轫����ֵ���и��£�������ַ
	_CreateBinTree(pRoot, array, size, &index, invalid);//���������ݹ��ʵ�ִ�����������
}

pBTNode CopyBinTree(pBTNode pRoot)	//ǰ�����
{
	pBTNode pNewRoot = NULL;
	if (pRoot)
	{
		//�������ڵ�
		pNewRoot = BTBuyNode(pRoot->_data);
		//������ǰ��������
		if (pRoot->_pLeft)	//������ڵ��������Ϊ�գ������п��������Ч��
		{
			pNewRoot->_pLeft = CopyBinTree(pRoot->_pLeft);
		}
		//������ǰ��������
		if (pRoot->_pRight)
		{
			pNewRoot->_pRight = CopyBinTree(pRoot->_pRight);
		}
	}
	return pNewRoot;
}

void PreOrder(pBTNode pRoot)	//ǰ��ݹ�  ��---��----��		O(N)   O(N)
{
	if (pRoot)
	{
		printf("%c ", pRoot->_data);
		PreOrder(pRoot->_pLeft);
		PreOrder(pRoot->_pRight);
	}
}

void PreOrderNor(pBTNode pRoot)
{
#if 0		//��1
	Stack s;
	pBTNode pTop = NULL;
	if (NULL == pRoot)
		return;
	InitStack(&s);
	
	PushStack(&s, pRoot);		//��ѹջ���ڵ�
	while (!StackEmpty(&s))
	{
		pTop = TopStack(&s);	//������ǰ�ڵ�
		printf("%c ", pTop->_data);
		PopStack(&s);		//����ǰ�ڵ��ջ

		if (NULL != pTop->_pRight)			//��ѹջ������
			PushStack(&s, pTop->_pRight);
		if (NULL != pTop->_pLeft)			//ѹջ������
			PushStack(&s, pTop->_pLeft);
	}
	printf("\n");
#endif
//��2
	Stack s;
	pBTNode pCur = NULL;
	if (NULL == pRoot)
		return;
	InitStack(&s);
	PushStack(&s, pRoot);
	while (!StackEmpty(&s))		
	{
		pCur = TopStack(&s);	//����ջ��
		PopStack(&s);			//��ջ
		while (pCur)
		{
			printf("%c ", pCur->_data);				//������ǰ���
			if (pCur->_pRight)						//���浱ǰ�ڵ��������
				PushStack(&s, pCur->_pRight);
			pCur = pCur->_pLeft;
		}
	}
	printf("\n");
}

void InOrder(pBTNode pRoot)		//����ݹ�   ��----��----��
{
	if (pRoot)
	{
		InOrder(pRoot->_pLeft);
		printf("%c ", pRoot->_data);
		InOrder(pRoot->_pRight);
	}
}

void InOrderNor(pBTNode pRoot)
{
	pBTNode pCur = NULL;
	Stack s;
	if (NULL == pRoot)
	{
		return;
	}
	InitStack(&s);
	pCur = pRoot;
	//pCur��ǵ�ǰ�Ľ�㣬���pCurΪ��˵���ýڵ������������Ϊ�գ�������ջ����ʱ��Ҫ���ջ��״̬
	while (pCur || !StackEmpty(&s))
	{
		while (pCur)	//�ҵ�ǰ���������Ľ�㲢��������·���е����нڵ�
		{
			PushStack(&s, pCur);
			pCur = pCur->_pLeft;
		}
		pCur = TopStack(&s);
		printf("%c ", pCur->_data);
		PopStack(&s);
		//����ǰԪ�ص����������ص�ѭ����ʼ��ȥ�ҵ��������������Ľ��
		pCur = pCur->_pRight;
	}

}

void PostOrder(pBTNode pRoot)		//����ݹ�    ��-----��-----��
{
	if (pRoot)
	{
		PostOrder(pRoot->_pLeft);
		PostOrder(pRoot->_pRight);
		printf("%c ", pRoot->_data);
	}
}

void PostOrderNor(pBTNode pRoot)
{
	pBTNode pCur = NULL;
	pBTNode pPre = NULL;	//�����һ�η��ʹ��Ľ��
	pBTNode pTop = NULL;	//���ջ�����
	Stack s;
	if (NULL == pRoot)
	{
		return;
	}
	InitStack(&s);
	pCur = pRoot;
	while (NULL != pCur || !StackEmpty(&s))		//pcָ��ղ���ջΪ����˵������������
	{
		while (pCur)	//�ҵ�����ߵĽ�㣬·���ϵ�Ԫ��ѹջ
		{
			PushStack(&s, pCur);
			pCur = pCur->_pLeft;
		}
		pTop = TopStack(&s);
		//ջ�����û�����������ߵ�ǰ�ڵ���������Ѿ������ʹ����ͷ��ʵ�ǰ��㣬��ջ
		if (NULL == pTop->_pRight || pTop->_pRight == pPre)
		{
			printf("%c ", pTop->_data);
			pPre = pTop;			//�����ʹ��Ľ����
			PopStack(&s);
		}
		else			//����ѭ���ķ�����������
		{
			pCur = pTop->_pRight;
		}
	}
}

void LevelOrder(pBTNode pRoot)
{
	Queue q;
	pBTNode pHead =	NULL;
	if (pRoot == NULL)
	{
		return;
	}
	QueueInit(&q);
	QueuePush(&q, pRoot);		//�Ƚ����ڵ������

	while (!QueueEmpty(&q))		//����Ϊ����˵�������������
	{
		pHead = QueueFront(&q);		//ȡ��ͷ
		printf("%c  ", pHead->_data);
		if (pHead->_pLeft)		//����������
		{
			QueuePush(&q, pHead->_pLeft);
		}
		if (pHead->_pRight)		//����������
		{
			QueuePush(&q, pHead->_pRight);
		}
		QueuePop(&q);
	}
	printf("\n");
	QueueDestory(&q);		//������Ҫ����
}



void DestoryBinTree(pBTNode *ppRoot)	//�����������������Ҫ�ı���ڵ��ָ�򣬴�����ָ��
{
	assert(ppRoot);
	if (*ppRoot)
	{
		DestoryBinTree(&(*ppRoot)->_pLeft);
		DestoryBinTree(&(*ppRoot)->_pRight);
		free(*ppRoot);
		*ppRoot = NULL;
	}
}

int SizeBinTree(pBTNode pRoot)
{
	if (NULL == pRoot)
	{
		return 0;
	}
	return (1 + SizeBinTree(pRoot->_pLeft) + SizeBinTree(pRoot->_pRight));
}

int GetLeafCount(pBTNode pRoot)
{
	if (NULL == pRoot)
	{
		return 0;
	}
	if (NULL == pRoot->_pLeft && NULL == pRoot->_pRight)
	{
		return 1;
	}
	return GetLeafCount(pRoot->_pLeft) + GetLeafCount(pRoot->_pRight);
}

int GetLevelNodeCount(pBTNode pRoot, int k)//��K�������
{
	if (NULL == pRoot || k <= 0)
		return 0;
	if (k == 1)
	{
		return 1;
	}
	return GetLevelNodeCount(pRoot->_pLeft, k - 1) + GetLevelNodeCount(pRoot->_pRight, k - 1);
}


int Height(pBTNode pRoot)
{
	int LeftHeight = 0;
	int RightHeight = 0;
	if (NULL == pRoot)
	{
		return 0;
	}
	LeftHeight = Height(pRoot->_pLeft);
	RightHeight = Height(pRoot->_pRight);
	
	return LeftHeight > RightHeight ? LeftHeight + 1 : RightHeight + 1;
}


void Mirror(pBTNode pRoot)			//����
{
	if (pRoot)
	{
		pBTNode pTmp = pRoot->_pLeft;
		pRoot->_pLeft = pRoot->_pRight;
		pRoot->_pRight = pTmp;
		if (pRoot->_pLeft)
			Mirror(pRoot->_pLeft);
		if (pRoot->_pRight)
			Mirror(pRoot->_pRight);
	}
}

void Mirror_Nor(pBTNode pRoot)		//��֤����ɹ�----��������
{
	Queue q;
	pBTNode pTmp = NULL;
	pBTNode pHead = NULL;	//��Ƕ�ͷԪ��
	if (NULL == pRoot)
	{
		return;
	}
	QueueInit(&q);
	QueuePush(&q, pRoot);

	while(!QueueEmpty(&q))
	{
		pHead = QueueFront(&q);

		pTmp = pHead->_pLeft;
		pHead->_pLeft = pHead->_pRight;
		pHead->_pRight = pTmp;
		
		if (pHead->_pLeft)
			QueuePush(&q, pHead->_pLeft);
		if (pHead->_pRight)
			QueuePush(&q, pHead->_pRight);
		
		QueuePop(&q);
	}
	QueueDestory(&q);
}

int IsCompleteBinTree(pBTNode pRoot)		//�ж���ȫ������, ��������
{
	Queue q;
	pBTNode pHead = NULL;
	int flag = 0;					//����ҵ��������㣨�Ӹ������㿪ʼ����Ľڵ㲻��������������
	if (NULL == pRoot)
	{
		return 1;
	}
	QueueInit(&q);
	QueuePush(&q, pRoot);//�����ڵ������
	while (!QueueEmpty(&q))		//����Ϊ�գ�˵��
	{
		pHead = QueueFront(&q);
		if (1 == flag)		//���������һ���ڵ�
		{
			if (pHead->_pLeft || pHead->_pRight)
			return 0;
		}
		else
		{
			if (pHead->_pLeft && pHead->_pRight)	//�������������Һ��ӣ�����Ҫ�ҵ�������
			{
				QueuePush(&q, pHead->_pLeft);
				QueuePush(&q, pHead->_pRight);
				flag = 0;
			}
			else if (pHead->_pLeft)			//ֻ������
			{
				QueuePush(&q, pHead->_pLeft);
				flag = 1;
			}
			else if (pHead->_pRight)		//ֻ���Һ���
				return 0;
			else						//���Һ��Ӷ�û��
				flag = 1;
		}
		QueuePop(&q);
	}
	return 1;
}

pBTNode Find(pBTNode pRoot, BTDataType data)		//����ֵΪdata��Ԫ��
{
	pBTNode pRet = NULL;
	if (NULL == pRoot)
	{
		return NULL;
	}
	if (data == pRoot->_data)
		return pRoot;
	if (pRet = Find(pRoot->_pLeft, data))
		return pRet;
	return Find(pRoot->_pRight, data);

}

int IsNodeInBinTree(pBTNode pRoot, pBTNode pNode)
{
	int flag = 0;
	if (NULL == pRoot || NULL == pNode)
		return 0;
	if (pRoot == pNode)
	{
		return 1;
	}
	if(flag = IsNodeInBinTree(pRoot->_pLeft, pNode))
		return flag;
	return IsNodeInBinTree(pRoot->_pRight, pNode);
}

pBTNode LeftChild(pBTNode pNode)
{

	return (NULL == pNode) ? NULL : pNode->_pLeft;
}

pBTNode RightChild(pBTNode pNode)
{
	return (NULL == pNode) ? NULL : pNode->_pRight;
}

pBTNode Parent(pBTNode pRoot, pBTNode pNode)
{
	pBTNode pLeft = NULL;
	pBTNode pRight = NULL;
	if (NULL == pRoot || NULL == pNode)
	{
		return NULL;
	}
	if (pRoot == pNode)		//���ڵ�˫����ΪNULL
	{
		return NULL;
	}
	if (pNode == pRoot->_pLeft || pNode == pRoot->_pRight)
	{
		return pRoot;
	}
	pLeft = Parent(pRoot->_pLeft, pNode);
	pRight = Parent(pRoot->_pRight, pNode);
	return pLeft != NULL ? pLeft : pRight;
}

int FindInOrder(BTDataType array[], int left, int right, BTDataType to_find)	//�������в��ҽ��
{
	int i = left;
	for (; i < right; i++)
	{
		if (to_find == array[i])
		{
			return i;
		}
	}
	return -1;	//���ܷ���0��		
}


pBTNode _ReBuildTree(BTDataType pre_order[], int pre_order_size, int* index,
	BTDataType in_order[], int in_order_left, int in_order_right)
{
	assert(NULL != index);
	int IdxCurInInOrder = 0;			//��ǰ����������������е�λ��
	if (in_order_left >= in_order_right)//˵�������������Ϊ�գ�����ǰ��û��������
	{
		return NULL;
	}
	if (*index >= pre_order_size)		//˵�������������������ԭ����
	{
		return NULL;
	}
	//ȡ���������ֵ�����µĽ��
	pBTNode NewNode = BTBuyNode(pre_order[*index]);
	//����ȡ����NewNode��ֵ��A�Ļ����������ݹ��ʱ����Ҫȡ���Ľڵ�ΪB

	IdxCurInInOrder = FindInOrder(in_order,in_order_left, in_order_right, pre_order[*index]);
	assert(IdxCurInInOrder != -1);		//�Ҳ�����ǰ�Ľ�㣬˵������������������
	//�����Ȳ�����������������ڽ���index������
	++(*index);
	
	NewNode->_pLeft =  _ReBuildTree(pre_order, pre_order_size, index, in_order, in_order_left, IdxCurInInOrder);	//�ݹ�Ĵ���ǰ����������
	NewNode->_pRight = _ReBuildTree(pre_order, pre_order_size, index, in_order, IdxCurInInOrder + 1, in_order_right);	//�ݹ�Ĵ���ǰ����������
	return NewNode;
}

pBTNode ReBuildTree(BTDataType pre_order[], int pre_order_size,
	BTDataType in_order[], int in_order_size)		//�������������������Ľ����ԭһ��������
{
	int index = 0;		//��������ĵ�ǰ�±�
	pBTNode NewNode = _ReBuildTree(pre_order, pre_order_size, &index, in_order, 0, in_order_size);	//��������ʵ�ֵݹ�
	return NewNode;
}


void TestReBuildTree()
{
	BTDataType pre_order[] = "abdegcf";
	BTDataType in_order[] = "dbgeacf";
	pBTNode NewNode= ReBuildTree(pre_order, strlen(pre_order), in_order, strlen(in_order));

	printf("�������:\n");
	PreOrder(NewNode);
	printf("\n");

	printf("�������:\n");
	InOrder(NewNode);
	printf("\n");
}


void  TestBinTree()
{
	pBTNode pRoot = NULL;
	pBTNode pNewRoot = NULL;
	pBTNode pTmp = NULL;
	pBTNode ret = NULL;
	int K = 3;
	char array[] = { 'A', 'B', 'D', '#', '#', '#', 'C', 'E', '#', '#', 'F'}; 
	CreateBinTree(&pRoot, array, sizeof(array)/sizeof(array[0]),'#');
	pNewRoot = CopyBinTree(pRoot);
	printf("ǰ��");
	PreOrderNor(pRoot);
	printf("\n");
	printf("����");
	InOrderNor(pRoot);
	printf("\n");
	printf("����");
	PostOrderNor(pRoot);
	printf("\n");
	printf("size of BinTree: %d\n", SizeBinTree(pRoot));
	printf("LeafCount: %d\n", GetLeafCount(pRoot));
	printf("%d  ---- NodeCount: %d\n",K, GetLevelNodeCount(pRoot, K));
	printf("Height: %d\n", Height(pRoot));
	LevelOrder(pRoot);
	Mirror_Nor(pRoot);
	Mirror_Nor(pRoot);
	LevelOrder(pRoot);
	if (IsCompleteBinTree(pRoot))
	{
		printf("Is completeBinTree!\n");
	}
	else
	{
		printf("No!\n");
	}

	pTmp = Find(pRoot, 'C');
	ret = LeftChild(pTmp);
	printf("left = %c \n", ret->_data);
	ret = RightChild(pTmp);
	printf("right = %c \n", ret->_data);
	ret = Parent(pRoot, pTmp);
	printf("parent == %c \n", ret->_data);

	DestoryBinTree(&pRoot);
	//DestoryBinTree(&pNewRoot);
}