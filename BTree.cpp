#include "bookManager.h"
extern Status InitQueue_Sq(SqQueue &Q, int size);
extern Status InitList(LinkList &L);
/**
* Description:�ȽϹؼ���
* @param k1 �ؼ���1
* @param k2 �ؼ���2
* @return:int ����-1��ʾk1<k2,0��ʾk1==k2,1��ʾk1>k2
*/
int compareTo(KeyType k1, KeyType k2)
{
	if (k1.num == k2.num)return 0;
	if (k1.num < k2.num)return -1;
	if (k1.num > k2.num)return 1;
}

/**
* Description:��ʼ������
* @param T Ҫ��ʼ����B��
* @return:Status ��ʼ���ɹ�����SUCCESS
*/
Status initBTree(BTree &T)
{
	T = NULL;
	return SUCCESS;
}
/**********************************���Ҳ���start*****************************************/
/**
* Description:��p->key[1...p->keynum]��k����SearchBTree�����ڲ�ʹ��
* @param p ���ڲ��ҵĽ��
* @param k ����Ҫ���ҵĹؼ���
* @return:int ���ز��ҵ�λ��
*/
int search(BTree p, KeyType k)
{
	int i = 1;                                //�ؼ������飬key[0]δ��
	while (i <= p->keynum && compareTo(k, p->key[i]) > 0)i++;  //����ҪС�ڽ�㵱ǰ�ؼ��ֵĸ������ҹؼ���ҪС�ڹؼ�������ĵ�ǰԪ��
	return i;                                //���ص��������ڵ�Ԫ��Ҫô���ڹؼ��֣�Ҫô���ڹؼ���
}
/**
* Description:��m��B��T�ϲ��ҹؼ���k����r����һ��result
* @param T Ҫ���ҵ�B��
* @param k Ҫ���ҵĹؼ���
* @param &r ���ز��ҵ��Ľ��
* @return:void
*/
void searchBTree(BTree T, KeyType k, Result &r)
{
	if (NULL == T)return;
	int i, found = 0;                                  //foundΪ0ʱ��ʾδ���ҵ���1��ʾ�ɹ�����
	BTree p = T, q = NULL;                                  //p��ʾ��ǰ�����Ľ�㣬q��ʾp����˫�׽��
	while (p != NULL && found == 0) {                      //�Ҳ���:���������п����иùؼ��ֵ�λ�ã�����foundû�з����ı䣨��û���ҵ���            
		i = search(p, k);                              //ʹ��Search����������ǰ���Ĺؼ������飬������Ӧλ��
		if (i <= p->keynum && compareTo(k, p->key[i]) == 0)found = 1;//������ص������Ϸ���С�ڵ��ڹؼ���ʵ�ʳ��ȣ�������Ҫ���ҵĹؼ����������е�Ԫ��ƥ�䣬���ҵ�
		else {                                          //����q��ס��ǰλ�ã�pָ������
			q = p;
			p = p->ptr[i - 1];
		}
	}
	if (found == 1) {                                      //����ҵ�����װ�����r
		r.pt = p; r.i = i; r.tag = 1;
	}
	else {
		r.pt = q; r.i = i; r.tag = 0;                      //����Ҳ������������λ�õ�r
	}
}
/**********************************���Ҳ���end*****************************************/

