#include "bookManager.h"
/*
* ��ʼ������
* SqQueue &Q     �����Ķ���
* int size       ���е�����
*/
Status InitQueue_Sq(SqQueue &Q, int size) {
	Q.elem = (ElemType *)malloc(size * sizeof(ElemType));   //�����ڴ�ռ�
	if (NULL != Q.elem)                                    //��ʼ�����б���
	{
		Q.front = Q.rear = 0;
		Q.maxSize = size;
		return OK;
	}
	else  return OVERFLOW;
}
/*
*  ���ٶ���Q��Q���ٴ���
*  SqQueue &Q �����Ķ���
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
* ��Q��Ϊ�ն���
* SqQueue Q ��������
*/
void ClearQueue_Sq(SqQueue &Q)
{
	if (Q.front != Q.rear)
	{
		Q.rear = Q.front;
	}
}

/*
* ������QΪ�ն����򷵻�TRUE������FALSE
* SqQueue Q ѭ������
*/
Status QueueEmpty_Sq(SqQueue Q)
{
	if (Q.front == Q.rear)return TRUE;
	else return FALSE;
}

/*
* ���ض���Q��Ԫ�ظ����������еĳ���
* SqQueue Q ѭ������
*/
int QueueLength_Sq(SqQueue Q)
{
	int length = Q.rear - Q.front;
	if (length < 0)length += Q.maxSize;   //�ж��Ƿ�β��С��ͷ��
	return length;
}

/*
* �����в��գ�����e����Q�Ķ���ͷԪ�أ�������OK������ERROR
* SqQueue &Q ѭ������
* ElemType e ����ͷԪ��
*/
Status GetHead_Sq(SqQueue &Q, ElemType e)
{
	/*�ж϶����Ƿ�Ϊ��*/
	if (Q.front == Q.rear)return ERROR;
	/*�Ѷ���ͷԪ�ظ�ֵ��e������OK*/
	e = Q.elem[Q.front];
	return OK;
}

/*
* �ڵ�ǰ���е�βԪ��֮�����Ԫ��eΪ�µĶ���βԪ��
* SqQueue &Q ѭ������
* ElemType e �����Ԫ��e
*/
Status EnQueue_Sq(SqQueue &Q, ElemType e)
{
	/*�жϸö����Ƿ�Ϊ��*/
	if (Q.front == (Q.rear + 1) % Q.maxSize)return ERROR;
	/*����Ԫ��e������β������rear����һλ,����OK*/
	Q.elem[Q.rear] = e;
	Q.rear = (Q.rear + 1) % Q.maxSize;
	return OK;
}
/*
* �����в�����ɾ����ǰ����Q�е�ͷԪ�أ���e������ֵ��������OK������ERROR
* SqQueue &Q   ѭ������
* ElemType &e  ��ɾ����Ԫ��
*/
Status DeQueue_Sq(SqQueue &Q, ElemType &e)
{
	/*�ж϶����Ƿ�Ϊ��*/
	if (Q.front == Q.rear)return ERROR;
	/*��ö�ͷԪ�أ���ͷλ�����һλ��������OK*/
	e = Q.elem[Q.front];
	Q.front = (Q.front + 1) % Q.maxSize;
	return OK;
}