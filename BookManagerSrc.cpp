#include "bookManager.h"
#define BACKTIME 60 //归还日期
extern Status deleteKey(BTree &T, KeyType e);
extern void destroyBTree(BTree &T);
extern Status initBTree(BTree &T);
extern Status insertBTree(BTree &T, KeyType key);
extern void printBTree1(BTree T);
extern void searchBTree(BTree T, KeyType i, Result &r);
extern Status InitList(LinkList &L);
extern Status EnQueue(LinkList &L, ElemType e);
extern Status DeQueue(LinkList &L, ElemType &e);
extern LinkList NextElem_L(LinkList p);
extern int ListLength_L(LinkList L);
extern Status ListEmpty_L(LinkList L);
extern LNode* Search_L(LinkList L, ElemType e);
extern Status InitTree(CSTree &T);
extern CSTree MakeTree(TElemType e, int n, ...);
extern CSTree Search(CSTree T, TElemType e);
extern Status InsertChild(CSTree &T, int i, CSTree c);
extern Status DeleteChild(CSTree &T, int i);
extern Status insertCSTree(CSTree &T, TElemType e);
extern Status findWriter(CSTree T, char *writer);
extern Status deleteCSTree(CSTree p, CSTree &T, TElemType e);
int x0 = 10, y0 = 8;				//设置页面初始位置
/*
*  Description:定位到第y行的第x列(因为vs不能使用gotoxy函数，所以在这里手动实现了)
*/
void gotoxy(int x, int y)
{
	int xx = 0x0b;
	HANDLE hOutput;
	COORD loc;
	loc.X = x;
	loc.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, loc);
	return;
}
/**
* Description:欢迎界面
*/
void welcome()
{
	system("cls");
	x0 = X0; y0 = Y0;
	gotoxy(x0, y0++); printf("+-----------------------------------------------------+");
	gotoxy(x0, y0++); printf("|                   图书信息管理系统                  |");
	gotoxy(x0, y0++); printf("+-----------------------------------------------------+");
	gotoxy(x0, y0++); printf("|               15届软件工程卓越工程师班              |");
	gotoxy(x0, y0++); printf("|                       陈俊铭                        |");
	gotoxy(x0, y0++); printf("|                   学号: 3115005567                  |");
	gotoxy(x0, y0++); printf("+-----------------------------------------------------+");
	gotoxy(x0, y0++); printf("|                   请按任意键继续                    |");
	gotoxy(x0, y0++); printf("+-----------------------------------------------------+");
	getch();
}
/*
* Description:主菜单页面
*/
void mainMenu()
{
	system("cls");
	x0 = X0; y0 = Y0;
	gotoxy(x0, y0++); printf("+-----------------------------------------------------+");
	gotoxy(x0, y0++); printf("|                     主菜单                          |");
	gotoxy(x0, y0++); printf("+-----------------------------------------------------+");
	gotoxy(x0, y0++); printf("|1.入库图书             |2. 删除图书                  |");
	gotoxy(x0, y0++); printf("|3.借阅图书             |4. 归还图书                  |");
	gotoxy(x0, y0++); printf("|5.查看著者著作         |6. 查看图书状态              |");
	gotoxy(x0, y0++); printf("|7.查看书库情况         |0. 退出系统                  |");
	gotoxy(x0, y0++); printf("+-----------------------------------------------------+");

}
/**
* Description:按书库格式(深度)输出结点上的图书
* @param p     要输出的书库结点
* int dep      当前的深度
* @return:void
*/
void printArray(KeyType key[], int keynum)
{
	int i;
	for (i = 1; i <= keynum; i++)
	{
		//输出单本图书
		printf(FORMAT, key[i].num, key[i].name, key[i].writer, key[i].current, key[i].total);
		printf(END);
	}
}
/**
* Description:按书库格式(深度)输出图书
* @param p     要输出的书库结点
* int dep      当前的深度
* @return:void
*/
void printBTNode1(BTree p)
{
	if (p == NULL)return;
	int i;
	printArray(p->key, p->keynum);
	for (i = 0; i <= p->keynum; i++)
	{
		printBTNode1(p->ptr[i]);
	}
}
/**
* Description:输出书库中的书
* @param store 书库
* @return:void
*/
void printStore(BTree store)
{
	if (NULL == store) {
		printf("该书库中无图书\n");
		return;
	}
	printf(HEARDER1);
	printf(HEARDER2);
	printf(HEARDER3);
	BTree p = store;
	int dep = 1;
	printBTNode1(p);
	getch();
}
/**
* Description:增加该树的库存量
* @param store 书库
* @param r 查找后获得的结果
* @return:返回增加库存量
*/
int AddNum(BTree &store, Result r)
{
	printf("该书已存在，请输入要增加的库存量:");
	int i;
	while (1)
	{
		scanf("%d", &i);
		if (i > 0)break;
		else {
			printf("增加的库存量必须为正整数！请重新输入！");
		}
	}
	r.pt->key[r.i].total += i;
	r.pt->key[r.i].current += i;
	return i;
}