/**********************************�������start*****************************************/
/**
* Description:����һ�����
* @param &T ���ش����Ľ�㣬����ʧ�ܷ���NULL
* @param firstchild �ý��ĵ�һ������
* @param key         �ý��Ĺؼ���������ĵ�һ���ؼ���
* @param secondchild�ý��ĵڶ�������
* @return:void
*/
void makeNode(BTree &T, BTree firstchild, KeyType key, BTree secondchild)
{
	T = (BTree)malloc(sizeof(BTNode));                //��������ڴ�
	if (NULL == T)return;
	//��װ��������
	InitList(key.reader);//��ʼ������������
	InitList(key.preBooker);//��ʼ��ԤԼ�߶���
	T->keynum = 1;    T->key[1] = key;    T->parent = NULL;    T->ptr[0] = firstchild;    T->ptr[1] = secondchild;
	if (firstchild != NULL)firstchild->parent = T;    //���������ӵ�˫����ֵ
	if (secondchild != NULL)secondchild->parent = T;
}
/**
* Description:����һ����¼��q����ڵ�(Ҫ����λ�õ���һ��ָ��Ų)
* @param q Ҫ���뵽�Ľ��
* @param i Ҫ�����λ��
* @param x Ҫ����Ĺؼ���
* @param ap Ҫ������º��ӽ��
*/
void insert1(BTree &q, int i, KeyType x, BTree ap)
{
	int j, n = q->keynum;
	if (i <= n) {
		for (j = n; j >= i; j--) {                //ΪҪ����Ĺؼ����ڳ�λ��
			q->key[j + 1] = q->key[j];
			q->ptr[j + 1] = q->ptr[j];
		}
		q->ptr[i] = q->ptr[i - 1];
		q->key[i] = x;                    //����ؼ���
		q->ptr[i - 1] = ap;
		if (ap != NULL)ap->parent = q;
		q->keynum++;
	}
	else {
		q->key[i] = x;
		q->ptr[i] = ap;
		if (ap != NULL)ap->parent = q;
		q->keynum++;
	}
}
/**
* Description:����һ����¼��q����ڵ㣨Ҫ����λ�õ���һ��ָ�벻Ų��
* @param q Ҫ���뵽�Ľ��
* @param i Ҫ�����λ��
* @param x Ҫ����Ĺؼ���
* @param ap Ҫ������º��ӽ��
*/
void insert(BTree &q, int i, KeyType x, BTree ap)
{
	int j, n = q->keynum;
	for (j = n; j >= i; j--) {                //ΪҪ����Ĺؼ����ڳ�λ��
		q->key[j + 1] = q->key[j];
		q->ptr[j + 1] = q->ptr[j];
	}
	q->key[i] = x;                    //����ؼ���
	q->ptr[i] = ap;
	if (ap != NULL)ap->parent = q;
	q->keynum++;
}
/**
* Description:�ӽ��p��ʼ��˫�׵ݹ���ѣ�ֱ������������B���Ķ���
* @param &p ��ǰҪ���ѵĽ��
* @return:Status ���ѳɹ�����SUCCESS,ʧ�ܷ���ERROR
*/
Status split(BTree &p)
{
	while (p != NULL && p->keynum >= m) {
		BTree t;
		t = (BTree)malloc(sizeof(BTNode));//����һ�½��
		int n = (p->keynum + 1) / 2;                //nΪ�м�λ��
		int i, j;
		t->keynum = p->keynum - n;                //��ʼ��װ�½�������
		t->parent = p->parent;
		t->ptr[0] = p->ptr[n];

		for (i = n + 1, j = 1; i <= p->keynum; i++, j++)
		{
			t->key[j] = p->key[i];//�ѹؼ��ַŵ��½����
			t->ptr[j] = p->ptr[i];//�Ѻ��ӽ��ŵ��½����
		}
		//�޸��½����ӽڵ��parent��
		for (i = 0; i <= p->keynum - n; i++)
			if (t->ptr[i] != NULL)t->ptr[i]->parent = t;
		p->keynum = n - 1;
		//˫�׽�����p����м�λ�õĹؼ���
		if (p->parent == NULL)
		{
			BTree np;
			makeNode(np, p, p->key[n], t);
			//printf("�ؼ�����%d\n",p->key[n]);
			p = np;
			break;
		}
		else {
			i = search(p->parent, p->key[n]);
			insert(p->parent, i, p->key[n], t);
			p = p->parent;
		}
	}
	return OK;
}
/**
* Description:����һ����¼��T���B����
* @param T Ҫ�����B��
* @param key Ҫ����Ĺؼ���
* @return:Status ����ɹ�����SUCCESS,ʧ�ܷ���ERROR
*/
Status insertBTree(BTree &T, KeyType key)
{
	int finished = 0;
	BTree p;
	if (NULL == T)makeNode(T, NULL, key, NULL);    //�������Ϊ�գ��½�һ�������Ϊ����㲢����
	else {
		Result r;
		searchBTree(T, key, r);
		if (r.tag == 1) {//���ҳɹ�,֤���ü�¼�Ѵ��ڣ��޷�����
			return ERROR;
		}
		else {           //����ʧ�ܣ����Բ���
			p = r.pt;                            //��¼����㵽p
			insert(r.pt, r.i, key, NULL);            //�Ȳ���
			if (r.pt->keynum < m)finished = 1;        //�������
			else {//Ҫ���p����
				split(p);
			}
			while (p->parent != NULL)p = p->parent;
			T = p;

			return OK;
		}
	}

	return OK;
}
/**
* Description:��������key�����е�Ԫ�ص�T���B����
* @param T Ҫ�����B��
* @param key Ҫ���������
* @return:Status ����ɹ�����SUCCESS,ʧ�ܷ���ERROR
*/
Status insertBTreeAll(BTree &T, KeyType key[], int len)
{
	int i;
	for (i = 0; i < len; i++)
	{
		insertBTree(T, key[i]);
	}
	return SUCCESS;
}
/**********************************�������end*****************************************/
/**********************************ɾ������start***************************************/

