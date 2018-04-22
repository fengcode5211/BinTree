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
	//前序遍历
{
	assert(index);		
	assert(size > 0);
	if ( *index < size && invalid != array[*index]) //索引边界，当前位置为有效值
	{
		/* 创建根节点 */
		*pRoot = BTBuyNode(array[*index]);

		++(*index);
		_CreateBinTree(&(*pRoot)->_pLeft, array, size, index, invalid);    //左子树
		
		++(*index);
		_CreateBinTree(&(*pRoot)->_pRight, array, size, index,invalid);   //右子树
	}
}

void CreateBinTree(pBTNode* pRoot, BTDataType array[], int size, BTDataType invalid)
{
	int index = 0;	//每次递归需将索引值进行更新，即传地址
	_CreateBinTree(pRoot, array, size, &index, invalid);//辅助函数递归的实现创建左右子树
}

pBTNode CopyBinTree(pBTNode pRoot)	//前序遍历
{
	pBTNode pNewRoot = NULL;
	if (pRoot)
	{
		//拷贝根节点
		pNewRoot = BTBuyNode(pRoot->_data);
		//拷贝当前树左子树
		if (pRoot->_pLeft)	//如果根节点的左子树为空，不进行拷贝，提高效率
		{
			pNewRoot->_pLeft = CopyBinTree(pRoot->_pLeft);
		}
		//拷贝当前树右子树
		if (pRoot->_pRight)
		{
			pNewRoot->_pRight = CopyBinTree(pRoot->_pRight);
		}
	}
	return pNewRoot;
}

void PreOrder(pBTNode pRoot)	//前序递归  根---左----右		O(N)   O(N)
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
#if 0		//法1
	Stack s;
	pBTNode pTop = NULL;
	if (NULL == pRoot)
		return;
	InitStack(&s);
	
	PushStack(&s, pRoot);		//先压栈根节点
	while (!StackEmpty(&s))
	{
		pTop = TopStack(&s);	//遍历当前节点
		printf("%c ", pTop->_data);
		PopStack(&s);		//将当前节点出栈

		if (NULL != pTop->_pRight)			//先压栈右子树
			PushStack(&s, pTop->_pRight);
		if (NULL != pTop->_pLeft)			//压栈左子树
			PushStack(&s, pTop->_pLeft);
	}
	printf("\n");
#endif
//法2
	Stack s;
	pBTNode pCur = NULL;
	if (NULL == pRoot)
		return;
	InitStack(&s);
	PushStack(&s, pRoot);
	while (!StackEmpty(&s))		
	{
		pCur = TopStack(&s);	//保存栈顶
		PopStack(&s);			//出栈
		while (pCur)
		{
			printf("%c ", pCur->_data);				//遍历当前结点
			if (pCur->_pRight)						//保存当前节点的右子树
				PushStack(&s, pCur->_pRight);
			pCur = pCur->_pLeft;
		}
	}
	printf("\n");
}

void InOrder(pBTNode pRoot)		//中序递归   左----根----右
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
	//pCur标记当前的结点，如果pCur为空说明该节点的左右子树都为空，不需入栈，此时需要检查栈的状态
	while (pCur || !StackEmpty(&s))
	{
		while (pCur)	//找当前树中最左侧的结点并保存所经路径中的所有节点
		{
			PushStack(&s, pCur);
			pCur = pCur->_pLeft;
		}
		pCur = TopStack(&s);
		printf("%c ", pCur->_data);
		PopStack(&s);
		//处理当前元素的右子树，回到循环开始，去找到右子树的最左侧的结点
		pCur = pCur->_pRight;
	}

}

void PostOrder(pBTNode pRoot)		//后序递归    左-----右-----根
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
	pBTNode pPre = NULL;	//标记上一次访问过的结点
	pBTNode pTop = NULL;	//标记栈顶结点
	Stack s;
	if (NULL == pRoot)
	{
		return;
	}
	InitStack(&s);
	pCur = pRoot;
	while (NULL != pCur || !StackEmpty(&s))		//pc指向空并且栈为空则说明树遍历结束
	{
		while (pCur)	//找到最左边的结点，路径上的元素压栈
		{
			PushStack(&s, pCur);
			pCur = pCur->_pLeft;
		}
		pTop = TopStack(&s);
		//栈顶结点没有右子树或者当前节点的右子树已经被访问过，就访问当前结点，出栈
		if (NULL == pTop->_pRight || pTop->_pRight == pPre)
		{
			printf("%c ", pTop->_data);
			pPre = pTop;			//将访问过的结点标记
			PopStack(&s);
		}
		else			//否则循环的访问其右子树
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
	QueuePush(&q, pRoot);		//先将根节点入队列

	while (!QueueEmpty(&q))		//队列为空则说明层序遍历结束
	{
		pHead = QueueFront(&q);		//取队头
		printf("%c  ", pHead->_data);
		if (pHead->_pLeft)		//保存左子树
		{
			QueuePush(&q, pHead->_pLeft);
		}
		if (pHead->_pRight)		//保存右子树
		{
			QueuePush(&q, pHead->_pRight);
		}
		QueuePop(&q);
	}
	printf("\n");
	QueueDestory(&q);		//队列需要销毁
}



