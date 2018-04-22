#pragma once 

typedef char BTDataType;

typedef struct BinTreeNode{
	struct BinTreeNode* _pLeft;
	struct BinTreeNode* _pRight;
	BTDataType _data;
}BTNode, *pBTNode;


pBTNode BTBuyNode(BTDataType data);
void InitBinTree(pBTNode *root);

/* ���������� */
void _CreateBinTree(pBTNode* pRoot, BTDataType array[], int size, int* index, BTDataType invalid);
/* �ⲿ�û����� */
void CreateBinTree(pBTNode* pRoot, BTDataType array[], int size, BTDataType invalid);
/* ���� */
pBTNode CopyBinTree(pBTNode pRoot);
/* ������ */
void DestoryBinTree(pBTNode *ppRoot);



/* ǰ��ݹ���� */
void PreOrder(pBTNode pRoot);
/* ǰ��ǵݹ� */
void PreOrderNor(pBTNode pRoot);
/* ����ݹ� */
void InOrder(pBTNode pRoot);
/* ����ǵݹ� */
void InOrderNor(pBTNode pRoot);
/* ����ݹ� */
void PostOrder(pBTNode pRoot);
/* ����ǵݹ� */
void PostOrderNor(pBTNode pRoot);
/* ������������� */
void LevelOrder(pBTNode pRoot);

/* ����������ݹ� */
void Mirror(pBTNode pRoot);
/* ����������ǵݹ� */
void Mirror_Nor(pBTNode pRoot);
/* �ж�һ�����Ƿ�Ϊ��ȫ������ */
int IsCompleteBinTree(pBTNode pRoot);
/* �ڶ������в���ֵΪdata�Ľ�� */
pBTNode Find(pBTNode pRoot, BTDataType data);
/*  �ж�һ���ڵ��Ƿ��ڶ������� */
int IsNodeInBinTree(pBTNode pRoot, pBTNode pNode);
/* ��ȡ��ǰ�ڵ������ */
pBTNode LeftChild(pBTNode pNode);
/*  ��ȡ��ǰ�ڵ���Һ��� */
pBTNode RightChild(pBTNode pNode);
/*  ��ȡ��ǰ����˫�׽�� */
pBTNode Parent(pBTNode pRoot, pBTNode pNode);
/*  �������������������Ľ����ԭһ��������   */
pBTNode ReBuildTree(BTDataType pre_order[], int pre_order_size,
	BTDataType in_order[], int in_order_size);




int SizeBinTree(pBTNode pRoot);		//������
int GetLeafCount(pBTNode pRoot);	//Ҷ�ӽڵ����
int GetLevelNodeCount(pBTNode pRoot, int k); //��K�������
int Height(pBTNode pRoot);			//��ȡ�������߶�


void   TestBinTree();
void TestReBuildTree();