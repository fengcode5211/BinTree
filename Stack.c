#include "Stack.h"
#include <stdio.h>
#include <assert.h>


void InitStack(Stack *S)
{
	int i = 0;
	assert(S);

	S->_size = 0;
}

void PushStack(Stack *S, SDataType data)
{
	assert(S);
	if (S->_size == MAX_SIZE)
	{
		return;
	}
	S->_array[S->_size++] = data;
}

void PopStack(Stack *S)
{
	assert(S);
	if (StackEmpty(S))
	{
		return;
	}
	S->_size--;
}

int SizeStack(Stack *S)
{
	assert(S);
	return S->_size;
}

int StackEmpty(Stack* S)
{
	assert(S);
	return 0 == S->_size;
}

SDataType TopStack(Stack *S)
{
	assert(S);
	return S->_array[S->_size - 1];
}

void StackPrint(Stack *S)
{
	int i = 0;
	assert(S);
	for (; i < S->_size; i++)
	{
		printf("%d--->", S->_array[i]);
	}
	printf("\n");
}
