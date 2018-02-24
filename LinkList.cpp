#include "bookManager.h"


/*
* ��������L���ͷ��ڴ���Դ
* LinkList &L Ҫ���ٵ�����L
*/
Status DestroyList_L(LinkList &L)
{
	if (NULL == L)return ERROR;     //����Ϊ������ʱ������ERROR
	LinkList p1 = L, p2 = L->next;  //p1ָ��ǰ��㣬p2ָ����һ���
	while (p1 != NULL)
	{
		free(p1);
		p1 = p2;
		if (p1 != NULL)
			p2 = p2->next;
		else break;
	}
	L = NULL;                      //��ֹ�û��������ͷŵ��ڴ�ռ�
	return OK;
}

/*
* �жϣ�����LΪ�ձ�ʱ����TRUE������FALSE
* LinkList L Ҫ�жϵ�����L
*/
Status ListEmpty_L(LinkList L)
{
	if (NULL == L)return TRUE;
	else return FALSE;
}

/*
* ������ĳ��ȣ�����int length
* LinkList L �󳤶ȵ�����
*/
int ListLength_L(LinkList L)
{
	int length = 0;
	while (L != NULL)
	{
		L = L->next;
		length++;
	}
	return length;
}

/*
* ���ң���������L�е�һ��������ֵΪe�Ľ���ַ�����������򷵻�NULL
* LinkList L   ����������
* ElemType e   ���ҵ�ֵ
*/
LNode* Search_L(LinkList L, ElemType e)
{
	/*����������������ֵ����eʱ�����ش�ʱ����ַ*/
	while (L != NULL)
	{
		if (L->data.cardNum == e.cardNum)
			return L;
		L = L->next;
	}
	return NULL;
}

/*
* ����p����ֱ�Ӻ�̽���ָ�룬��p�����βԪ����򷵻�NULL
* LNode *p
*/
LinkList NextElem_L(LinkList p)
{
	//if(NULL == p)return ERROR;  ��ֵı������
	LinkList p1 = p->next;
	return p1;
}


/*
* ����Ԫ��e�Ľ�㣬����ָ��ý���ָ��
*/
LNode* MakeNode_L(ElemType e)
{
	LinkList p;
	p = (LinkList)malloc(sizeof(LNode));
	if (NULL == p)return NULL;
	p->data = e;
	p->next = NULL;
	return NULL;
}

/*
* ��p���֮�����q���
* LNode *p  Ҫ�����λ��
* LNode *q  Ҫ����Ľ��
*/
Status InsertAfter_L(LNode *p, LNode *q)
{

	if (NULL == p || NULL == q)return ERROR;      //�жϲ����Ƿ�Ϸ�
	q->next = p->next;
	p->next = q;
	return OK;
}

Status DeQueue(LinkList &L, ElemType &e)
{
	if (NULL == L)return ERROR;
	LinkList p = L;
	e = p->data;
	L = p->next;
	free(p);
	return OK;
}
/*��β���*/
Status EnQueue(LinkList &L, ElemType e)
{
	LinkList p1 = L, t, p2 = NULL;
	while (p1 != NULL) //���������ҵ���β
	{
		p2 = p1;
		p1 = p1->next;
	}
	/*�����¼���Ľ��*/
	t = (LinkList)malloc(sizeof(LNode));
	if (NULL == t)return OVERFLOW;
	t->data = e;
	t->next = NULL;
	if (NULL == p2)L = t;
	else p2->next = t;
	return OK;
}
/*����һ���յĵ�����*/
Status InitList(LinkList &L)
{
	L = NULL;
	return OK;
}
Status create(LinkList &L, ElemType *data, int n)
{
	InitList(L);
	if (n <= 0)return ERROR;                           //��������Ƿ�Ϸ�
	while (n >= 0)
	{
		InsertAfter_L(L, MakeNode_L(data[--n]));
	}
	return OK;
}