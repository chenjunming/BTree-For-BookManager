#include "bookManager.h"


/*
* 销毁链表L，释放内存资源
* LinkList &L 要销毁的链表L
*/
Status DestroyList_L(LinkList &L)
{
	if (NULL == L)return ERROR;     //链表为空链表时，返回ERROR
	LinkList p1 = L, p2 = L->next;  //p1指向当前结点，p2指向下一结点
	while (p1 != NULL)
	{
		free(p1);
		p1 = p2;
		if (p1 != NULL)
			p2 = p2->next;
		else break;
	}
	L = NULL;                      //防止用户调用已释放的内存空间
	return OK;
}

/*
* 判断：链表L为空表时返回TRUE，否则FALSE
* LinkList L 要判断的链表L
*/
Status ListEmpty_L(LinkList L)
{
	if (NULL == L)return TRUE;
	else return FALSE;
}

/*
* 求链表的长度，返回int length
* LinkList L 求长度的链表
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
* 查找，返回链表L中第一个数据域值为e的结点地址，若不存在则返回NULL
* LinkList L   遍历的链表
* ElemType e   查找的值
*/
LNode* Search_L(LinkList L, ElemType e)
{
	/*遍历链表，当数据域值等于e时，返回此时结点地址*/
	while (L != NULL)
	{
		if (L->data.cardNum == e.cardNum)
			return L;
		L = L->next;
	}
	return NULL;
}

/*
* 返回p结点的直接后继结点的指针，若p结点是尾元结点则返回NULL
* LNode *p
*/
LinkList NextElem_L(LinkList p)
{
	//if(NULL == p)return ERROR;  奇怪的编译错误
	LinkList p1 = p->next;
	return p1;
}


/*
* 构造元素e的结点，返回指向该结点的指针
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
* 在p结点之后插入q结点
* LNode *p  要插入的位置
* LNode *q  要插入的结点
*/
Status InsertAfter_L(LNode *p, LNode *q)
{

	if (NULL == p || NULL == q)return ERROR;      //判断参数是否合法
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
/*队尾入队*/
Status EnQueue(LinkList &L, ElemType e)
{
	LinkList p1 = L, t, p2 = NULL;
	while (p1 != NULL) //遍历链表找到队尾
	{
		p2 = p1;
		p1 = p1->next;
	}
	/*创建新加入的结点*/
	t = (LinkList)malloc(sizeof(LNode));
	if (NULL == t)return OVERFLOW;
	t->data = e;
	t->next = NULL;
	if (NULL == p2)L = t;
	else p2->next = t;
	return OK;
}
/*构造一个空的单链表*/
Status InitList(LinkList &L)
{
	L = NULL;
	return OK;
}
Status create(LinkList &L, ElemType *data, int n)
{
	InitList(L);
	if (n <= 0)return ERROR;                           //检验参数是否合法
	while (n >= 0)
	{
		InsertAfter_L(L, MakeNode_L(data[--n]));
	}
	return OK;
}