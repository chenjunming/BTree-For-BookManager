#include "bookManager.h"
/*
 * �������T
 * CSTree &T ���ع����Ŀ���
 */
Status InitTree(CSTree &T)
{
	T = NULL;
	return OK;
}

/*
* ���������e��n����������
* TElemType e  ������ֵ
* int n,...    n�������Ľ��ָ��
* ���ظ�����ָ��
*/
CSTree MakeTree(TElemType e, int n, ...)
{
	int i;
	CSTree t = NULL, p, pi;
	va_list argptr;             //argptr�Ǵ�ű䳤��������Ϣ������
	t = (CSTree)malloc(sizeof(CSTNode));
	if (NULL == t)return NULL;
	t->data = e;
	t->firstChild = t->nextSibling = NULL;
	if (n <= 0)return t;           //�����������򷵻ظ����
	va_start(argptr, n);         //��argptrָ�����n��ĵ�һ��ʵ��
	p = va_arg(argptr, CSTree);  //ȡ��һ��������ʵ�β�ת����CSTree����
	t->firstChild = p;
	pi = p;
	for (i = 1; i<n; i++)
	{   //��n������Ϊ��������������
		p = va_arg(argptr, CSTree);//ȡ��һ��������ʵ�β�ת��ΪCSTree����
		pi->nextSibling = p;
		pi = p;
	}
	va_end(argptr);//ȡʵ�ν���     
	return t;
}
/*
* ������T
* CSTree &T Ҫ�����ٵ���T
*/
Status DestroyTree(CSTree &T)
{
	if (NULL != T)
	{
		DestroyTree(T->firstChild);
		DestroyTree(T->nextSibling);
		free(T);
	}
	return OK;
}
/*
* ������T�����
* CSTree &T    Ҫ����ȵ���
*/
int TreeDepth(CSTree T)
{
	int dep = 1;
	CSTree Tp = T;
	while (Tp != NULL)
	{
		do {
			Tp = Tp->firstChild;
			if (Tp != NULL)
				dep++;
			else break;
		} while (Tp->firstChild != NULL);
		if (Tp != NULL)
			Tp = Tp->nextSibling;
		else break;
	}
	return dep;
}
/*
* ������T�еĽ��e��������ָ�루��Ȳ��ҷ���
* CSTree T    Ҫ���ҵ���T
* TElemType e    Ҫ���ҵ�ֵ
*/
CSTree Search(CSTree T, TElemType e)
{
	CSTree tp;
	if (NULL == T)return NULL;
	if (T->data.num == e.num)return T;
	T = T->firstChild;
	while (T != NULL) {
		tp = T;
		while (T != NULL) {
			if (T->data.num == e.num)return T;
			T = T->nextSibling;
		}
		T = tp->firstChild;
	}
	return NULL;
}
/*
* ����cΪT�ĵ�i��������c�ǿղ���T���ཻ
* CSTree &T    ���������T
* int i        λ��Ϊi
* CSTree c        Ҫ���������c
*/
Status InsertChild(CSTree &T, int i, CSTree c)
{
	int n;
	if (T == NULL || c == NULL || i <= 0)return ERROR;
	CSTree Tp = T->firstChild;
	if (i == 1) {
		T->firstChild = c;
		c->nextSibling = Tp;
		return OK;
	}
	for (n = 2; Tp != NULL && n<i; n++)
	{
		Tp = Tp->nextSibling;
	}
	if (n == i && Tp != NULL) {
		c->nextSibling = Tp->nextSibling;
		Tp->nextSibling = c;
		return OK;
	}
	else return ERROR;
}
/*
* ɾ��T�ĵ�i������
* CSTree &T    ��ɾ������T
* int i        ɾ��������λ��i
*/
Status DeleteChild(CSTree &T, int i)
{
	CSTree Tp = T->firstChild;
	CSTree Tk;
	if (T == NULL || i <1)return ERROR;
	if (i == 1)
	{
		T->firstChild = Tp->nextSibling;
		free(Tp);
		return OK;
	}
	int j;
	for (j = 2; Tp != NULL &&j<i; j++)
	{
		Tp = Tp->nextSibling;
	}
	if (j == i && Tp->nextSibling != NULL) {
		Tk = Tp->nextSibling;
		Tp->nextSibling = Tk->nextSibling;
		free(Tk);
		return OK;
	}
	else return ERROR;
}
/*
* 
* CSTree &T    ��ɾ������T
* int i        ɾ��������λ��i
*/
Status deleteCSTree(CSTree p,CSTree &T, TElemType e)
{
	CSTree tp = NULL, fp = NULL;//ǰָ��
	if (T == NULL)return ERROR;
	if (strcmp(T->data.writer, e.writer) == 0) {
		//�����˫��
		if (T->data.num == e.num) {
			if (T->firstChild != NULL) {
				T->firstChild->firstChild = T->firstChild->nextSibling;
				T->firstChild->nextSibling = T->nextSibling;
				T = T->firstChild;
			}
			else {
				T = T->nextSibling;
			}
			if (p != NULL) {
				p->nextSibling = T;
			}
			return OK;
		}
		else {
			fp = T;
			tp = T->firstChild;
			while (tp->data.num != e.num) {
				fp = tp;
				tp = tp->nextSibling;
			}
			if (tp != T->firstChild)
			{
				fp->nextSibling = tp->nextSibling;
			}
			else {
				T->firstChild = tp->nextSibling;
			}
			return OK;
		}
	}
	else {
		return deleteCSTree(T,T->nextSibling, e);
	}
}
Status insertCSTree(CSTree &T,TElemType e)
{
	CSTree p=MakeTree(e, 0);
	CSTree fp=NULL,tp=T;
	int sign = 0;
	if (T != NULL) {
		do {
			if (strcmp(tp->data.writer, e.writer) == 0)//���������ͬ
			{
				MakeTree(e, 0);
				InsertChild(tp, 1, p);
				sign = 1;
				break;
			}
			fp = tp;
			tp = tp->nextSibling;
		} while (tp != NULL);
		if (sign == 0)//��ʾ��û����
		{
			fp->nextSibling = p;
		}
	}
	else {
		T = p;
	}
	return OK;
}
Status findWriter(CSTree T, char *writer)
{
	if (T == NULL)return ERROR;
	if (strcmp(T->data.writer, writer) == 0) {//����ҵ�������
		CSTree tp = T;
		printf(HEARDER1);
		printf(HEARDER2);
		printf(HEARDER3);
		printf(FORMAT, tp->data.num, tp->data.name, tp->data.writer, tp->data.current, tp->data.total);
		printf(END);
		tp = tp->firstChild;
		while (tp != NULL) {
			printf(FORMAT, tp->data.num, tp->data.name, tp->data.writer, tp->data.current, tp->data.total);
			printf(END);
			tp = tp->nextSibling;
		}
		return SUCCESS;
	}
	else {//����Ҳ���
		T = T->nextSibling;
		return findWriter(T, writer);
	}
}