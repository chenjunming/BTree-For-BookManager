#include "bookManager.h"
/*
 * 构造空树T
 * CSTree &T 返回构造后的空树
 */
Status InitTree(CSTree &T)
{
	T = NULL;
	return OK;
}

/*
* 创建根结点e和n棵子树的树
* TElemType e  根结点的值
* int n,...    n棵子树的结点指针
* 返回根结点的指针
*/
CSTree MakeTree(TElemType e, int n, ...)
{
	int i;
	CSTree t = NULL, p, pi;
	va_list argptr;             //argptr是存放变长参数表信息的数组
	t = (CSTree)malloc(sizeof(CSTNode));
	if (NULL == t)return NULL;
	t->data = e;
	t->firstChild = t->nextSibling = NULL;
	if (n <= 0)return t;           //若无子树，则返回根结点
	va_start(argptr, n);         //令argptr指向参数n后的第一个实参
	p = va_arg(argptr, CSTree);  //取第一棵子树的实参并转换成CSTree类型
	t->firstChild = p;
	pi = p;
	for (i = 1; i<n; i++)
	{   //将n棵树作为根结点的子树插入
		p = va_arg(argptr, CSTree);//取下一棵子树的实参并转换为CSTree类型
		pi->nextSibling = p;
		pi = p;
	}
	va_end(argptr);//取实参结束     
	return t;
}
/*
* 销毁树T
* CSTree &T 要被销毁的树T
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
* 返回树T的深度
* CSTree &T    要求深度的树
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
* 查找树T中的结点e并返回其指针（广度查找法）
* CSTree T    要查找的树T
* TElemType e    要查找的值
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
* 插入c为T的第i棵子树，c非空并与T不相交
* CSTree &T    被插入的树T
* int i        位置为i
* CSTree c        要插入的子树c
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
* 删除T的第i棵子树
* CSTree &T    被删除的树T
* int i        删除子树的位置i
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
* CSTree &T    被删除的树T
* int i        删除子树的位置i
*/
Status deleteCSTree(CSTree p,CSTree &T, TElemType e)
{
	CSTree tp = NULL, fp = NULL;//前指针
	if (T == NULL)return ERROR;
	if (strcmp(T->data.writer, e.writer) == 0) {
		//如果是双亲
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
			if (strcmp(tp->data.writer, e.writer) == 0)//如果著者相同
			{
				MakeTree(e, 0);
				InsertChild(tp, 1, p);
				sign = 1;
				break;
			}
			fp = tp;
			tp = tp->nextSibling;
		} while (tp != NULL);
		if (sign == 0)//表示还没插入
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
	if (strcmp(T->data.writer, writer) == 0) {//如果找到该著者
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
	else {//如果找不到
		T = T->nextSibling;
		return findWriter(T, writer);
	}
}