/**
* Description:��Ai�������ҳ����²��ն˽�����С�ؼ������Ki
* @param p Ҫ�����滻����������˫�׽��
* @param i Ҫ�滻�Ĺؼ��ֵ�����λ��
* @return:void
*/
void Successor(BTree &p, int i)
{
	BTree T = p;
	p = T->ptr[i];//��õ�i�������ĸ�
	while (p->ptr[0] != NULL)//������ҵ����²��ն˽��
	{
		p = p->ptr[0];
	}
	//�滻
	T->key[i] = p->key[1];
}
/**
* Description:�ӽ��p��ɾ��key[i]
* @param T Ҫ����ɾ�������Ľ��p
* @param i Ҫɾ���Ĺؼ��ֵ�λ��
* @return:void
*/
void Remove(BTree &p, int i)
{
	int j;
	if (i == p->keynum) { p->keynum--; return; }
	for (j = i; j < p->keynum; j++)
	{
		p->key[j] = p->key[j + 1];
		p->ptr[j - 1] = p->ptr[j];
	}
	p->ptr[j - 1] = p->ptr[j];
	p->keynum--;
}
void Restore(BTree &T, BTree &p, int i);
/**
* Description:���Ϻϲ����
* @param p Ҫɾ���Ĺؼ��ֵĽ��
* @param i Ҫɾ���Ĺؼ��ֵ�λ��
* @return:void
*/
void combine(BTree &T, BTree &p)
{
	//�ҵ��ý��������ֵ�
	BTree pp = p->parent;
	BTree ps;
	int j;
	if (pp == NULL)
	{
		if (p->ptr[0]->keynum != 0)T = p->ptr[0];
		else if (p->ptr[1]->keynum != 0)T = p->ptr[1];
		else  return;
		T->parent = NULL;
		return;
	}
	for (j = 0; j <= pp->keynum; j++)
	{
		if (pp->ptr[j] == p)break;
	}//pp->ptr[j]Ϊp
	 //�ϲ�p��pp�ĵ�i�ؼ��֣����ң��ֵܽ�㵽���ң��ֵܽ��
	if (j > 0) {//���ֵ�
				//����pp�ĵ�j�ؼ��ֵ����ֵ�
		ps = pp->ptr[j - 1];
		insert1(ps, ps->keynum + 1, pp->key[j], NULL);
		//Remove(pp, j);
		//����p��ʣ��ؼ��ֵ����ֵ�
		if (p->keynum != 0) {
			int k;
			for (k = 1; k <= p->keynum; k++) {
				insert(ps, ps->keynum + 1, p->key[k], p->ptr[k]);
				Remove(p, k);
			}
		}
		else {
			if (p->ptr[1] != NULL && p->ptr[1]->keynum != 0)
			{
				ps->ptr[ps->keynum] = p->ptr[1];
				p->ptr[1]->parent = ps;
			}
			else {
				ps->ptr[ps->keynum] = p->ptr[0];
				if (p->ptr[0] != NULL)
					p->ptr[0]->parent = ps;
			}
			if (T == pp && p->keynum != 0 && p->ptr[1] != NULL)p->ptr[0]->parent = ps;
		}
		Remove(pp, j);
		pp->ptr[j - 1] = ps;
		if (pp->keynum < (m / 2))
		{
			//combine(T, pp);
			if (pp->parent != NULL)
				Restore(T, pp, j);
			else {
				ps->parent = NULL;
				T = ps;
			}
		}
	}
	else {//���ֵ�
		  //����pp�ĵ�j+1�ؼ��ֵ����ֵ�
		ps = pp->ptr[j + 1];
		insert1(ps, 1, pp->key[j + 1], NULL);
		//Remove(pp, j);
		//����p��ʣ��ؼ��ֵ����ֵ�
		if (p->keynum != 0) {
			int k;
			for (k = 1; k <= p->keynum; k++) {
				insert(ps, 1, p->key[k], p->ptr[k - 1]);
				Remove(p, k);
			}
		}
		else {
			if (p->ptr[0] != NULL && p->ptr[0]->keynum != 0)
			{
				ps->ptr[0] = p->ptr[0];
				p->ptr[0]->parent = ps;
			}
			else
			{
				ps->ptr[0] = p->ptr[1];
				if (p->ptr[1] != NULL)
					p->ptr[1]->parent = ps;
			}
			if (T == pp && p->keynum != 0 && p->ptr[1] != NULL)p->ptr[1]->parent = ps;
		}
		Remove(pp, j + 1);
		pp->ptr[0] = ps;
		if (pp->keynum < (m / 2))
		{
			//combine(T, pp);
			if (pp->parent != NULL)
				Restore(T, pp, j + 1);//
			else {
				ps->parent = NULL;
				T = ps;
			}
		}
	}

}
/**
* Description:����B��
* @param T Ҫ���е�����B��
* @param &p Ҫɾ���Ľ��p
* @param i Ҫɾ���Ĺؼ��ֵ�λ��
* @return:void
*/
void Restore(BTree &T, BTree &p, int i)
{
	//�ҵ��ý��������ֵ�
	BTree pp = p->parent;
	//if (pp == NULL) { T = p; return; }
	int j;
	for (j = 0; j <= pp->keynum; j++)
	{
		if (pp->ptr[j] == p)break;
	}
	//����������ֵܽ���С����ࡱ�Ĺؼ���
	if (j > 0 && pp->ptr[j - 1]->keynum > (m / 2))//��
	{
		//�ƶ����ֵܵ����ؼ��ַ���˫�׽��
		p->ptr[1] = p->ptr[0];
		p->ptr[0] = pp->ptr[j - 1]->ptr[pp->ptr[j - 1]->keynum];
		if (p->ptr[0] != NULL)p->ptr[0]->parent = p;
		insert(pp, j, pp->ptr[j - 1]->key[pp->ptr[j - 1]->keynum], pp->ptr[j]);
		Remove(pp->ptr[j - 1], pp->ptr[j - 1]->keynum);
		//��˫�׽���д��ڸ����ƹؼ��ֵĹؼ������Ƶ���ɾ�ؼ������ڵĽ����
		insert(p, i, pp->key[j + 1], p->ptr[i]);
		Remove(pp, j + 1);
		//if (p->ptr[0] != NULL)Restore(T, p->ptr[i], 1);
		//pp->ptr[j + 1] = pp->ptr[j + 2];
	}
	else if (j<pp->keynum && pp->ptr[j + 1]->keynum >(m / 2))//��
	{
		//�ƶ����ֵܵ���С�ؼ��ַ���˫�׽��
		p->ptr[1] = pp->ptr[j + 1]->ptr[0];
		if (p->ptr[1] != NULL)p->ptr[1]->parent = p;
		insert(pp, j + 2, pp->ptr[j + 1]->key[1], pp->ptr[j + 1]);
		Remove(pp->ptr[j + 1], 1);
		//��˫�׽����С�ڸ����ƹؼ��ֵĹؼ������Ƶ���ɾ�ؼ������ڵĽ����
		insert(p, i, pp->key[j + 1], p->ptr[i]);
		Remove(pp, j + 1);
		pp->ptr[j] = p;
		/*if (p->ptr[0] != NULL) {
		p->ptr[i]->keynum = 0;
		Restore(T, p->ptr[i], 1);
		}*/
		//pp->ptr[j ] = pp->ptr[j + 1];
	}
	else {//�ֵ�û�и���Ĺؼ���
		combine(T, p);
	}
}
/**
* Description:ɾ��B����p���ĵ�i���ؼ���
* @param T Ҫ����ɾ��������B��
* @param &p Ҫɾ���ؼ����ϵĽ��
* @param i Ҫɾ���Ĺؼ��ֵ�λ��
* @return:void
*/
void deleteBTree(BTree &T, BTree &p, int i)
{
	if (p->ptr[i] != NULL) {//���������²���ն˽��
		Successor(p, i);  //��Ai�������ҳ����²��ն˽�����С�ؼ������Ki
		deleteBTree(T, p, 1);//ת��Ϊɾ�����²���ն˽���е���С�ؼ���
	}
	else {//�������²���ն˽��
		Remove(p, i);//�ӽ��p��ɾ��key[i]
		if (p == T &&T->keynum == 0) { T = NULL; return; }
		if (p->keynum < m / 2)//ɾ����ؼ��ָ���С�ڣ�m-1��/2
			Restore(T, p, i);        //����B��
	}
}