/**
* Description:采编入库：新购入一种书，经分类和确定书号之后登记到图书账目中去。
*             如果这种书在帐中已有，则只将总库存量增加。
* @param &store 书库
* @param &T 著者树
* @return:void
*/
void insertBook(BTree &store,FILE* &fp,CSTree &T)
{
	unsigned long int i;
	system("cls");
	while (1)
	{
		printf("请输入要入库书籍的书号(长度不能超过9位):");
		scanf("%lu", &i);
		BookNode e;
		Result r;
		e.num = i;
		fflush(stdin);
		searchBTree(store, e, r);
		if (r.tag == 1)//该书已存在
		{
			int num = AddNum(store, r);
			printf("增加库存成功！");
			fprintf(fp, "增加书号为%lu的书籍%d本\n",i,num);
		}
		else {
			printf("请输入书名（不能超过20个非空字符）:");
			scanf("%s", e.name);
			fflush(stdin);
			printf("请输入著者（不能超过20个非空字符）:");
			scanf("%s", e.writer);
			fflush(stdin);
			while (1) {
				printf("请输入库存量");
				scanf("%d", &e.total);
				if (e.total > 0)break;
				else { 
					printf("库存量不能不大于0");
				}
				fflush(stdin);
			}
			e.current = e.total;
			InitList(e.reader);
			InitList(e.preBooker);
			fflush(stdin);
			insertBTree(store, e);
			insertCSTree(T, e);
			printf("入库成功!");
			fprintf(fp, "入库%s%d本\n", e.name, e.total);
		}
		//printf("B树展示如下:\n");
		//printBTree1(store);
		printStore(store);
		printf("\n是否继续输入？(Y/N)\n");
		char c;
		c = getch();
		fflush(stdin);
		if (c != 'Y'&&c != 'y')
			break;
		else
			system("cls");
	}

}
/**
* Description:删除书籍
* @param store 书库
* @return:void
*/
void deleteBook(BTree &store,FILE* &fp,CSTree &T)//输入删除相关数据并回显结果
{
	char k;
	unsigned long int i;
	while (1)
	{
		printf("\n请输入要删除书籍的书号:");
		scanf("%lu", &i);
		BookNode e;
		Result r;
		e.num = i;
		fflush(stdin);
		searchBTree(store, e, r);
		if (r.tag == 0)
		{
			printf("查无此书");
		}
		else {
			printf(HEARDER1);
			printf(HEARDER2);
			printf(HEARDER3);
			printf(FORMAT, r.pt->key[r.i].num, r.pt->key[r.i].name, r.pt->key[r.i].writer, r.pt->key[r.i].current, r.pt->key[r.i].total);
			printf(END);
			printf("是否确定删除该书本?(Y/N)(该操作不可逆)\n");
			k = getch();
			if (k == 'Y' || k == 'y') {
				fprintf(fp, "删除书籍%s\n", r.pt->key[r.i].name);
				deleteCSTree(NULL, T, r.pt->key[r.i]);
				deleteKey(store, e);
				printf("删除成功！\n");
				//printf("\nB树如下所示:\n");
				//printBTree1(store);
				printStore(store);
			}
			fflush(stdin);
		}
		printf("\n是否继续删除？(Y/N)");
		k = getch();
		if (k != 'Y'&&k != 'y')
			break;
		else
			system("cls");
	}
}
/**
* Description:借阅图书
* @param store 书库
* @return:void
*/
void lendBook(BTree &store,FILE* &fp)
{
	printf("请输入您要借阅的书籍的书号:\n");
	int num;
	BookNode book;
	Result r;
	scanf("%d", &num);
	book.num = num;
	searchBTree(store, book, r);
	if (r.tag == 0) {//找不到该书
		printf("找不到此书，请检验书号!");
		getch();
	}
	else {//找到该书且库存足
		if (r.pt->key[r.i].current >0) {
			ReaderNode reader;
			fflush(stdin);
			printf("请输入您的图书证号:");
			scanf("%d", &reader.cardNum);
			printf("\n");
			fflush(stdin);
			printf("请输入您的姓名:");
			scanf("%s", reader.name);
			printf("\n");
			fflush(stdin);
			reader.time = 30;
			EnQueue(r.pt->key[r.i].reader, reader);//加入到借阅者链表中
			r.pt->key[r.i].current--;
			printf("借阅成功,按任意键返回主菜单！\n");
			fprintf(fp, "%s借阅书籍%s\n", reader.name, r.pt->key[r.i].name);
			getch();
		}
		else {//库存不足
			printf("库存不足，是否进行预约借书？(Y/N)\n");
			char a;
			a = getch();
			if (a == 'Y' || a == 'y')
			{
				ReaderNode reader;
				fflush(stdin);
				printf("请输入您的图书证号:");
				scanf("%d", &reader.cardNum);
				printf("\n");
				fflush(stdin);
				printf("请输入您的姓名:");
				scanf("%s", reader.name);
				fflush(stdin);
				printf("\n");
				if (SUCCESS == EnQueue(r.pt->key[r.i].preBooker, reader))
				{
					printf("预约成功!");
					fprintf(fp, "%s成功预约书籍%s\n", reader.name, r.pt->key[r.i].name);
				}
				else printf("不好意思，预约失败!");
				getch();
			}
			else {

			}
		}
	}
}
/**
* Description:归还书本
* @param store 书库
* @return:void
*/
void backBook(BTree &store,FILE* &fp)
{
	BookNode book;
	Result r;
	printf("请输入要归还书本的编号：");
	scanf("%d", &book.num);
	//查找该书
	searchBTree(store, book, r);
	if (r.tag == 1)
	{//查找成功，归还
		printf("请输入你的图书证号:");
		ReaderNode reader;
		scanf("%d", &reader.cardNum);
		fflush(stdin);
		if (Search_L(r.pt->key[r.i].reader, reader) == NULL)
		{
			printf("无此借阅者，请检查借阅者的图书证号!\n");
			getch();
		}
		else {
			DeQueue(r.pt->key[r.i].reader, reader);
			r.pt->key[r.i].current++;
			printf("还书成功！");
			fprintf(fp, "%s还书%s成功\n", reader.name, r.pt->key[r.i].name);
			getch();
		}
	}
	else {
		printf("查无此书!请检查图书号！\n");
		fflush(stdin);
	}
}
/**
* Description:查看图书状态
* @param store 书库
* @return:void
*/
void bookStatus(BTree store)
{
	printf("请输入图书编号：");
	BookNode book;
	scanf("%d", &book.num);
	fflush(stdin);
	Result r;
	searchBTree(store, book, r);
	if (r.tag == 1)
	{//查找成功
		printf(HEARDER1);
		printf(HEARDER2);
		printf(HEARDER3);
		printf(FORMAT, r.pt->key[r.i].num, r.pt->key[r.i].name, r.pt->key[r.i].writer, r.pt->key[r.i].current, r.pt->key[r.i].total);
		printf(END);
		printf("\n");
		printf("+----------------|--------------------|---------+\n");
		printf("|      借阅者姓名|      借阅者图书证号|归还日期 |\n");
		printf("|----------------|--------------------|---------|\n");
		LinkList L = r.pt->key[r.i].reader;
		LinkList p = L;
		int i;
		for (i = 1; i <= ListLength_L(L); i++)
		{
			printf("|%16s|%20lu|%7d天|\n",p->data.name,p->data.cardNum,p->data.time );
			printf("|----------------|--------------------|---------|\n");
			p = p->next;
		}
		printf("+-----------------------------------------------+\n");
		printf("\n");
		printf("+----------------|--------------------+\n");
		printf("|      预约者姓名|      预约者图书证号|\n");
		printf("|----------------|--------------------|\n");
		LinkList p1 = r.pt->key[r.i].preBooker;
		for (i = 1; i <= ListLength_L(p1); i++)
		{
			printf("|%16s|%20lu|\n",p1->data.name,p1->data.cardNum);
			p1 = p1->next;
			printf("|----------------|--------------------|\n");
		}
		printf("+-------------------------------------+\n");
		getch();
	}
	else {
		printf("查无此书，请检查图书编号！\n");
		getch();
	}
}
/**
* Description:测试代码
* @param store 书库
* @return:void
*/
void test(BTree &store,CSTree &T)
{
	FILE *fp;
	int count = 0;
	BookNode book;
	if ((fp = fopen("book.txt", "r")) == NULL)
	{
		system("cls");
		printf("open book.txt error");
		fflush(stdin);
		getchar();
		exit(0);
	}
	while (!feof(fp))
	{
		count++;
		fscanf(fp, "%d%s%s", &book.num, &book.name, &book.writer);
		book.current = book.total = 2;
		InitList(book.reader);//初始化借阅者链表
		InitList(book.preBooker);//初始化预约者队列
		insertBTree(store, book);
		insertCSTree(T, book);
	}
	fclose(fp);
}
/**
* Description:开始记录操作
* @return:返回当前移动的文件指针
*/
FILE* logStart()
{
	FILE *fp;
	if ((fp = fopen("log.txt","a")) == NULL)
	{
		system("cls");
		printf("open log.txt error");
		fflush(stdin);
		getchar();
		exit(0);
	}
	fprintf(fp, "------------------start-----------------\n");
	return fp;
}
/**
* Description:结束记录操作
* @param fp		当前的文件指针
* @return:void
*/
void logEnd(FILE *fp)
{
	fprintf(fp, "------------------end-------------------\n");
	fclose(fp);
}
/**
* Description:输出该著者的书
* @param store 书库
* @param T	孩子兄弟森林指针
* @return:void
*/
void Writer(BTree store, CSTree T)
{
	printf("请输入著者:");
	char a[NAME];
	scanf("%s", a);
	if (ERROR == findWriter(T, a)) {
		printf("找不到该著者");
	}
	getch();
}
void main()
{
	BTree store;
	CSTree T;//著者树
	initBTree(store);
	InitTree(T);
	welcome();
	test(store,T);
	FILE* fp=logStart();
	while (1)
	{
		system("cls");
		mainMenu();
		gotoxy(x0, y0++); printf("请选择功能:");
		x0 = X0, y0 = Y0;
		switch (getch())
		{
		case '1': {gotoxy(x0, y0 += 2); system("cls"); fflush(stdin); insertBook(store,fp,T); break; }
		case '2': {gotoxy(x0, y0 += 2); system("cls"); fflush(stdin); deleteBook(store,fp,T); break; }
		case '3': {gotoxy(x0, y0 += 2); system("cls"); fflush(stdin); lendBook(store,fp);   break; }
		case '4': {gotoxy(x0, y0 += 2); system("cls"); fflush(stdin); backBook(store,fp); break; }
		case '5': {gotoxy(x0, y0 += 2); system("cls"); fflush(stdin); Writer(store,T); break; }
		case '6': {gotoxy(x0, y0 += 2); system("cls"); fflush(stdin); bookStatus(store); break; }
		case '7': {gotoxy(x0, y0 += 2); system("cls"); fflush(stdin); printStore(store); break; }
		case '0': {gotoxy(x0, y0 += 2); system("cls");  logEnd(fp); exit(0); }
		default:;
		}
	}

}