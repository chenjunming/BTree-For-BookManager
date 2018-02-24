#include "bookManager.h"
extern Status InitQueue_Sq(SqQueue &Q, int size);
extern Status InitList(LinkList &L);
/**
* Description:比较关键字
* @param k1 关键字1
* @param k2 关键字2
* @return:int 返回-1表示k1<k2,0表示k1==k2,1表示k1>k2
*/
int compareTo(KeyType k1, KeyType k2)
{
	if (k1.num == k2.num)return 0;
	if (k1.num < k2.num)return -1;
	if (k1.num > k2.num)return 1;
}

/**
* Description:初始化空树
* @param T 要初始化的B树
* @return:Status 初始化成功返回SUCCESS
*/
Status initBTree(BTree &T)
{
	T = NULL;
	return SUCCESS;
}
/**********************************查找操作start*****************************************/
/**
* Description:在p->key[1...p->keynum]找k，在SearchBTree函数内部使用
* @param p 正在查找的结点
* @param k 正在要查找的关键字
* @return:int 返回查找的位置
*/
int search(BTree p, KeyType k)
{
	int i = 1;                                //关键字数组，key[0]未用
	while (i <= p->keynum && compareTo(k, p->key[i]) > 0)i++;  //索引要小于结点当前关键字的个数，且关键字要小于关键字数组的当前元素
	return i;                                //返回的索引所在的元素要么等于关键字，要么大于关键字
}
/**
* Description:在m阶B树T上查找关键字k，用r返回一个result
* @param T 要查找的B树
* @param k 要查找的关键字
* @param &r 返回查找到的结果
* @return:void
*/
void searchBTree(BTree T, KeyType k, Result &r)
{
	if (NULL == T)return;
	int i, found = 0;                                  //found为0时表示未查找到，1表示成功查找
	BTree p = T, q = NULL;                                  //p表示当前检索的结点，q表示p结点的双亲结点
	while (p != NULL && found == 0) {                      //找不到:遍历完所有可能有该关键字的位置，而且found没有发生改变（即没有找到）            
		i = search(p, k);                              //使用Search函数遍历当前结点的关键字数组，返回相应位置
		if (i <= p->keynum && compareTo(k, p->key[i]) == 0)found = 1;//如果返回的索引合法（小于等于关键字实际长度），而且要查找的关键字与数组中的元素匹配，则找到
		else {                                          //否则，q记住当前位置，p指针下移
			q = p;
			p = p->ptr[i - 1];
		}
	}
	if (found == 1) {                                      //如果找到，封装结果到r
		r.pt = p; r.i = i; r.tag = 1;
	}
	else {
		r.pt = q; r.i = i; r.tag = 0;                      //如果找不到，保存插入位置到r
	}
}
/**********************************查找操作end*****************************************/

