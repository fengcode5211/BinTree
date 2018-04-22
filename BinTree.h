#pragma once 

typedef char BTDataType;

typedef struct BinTreeNode{
	struct BinTreeNode* _pLeft;
	struct BinTreeNode* _pRight;
	BTDataType _data;
}BTNode, *pBTNode;


pBTNode BTBuyNode(BTDataType data);
void InitBinTree(pBTNode *root);

/* 创建二叉树 */
void _CreateBinTree(pBTNode* pRoot, BTDataType array[], int size, int* index, BTDataType invalid);
/* 外部用户调用 */
void CreateBinTree(pBTNode* pRoot, BTDataType array[], int size, BTDataType invalid);
/* 拷贝 */
pBTNode CopyBinTree(pBTNode pRoot);
/* 销毁树 */
void DestoryBinTree(pBTNode *ppRoot);



/* 前序递归遍历 */
void PreOrder(pBTNode pRoot);
/* 前序非递归 */
void PreOrderNor(pBTNode pRoot);
/* 中序递归 */
void InOrder(pBTNode pRoot);
/* 中序非递归 */
void InOrderNor(pBTNode pRoot);
/* 后序递归 */
void PostOrder(pBTNode pRoot);
/* 后序非递归 */
void PostOrderNor(pBTNode pRoot);
/* 层序遍历二叉树 */
void LevelOrder(pBTNode pRoot);

/* 二叉树镜像递归 */
void Mirror(pBTNode pRoot);
/* 二叉树镜像非递归 */
void Mirror_Nor(pBTNode pRoot);
/* 判断一棵树是否为完全二叉树 */
int IsCompleteBinTree(pBTNode pRoot);
/* 在二叉树中查找值为data的结点 */
pBTNode Find(pBTNode pRoot, BTDataType data);
/*  判断一个节点是否在二叉树中 */
int IsNodeInBinTree(pBTNode pRoot, pBTNode pNode);
/* 获取当前节点的左孩子 */
pBTNode LeftChild(pBTNode pNode);
/*  获取当前节点的右孩子 */
pBTNode RightChild(pBTNode pNode);
/*  获取当前结点的双亲结点 */
pBTNode Parent(pBTNode pRoot, pBTNode pNode);
/*  由先序遍历和中序遍历的结果还原一个二叉树   */
pBTNode ReBuildTree(BTDataType pre_order[], int pre_order_size,
	BTDataType in_order[], int in_order_size);




int SizeBinTree(pBTNode pRoot);		//结点个数
int GetLeafCount(pBTNode pRoot);	//叶子节点个数
int GetLevelNodeCount(pBTNode pRoot, int k); //第K层结点个数
int Height(pBTNode pRoot);			//获取二叉树高度


void   TestBinTree();
void TestReBuildTree();