/**
* Description:ɾ��B��T�ϵĹؼ���e
* @param T Ҫ����ɾ��������B��
* @param key Ҫɾ���Ĺؼ���
* @return:Status ɾ���ɹ�����SUCCESS,ʧ�ܷ���ERROR
*/
Status deleteKey(BTree &T, KeyType e)
{
	//���ҹؼ���e
	Result r;
	if (T == NULL)return ERROR;
	searchBTree(T, e, r);
	if (r.tag == 0)return ERROR;    //�����ڣ��޷�ɾ��
	else
	{                            //���ڣ�����ɾ������
		int i = r.i;
		BTree p = r.pt;
		deleteBTree(T, p, i);
		return SUCCESS;
	}
}
/**********************************ɾ������  end***************************************/
/**********************************�������start***************************************/
/**
* Description:����ʽ�������(������1-keynum)
* @param key  Ҫ����Ĺؼ�������
* @param keynum ����ĳ���
* @return:void
*/
void printArray1(KeyType key[], int keynum)
{
	int i;
	for (i = 1; i <= keynum; i++)
	{
		if (i == keynum)
			printf("%d", key[i].num);
		else printf("%d,", key[i].num);
	}
	printf("\n");
}
/**
* Description:����ʽ(���)���B��
* @param T      Ҫ�����B��
* int dep      ��ǰ�����
* @return:void
*/
void printBTNode(BTree p, int dep)
{
	if (p == NULL)return;
	int i;
	if (dep > 1)
	{
		for (i = 1; i<dep; i++)
		{
			printf("   ");
		}
	}
	printArray1(p->key, p->keynum);
	for (i = 0; i <= p->keynum; i++)
	{
		printBTNode(p->ptr[i], dep + 1);
	}
}
/**
* Description:����ʽ���B��
* @param T      Ҫ�����B��
* @return:void
*/
void printBTree1(BTree T)
{
	if (NULL == T)
	{
		printf("��B��Ϊ����\n");
		return;
	}
	BTree p = T;
	int dep = 1;
	printBTNode(p, dep);
}

/**********************************�������end***************************************/
/**
* Description:����B��
* @param T Ҫ��ʼ����B��
* @return:void
*/
void destroyBTree(BTree &T)
{
	int i;
	BTree node = T;
	if (node) {
		for (i = 0; i <= node->keynum; i++) {
			destroyBTree(node->ptr[i]);
		}
		free(node);
	}
	T = NULL;
}