/**********************************插入操作start*****************************************/
/**
* Description:创建一个结点
* @param &T 返回创建的结点，创建失败返回NULL
* @param firstchild 该结点的第一个孩子
* @param key         该结点的关键字数组域的第一个关键字
* @param secondchild该结点的第二个孩子
* @return:void
*/
void makeNode(BTree &T, BTree firstchild, KeyType key, BTree secondchild)
{
	T = (BTree)malloc(sizeof(BTNode));                //分配结点的内存
	if (NULL == T)return;
	//封装结点的数据
	InitList(key.reader);//初始化借阅者链表
	InitList(key.preBooker);//初始化预约者队列
	T->keynum = 1;    T->key[1] = key;    T->parent = NULL;    T->ptr[0] = firstchild;    T->ptr[1] = secondchild;
	if (firstchild != NULL)firstchild->parent = T;    //给两个孩子的双亲域赋值
	if (secondchild != NULL)secondchild->parent = T;
}
/**
* Description:插入一条记录到q这个节点(要插入位置的下一个指针挪)
* @param q 要插入到的结点
* @param i 要插入的位置
* @param x 要插入的关键字
* @param ap 要插入的新孩子结点
*/
void insert1(BTree &q, int i, KeyType x, BTree ap)
{
	int j, n = q->keynum;
	if (i <= n) {
		for (j = n; j >= i; j--) {                //为要插入的关键字腾出位置
			q->key[j + 1] = q->key[j];
			q->ptr[j + 1] = q->ptr[j];
		}
		q->ptr[i] = q->ptr[i - 1];
		q->key[i] = x;                    //插入关键字
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
* Description:插入一条记录到q这个节点（要插入位置的下一个指针不挪）
* @param q 要插入到的结点
* @param i 要插入的位置
* @param x 要插入的关键字
* @param ap 要插入的新孩子结点
*/
void insert(BTree &q, int i, KeyType x, BTree ap)
{
	int j, n = q->keynum;
	for (j = n; j >= i; j--) {                //为要插入的关键字腾出位置
		q->key[j + 1] = q->key[j];
		q->ptr[j + 1] = q->ptr[j];
	}
	q->key[i] = x;                    //插入关键字
	q->ptr[i] = ap;
	if (ap != NULL)ap->parent = q;
	q->keynum++;
}
/**
* Description:从结点p开始向双亲递归分裂，直到整棵树满足B树的定义
* @param &p 当前要分裂的结点
* @return:Status 分裂成功返回SUCCESS,失败返回ERROR
*/
Status split(BTree &p)
{
	while (p != NULL && p->keynum >= m) {
		BTree t;
		t = (BTree)malloc(sizeof(BTNode));//创建一新结点
		int n = (p->keynum + 1) / 2;                //n为中间位置
		int i, j;
		t->keynum = p->keynum - n;                //开始封装新结点的数据
		t->parent = p->parent;
		t->ptr[0] = p->ptr[n];

		for (i = n + 1, j = 1; i <= p->keynum; i++, j++)
		{
			t->key[j] = p->key[i];//把关键字放到新结点中
			t->ptr[j] = p->ptr[i];//把孩子结点放到新结点中
		}
		//修改新结点的子节点的parent域
		for (i = 0; i <= p->keynum - n; i++)
			if (t->ptr[i] != NULL)t->ptr[i]->parent = t;
		p->keynum = n - 1;
		//双亲结点插入p结点中间位置的关键字
		if (p->parent == NULL)
		{
			BTree np;
			makeNode(np, p, p->key[n], t);
			//printf("关键字是%d\n",p->key[n]);
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
* Description:插入一条记录到T这棵B树中
* @param T 要插入的B树
* @param key 要插入的关键字
* @return:Status 插入成功返回SUCCESS,失败返回ERROR
*/
Status insertBTree(BTree &T, KeyType key)
{
	int finished = 0;
	BTree p;
	if (NULL == T)makeNode(T, NULL, key, NULL);    //如果该树为空，新建一个结点作为根结点并返回
	else {
		Result r;
		searchBTree(T, key, r);
		if (r.tag == 1) {//查找成功,证明该记录已存在，无法插入
			return ERROR;
		}
		else {           //查找失败，可以插入
			p = r.pt;                            //记录插入点到p
			insert(r.pt, r.i, key, NULL);            //先插入
			if (r.pt->keynum < m)finished = 1;        //插入完成
			else {//要结点p分裂
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
* Description:插入数据key中所有的元素到T这棵B树中
* @param T 要插入的B树
* @param key 要插入的数组
* @return:Status 插入成功返回SUCCESS,失败返回ERROR
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
/**********************************插入操作end*****************************************/
/**********************************删除操作start***************************************/

/**
* Description:在Ai子树中找出最下层终端结点的最小关键字替代Ki
* @param p 要进行替换操作根结点的双亲结点
* @param i 要替换的关键字的所在位置
* @return:void
*/
void Successor(BTree &p, int i)
{
	BTree T = p;
	p = T->ptr[i];//获得第i棵子树的根
	while (p->ptr[0] != NULL)//所需的找到最下层终端结点
	{
		p = p->ptr[0];
	}
	//替换
	T->key[i] = p->key[1];
}
/**
* Description:从结点p中删除key[i]
* @param T 要进行删除操作的结点p
* @param i 要删除的关键字的位置
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
* Description:向上合并结点
* @param p 要删除的关键字的结点
* @param i 要删除的关键字的位置
* @return:void
*/
void combine(BTree &T, BTree &p)
{
	//找到该结点的左右兄弟
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
	}//pp->ptr[j]为p
	 //合并p，pp的第i关键字，左（右）兄弟结点到左（右）兄弟结点
	if (j > 0) {//左兄弟
				//插入pp的第j关键字到左兄弟
		ps = pp->ptr[j - 1];
		insert1(ps, ps->keynum + 1, pp->key[j], NULL);
		//Remove(pp, j);
		//插入p的剩余关键字到左兄弟
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
	else {//右兄弟
		  //插入pp的第j+1关键字到右兄弟
		ps = pp->ptr[j + 1];
		insert1(ps, 1, pp->key[j + 1], NULL);
		//Remove(pp, j);
		//插入p的剩余关键字到右兄弟
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
* Description:调整B树
* @param T 要进行调整的B树
* @param &p 要删除的结点p
* @param i 要删除的关键字的位置
* @return:void
*/
void Restore(BTree &T, BTree &p, int i)
{
	//找到该结点的左右兄弟
	BTree pp = p->parent;
	//if (pp == NULL) { T = p; return; }
	int j;
	for (j = 0; j <= pp->keynum; j++)
	{
		if (pp->ptr[j] == p)break;
	}
	//如果其左右兄弟结点有“富余”的关键字
	if (j > 0 && pp->ptr[j - 1]->keynum > (m / 2))//左
	{
		//移动左兄弟的最大关键字放在双亲结点
		p->ptr[1] = p->ptr[0];
		p->ptr[0] = pp->ptr[j - 1]->ptr[pp->ptr[j - 1]->keynum];
		if (p->ptr[0] != NULL)p->ptr[0]->parent = p;
		insert(pp, j, pp->ptr[j - 1]->key[pp->ptr[j - 1]->keynum], pp->ptr[j]);
		Remove(pp->ptr[j - 1], pp->ptr[j - 1]->keynum);
		//将双亲结点中大于该上移关键字的关键字下移到被删关键字所在的结点中
		insert(p, i, pp->key[j + 1], p->ptr[i]);
		Remove(pp, j + 1);
		//if (p->ptr[0] != NULL)Restore(T, p->ptr[i], 1);
		//pp->ptr[j + 1] = pp->ptr[j + 2];
	}
	else if (j<pp->keynum && pp->ptr[j + 1]->keynum >(m / 2))//右
	{
		//移动右兄弟的最小关键字放在双亲结点
		p->ptr[1] = pp->ptr[j + 1]->ptr[0];
		if (p->ptr[1] != NULL)p->ptr[1]->parent = p;
		insert(pp, j + 2, pp->ptr[j + 1]->key[1], pp->ptr[j + 1]);
		Remove(pp->ptr[j + 1], 1);
		//将双亲结点中小于该上移关键字的关键字下移到被删关键字所在的结点中
		insert(p, i, pp->key[j + 1], p->ptr[i]);
		Remove(pp, j + 1);
		pp->ptr[j] = p;
		/*if (p->ptr[0] != NULL) {
		p->ptr[i]->keynum = 0;
		Restore(T, p->ptr[i], 1);
		}*/
		//pp->ptr[j ] = pp->ptr[j + 1];
	}
	else {//兄弟没有富余的关键字
		combine(T, p);
	}
}
/**
* Description:删除B树上p结点的第i个关键字
* @param T 要进行删除操作的B树
* @param &p 要删除关键字上的结点
* @param i 要删除的关键字的位置
* @return:void
*/
void deleteBTree(BTree &T, BTree &p, int i)
{
	if (p->ptr[i] != NULL) {//若不是最下层非终端结点
		Successor(p, i);  //在Ai子树中找出最下层终端结点的最小关键字替代Ki
		deleteBTree(T, p, 1);//转换为删除最下层非终端结点中的最小关键字
	}
	else {//若是最下层非终端结点
		Remove(p, i);//从结点p中删除key[i]
		if (p == T &&T->keynum == 0) { T = NULL; return; }
		if (p->keynum < m / 2)//删除后关键字个数小于（m-1）/2
			Restore(T, p, i);        //调整B树
	}
}

/**
* Description:删除B树T上的关键字e
* @param T 要进行删除操作的B树
* @param key 要删除的关键字
* @return:Status 删除成功返回SUCCESS,失败返回ERROR
*/
Status deleteKey(BTree &T, KeyType e)
{
	//查找关键字e
	Result r;
	if (T == NULL)return ERROR;
	searchBTree(T, e, r);
	if (r.tag == 0)return ERROR;    //不存在，无法删除
	else
	{                            //存在，进行删除操作
		int i = r.i;
		BTree p = r.pt;
		deleteBTree(T, p, i);
		return SUCCESS;
	}
}
/**********************************删除操作  end***************************************/
/**********************************输出操作start***************************************/
/**
* Description:按格式输出数组(索引从1-keynum)
* @param key  要输出的关键字数组
* @param keynum 数组的长度
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
* Description:按格式(深度)输出B树
* @param T      要输出的B树
* int dep      当前的深度
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
* Description:按格式输出B树
* @param T      要输出的B树
* @return:void
*/
void printBTree1(BTree T)
{
	if (NULL == T)
	{
		printf("该B树为空树\n");
		return;
	}
	BTree p = T;
	int dep = 1;
	printBTNode(p, dep);
}

/**********************************输出操作end***************************************/
/**
* Description:销毁B树
* @param T 要初始化的B树
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