#include "bookManager.h"
/*
* 初始化队列
* SqQueue &Q     操作的队列
* int size       队列的容量
*/
Status InitQueue_Sq(SqQueue &Q, int size) {
	Q.elem = (ElemType *)malloc(size * sizeof(ElemType));   //分配内存空间
	if (NULL != Q.elem)                                    //初始化队列变量
	{
		Q.front = Q.rear = 0;
		Q.maxSize = size;
		return OK;
	}
	else  return OVERFLOW;
}
/*
*  销毁队列Q，Q不再存在
*  SqQueue &Q 操作的队列
*/
Status DestroyQueue_Sq(SqQueue &Q)
{
	if (NULL != Q.elem)
	{
		free(Q.elem);
		//free(&Q);
		return OK;
	}
	else return ERROR;
}

/*
* 将Q置为空队列
* SqQueue Q 操作队列
*/
void ClearQueue_Sq(SqQueue &Q)
{
	if (Q.front != Q.rear)
	{
		Q.rear = Q.front;
	}
}

/*
* 若队列Q为空队列则返回TRUE，否则FALSE
* SqQueue Q 循环队列
*/
Status QueueEmpty_Sq(SqQueue Q)
{
	if (Q.front == Q.rear)return TRUE;
	else return FALSE;
}

/*
* 返回队列Q中元素个数，即队列的长度
* SqQueue Q 循环队列
*/
int QueueLength_Sq(SqQueue Q)
{
	int length = Q.rear - Q.front;
	if (length < 0)length += Q.maxSize;   //判断是否尾标小于头标
	return length;
}

/*
* 若队列不空，则用e返回Q的队列头元素，并返回OK，否则ERROR
* SqQueue &Q 循环队列
* ElemType e 返回头元素
*/
Status GetHead_Sq(SqQueue &Q, ElemType e)
{
	/*判断队列是否为空*/
	if (Q.front == Q.rear)return ERROR;
	/*把队列头元素赋值给e，返回OK*/
	e = Q.elem[Q.front];
	return OK;
}

/*
* 在当前队列的尾元素之后插入元素e为新的队列尾元素
* SqQueue &Q 循环队列
* ElemType e 插入的元素e
*/
Status EnQueue_Sq(SqQueue &Q, ElemType e)
{
	/*判断该队列是否为满*/
	if (Q.front == (Q.rear + 1) % Q.maxSize)return ERROR;
	/*插入元素e到队列尾，并且rear后移一位,返回OK*/
	Q.elem[Q.rear] = e;
	Q.rear = (Q.rear + 1) % Q.maxSize;
	return OK;
}
/*
* 若队列不空则删除当前队列Q中的头元素，用e返回其值，并返回OK；否则ERROR
* SqQueue &Q   循环队列
* ElemType &e  被删除的元素
*/
Status DeQueue_Sq(SqQueue &Q, ElemType &e)
{
	/*判断队列是否为空*/
	if (Q.front == Q.rear)return ERROR;
	/*获得队头元素，队头位标后移一位，并返回OK*/
	e = Q.elem[Q.front];
	Q.front = (Q.front + 1) % Q.maxSize;
	return OK;
}