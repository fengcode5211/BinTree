#pragma once 

//#include "BinTree.h"
//typedef pBTNode SDataType;


extern struct BinTreeNode;
typedef struct BinTreeNode* SDataType;


#define MAX_SIZE 100

typedef struct Stack{
	SDataType _array[MAX_SIZE];
	int _size;
}Stack;


void InitStack(Stack *S);
void PushStack(Stack *S, SDataType data);		// ±º‰∏¥‘”∂»O(1)
void PopStack(Stack *S);							//O(1)
int FindStack(Stack *S, SDataType data);
int SizeStack(Stack *S);
int StackEmpty(Stack* S);

SDataType TopStack(Stack *S);

void StackPrint(Stack *S);