void DestoryBinTree(pBTNode *ppRoot)	//后序销毁树，最后需要改变根节点的指向，传二级指针
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

int GetLevelNodeCount(pBTNode pRoot, int k)//第K层结点个数
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


void Mirror(pBTNode pRoot)			//先序
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

void Mirror_Nor(pBTNode pRoot)		//验证镜像成功----镜像两次
{
	Queue q;
	pBTNode pTmp = NULL;
	pBTNode pHead = NULL;	//标记队头元素
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

int IsCompleteBinTree(pBTNode pRoot)		//判断完全二叉树, 借助队列
{
	Queue q;
	pBTNode pHead = NULL;
	int flag = 0;					//标记找到的特殊结点（从该特殊结点开始后面的节点不能右左右子树）
	if (NULL == pRoot)
	{
		return 1;
	}
	QueueInit(&q);
	QueuePush(&q, pRoot);//将根节点入队列
	while (!QueueEmpty(&q))		//队列为空，说明
	{
		pHead = QueueFront(&q);
		if (1 == flag)		//特殊结点的下一个节点
		{
			if (pHead->_pLeft || pHead->_pRight)
			return 0;
		}
		else
		{
			if (pHead->_pLeft && pHead->_pRight)	//既有左孩子又有右孩子，不是要找的特殊结点
			{
				QueuePush(&q, pHead->_pLeft);
				QueuePush(&q, pHead->_pRight);
				flag = 0;
			}
			else if (pHead->_pLeft)			//只有左孩子
			{
				QueuePush(&q, pHead->_pLeft);
				flag = 1;
			}
			else if (pHead->_pRight)		//只有右孩子
				return 0;
			else						//左右孩子都没有
				flag = 1;
		}
		QueuePop(&q);
	}
	return 1;
}

pBTNode Find(pBTNode pRoot, BTDataType data)		//查找值为data的元素
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
	if (pRoot == pNode)		//根节点双亲认为NULL
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

int FindInOrder(BTDataType array[], int left, int right, BTDataType to_find)	//在数组中查找结点
{
	int i = left;
	for (; i < right; i++)
	{
		if (to_find == array[i])
		{
			return i;
		}
	}
	return -1;	//不能返回0！		
}


pBTNode _ReBuildTree(BTDataType pre_order[], int pre_order_size, int* index,
	BTDataType in_order[], int in_order_left, int in_order_right)
{
	assert(NULL != index);
	int IdxCurInInOrder = 0;			//当前结点在中序遍历结果中的位置
	if (in_order_left >= in_order_right)//说明中序遍历序列为空，即当前树没有左子树
	{
		return NULL;
	}
	if (*index >= pre_order_size)		//说明先序遍历结束，树还原结束
	{
		return NULL;
	}
	//取先序遍历的值创建新的结点
	pBTNode NewNode = BTBuyNode(pre_order[*index]);
	//假设取出的NewNode的值是A的话，接下来递归的时候需要取出的节点为B

	IdxCurInInOrder = FindInOrder(in_order,in_order_left, in_order_right, pre_order[*index]);
	assert(IdxCurInInOrder != -1);		//找不到当前的结点，说明中序遍历结果传错了
	//必须先查找中序遍历的区间在进行index的自增
	++(*index);
	
	NewNode->_pLeft =  _ReBuildTree(pre_order, pre_order_size, index, in_order, in_order_left, IdxCurInInOrder);	//递归的处理当前结点的左子树
	NewNode->_pRight = _ReBuildTree(pre_order, pre_order_size, index, in_order, IdxCurInInOrder + 1, in_order_right);	//递归的处理当前结点的右子树
	return NewNode;
}

pBTNode ReBuildTree(BTDataType pre_order[], int pre_order_size,
	BTDataType in_order[], int in_order_size)		//由先序遍历和中序遍历的结果还原一个二叉树
{
	int index = 0;		//先序遍历的当前下标
	pBTNode NewNode = _ReBuildTree(pre_order, pre_order_size, &index, in_order, 0, in_order_size);	//辅助函数实现递归
	return NewNode;
}


void TestReBuildTree()
{
	BTDataType pre_order[] = "abdegcf";
	BTDataType in_order[] = "dbgeacf";
	pBTNode NewNode= ReBuildTree(pre_order, strlen(pre_order), in_order, strlen(in_order));

	printf("先序遍历:\n");
	PreOrder(NewNode);
	printf("\n");

	printf("中序遍历:\n");
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
	printf("前序：");
	PreOrderNor(pRoot);
	printf("\n");
	printf("中序：");
	InOrderNor(pRoot);
	printf("\n");
	printf("后序：");
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