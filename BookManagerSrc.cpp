#include "bookManager.h"
#define BACKTIME 60 //�黹����
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
int x0 = 10, y0 = 8;				//����ҳ���ʼλ��
/*
*  Description:��λ����y�еĵ�x��(��Ϊvs����ʹ��gotoxy�����������������ֶ�ʵ����)
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
* Description:��ӭ����
*/
void welcome()
{
	system("cls");
	x0 = X0; y0 = Y0;
	gotoxy(x0, y0++); printf("+-----------------------------------------------------+");
	gotoxy(x0, y0++); printf("|                   ͼ����Ϣ����ϵͳ                  |");
	gotoxy(x0, y0++); printf("+-----------------------------------------------------+");
	gotoxy(x0, y0++); printf("|               15���������׿Խ����ʦ��              |");
	gotoxy(x0, y0++); printf("|                       �¿���                        |");
	gotoxy(x0, y0++); printf("|                   ѧ��: 3115005567                  |");
	gotoxy(x0, y0++); printf("+-----------------------------------------------------+");
	gotoxy(x0, y0++); printf("|                   �밴���������                    |");
	gotoxy(x0, y0++); printf("+-----------------------------------------------------+");
	getch();
}
/*
* Description:���˵�ҳ��
*/
void mainMenu()
{
	system("cls");
	x0 = X0; y0 = Y0;
	gotoxy(x0, y0++); printf("+-----------------------------------------------------+");
	gotoxy(x0, y0++); printf("|                     ���˵�                          |");
	gotoxy(x0, y0++); printf("+-----------------------------------------------------+");
	gotoxy(x0, y0++); printf("|1.���ͼ��             |2. ɾ��ͼ��                  |");
	gotoxy(x0, y0++); printf("|3.����ͼ��             |4. �黹ͼ��                  |");
	gotoxy(x0, y0++); printf("|5.�鿴��������         |6. �鿴ͼ��״̬              |");
	gotoxy(x0, y0++); printf("|7.�鿴������         |0. �˳�ϵͳ                  |");
	gotoxy(x0, y0++); printf("+-----------------------------------------------------+");

}
/**
* Description:������ʽ(���)�������ϵ�ͼ��
* @param p     Ҫ����������
* int dep      ��ǰ�����
* @return:void
*/
void printArray(KeyType key[], int keynum)
{
	int i;
	for (i = 1; i <= keynum; i++)
	{
		//�������ͼ��
		printf(FORMAT, key[i].num, key[i].name, key[i].writer, key[i].current, key[i].total);
		printf(END);
	}
}
/**
* Description:������ʽ(���)���ͼ��
* @param p     Ҫ����������
* int dep      ��ǰ�����
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
* Description:�������е���
* @param store ���
* @return:void
*/
void printStore(BTree store)
{
	if (NULL == store) {
		printf("���������ͼ��\n");
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
* Description:���Ӹ����Ŀ����
* @param store ���
* @param r ���Һ��õĽ��
* @return:�������ӿ����
*/
int AddNum(BTree &store, Result r)
{
	printf("�����Ѵ��ڣ�������Ҫ���ӵĿ����:");
	int i;
	while (1)
	{
		scanf("%d", &i);
		if (i > 0)break;
		else {
			printf("���ӵĿ��������Ϊ�����������������룡");
		}
	}
	r.pt->key[r.i].total += i;
	r.pt->key[r.i].current += i;
	return i;
}

/**
* Description:�ɱ���⣺�¹���һ���飬�������ȷ�����֮��Ǽǵ�ͼ����Ŀ��ȥ��
*             ������������������У���ֻ���ܿ�������ӡ�
* @param &store ���
* @param &T ������
* @return:void
*/
void insertBook(BTree &store,FILE* &fp,CSTree &T)
{
	unsigned long int i;
	system("cls");
	while (1)
	{
		printf("������Ҫ����鼮�����(���Ȳ��ܳ���9λ):");
		scanf("%lu", &i);
		BookNode e;
		Result r;
		e.num = i;
		fflush(stdin);
		searchBTree(store, e, r);
		if (r.tag == 1)//�����Ѵ���
		{
			int num = AddNum(store, r);
			printf("���ӿ��ɹ���");
			fprintf(fp, "�������Ϊ%lu���鼮%d��\n",i,num);
		}
		else {
			printf("���������������ܳ���20���ǿ��ַ���:");
			scanf("%s", e.name);
			fflush(stdin);
			printf("���������ߣ����ܳ���20���ǿ��ַ���:");
			scanf("%s", e.writer);
			fflush(stdin);
			while (1) {
				printf("����������");
				scanf("%d", &e.total);
				if (e.total > 0)break;
				else { 
					printf("��������ܲ�����0");
				}
				fflush(stdin);
			}
			e.current = e.total;
			InitList(e.reader);
			InitList(e.preBooker);
			fflush(stdin);
			insertBTree(store, e);
			insertCSTree(T, e);
			printf("���ɹ�!");
			fprintf(fp, "���%s%d��\n", e.name, e.total);
		}
		//printf("B��չʾ����:\n");
		//printBTree1(store);
		printStore(store);
		printf("\n�Ƿ�������룿(Y/N)\n");
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
* Description:ɾ���鼮
* @param store ���
* @return:void
*/
void deleteBook(BTree &store,FILE* &fp,CSTree &T)//����ɾ��������ݲ����Խ��
{
	char k;
	unsigned long int i;
	while (1)
	{
		printf("\n������Ҫɾ���鼮�����:");
		scanf("%lu", &i);
		BookNode e;
		Result r;
		e.num = i;
		fflush(stdin);
		searchBTree(store, e, r);
		if (r.tag == 0)
		{
			printf("���޴���");
		}
		else {
			printf(HEARDER1);
			printf(HEARDER2);
			printf(HEARDER3);
			printf(FORMAT, r.pt->key[r.i].num, r.pt->key[r.i].name, r.pt->key[r.i].writer, r.pt->key[r.i].current, r.pt->key[r.i].total);
			printf(END);
			printf("�Ƿ�ȷ��ɾ�����鱾?(Y/N)(�ò���������)\n");
			k = getch();
			if (k == 'Y' || k == 'y') {
				fprintf(fp, "ɾ���鼮%s\n", r.pt->key[r.i].name);
				deleteCSTree(NULL, T, r.pt->key[r.i]);
				deleteKey(store, e);
				printf("ɾ���ɹ���\n");
				//printf("\nB��������ʾ:\n");
				//printBTree1(store);
				printStore(store);
			}
			fflush(stdin);
		}
		printf("\n�Ƿ����ɾ����(Y/N)");
		k = getch();
		if (k != 'Y'&&k != 'y')
			break;
		else
			system("cls");
	}
}
/**
* Description:����ͼ��
* @param store ���
* @return:void
*/
void lendBook(BTree &store,FILE* &fp)
{
	printf("��������Ҫ���ĵ��鼮�����:\n");
	int num;
	BookNode book;
	Result r;
	scanf("%d", &num);
	book.num = num;
	searchBTree(store, book, r);
	if (r.tag == 0) {//�Ҳ�������
		printf("�Ҳ������飬��������!");
		getch();
	}
	else {//�ҵ������ҿ����
		if (r.pt->key[r.i].current >0) {
			ReaderNode reader;
			fflush(stdin);
			printf("����������ͼ��֤��:");
			scanf("%d", &reader.cardNum);
			printf("\n");
			fflush(stdin);
			printf("��������������:");
			scanf("%s", reader.name);
			printf("\n");
			fflush(stdin);
			reader.time = 30;
			EnQueue(r.pt->key[r.i].reader, reader);//���뵽������������
			r.pt->key[r.i].current--;
			printf("���ĳɹ�,��������������˵���\n");
			fprintf(fp, "%s�����鼮%s\n", reader.name, r.pt->key[r.i].name);
			getch();
		}
		else {//��治��
			printf("��治�㣬�Ƿ����ԤԼ���飿(Y/N)\n");
			char a;
			a = getch();
			if (a == 'Y' || a == 'y')
			{
				ReaderNode reader;
				fflush(stdin);
				printf("����������ͼ��֤��:");
				scanf("%d", &reader.cardNum);
				printf("\n");
				fflush(stdin);
				printf("��������������:");
				scanf("%s", reader.name);
				fflush(stdin);
				printf("\n");
				if (SUCCESS == EnQueue(r.pt->key[r.i].preBooker, reader))
				{
					printf("ԤԼ�ɹ�!");
					fprintf(fp, "%s�ɹ�ԤԼ�鼮%s\n", reader.name, r.pt->key[r.i].name);
				}
				else printf("������˼��ԤԼʧ��!");
				getch();
			}
			else {

			}
		}
	}
}
/**
* Description:�黹�鱾
* @param store ���
* @return:void
*/
void backBook(BTree &store,FILE* &fp)
{
	BookNode book;
	Result r;
	printf("������Ҫ�黹�鱾�ı�ţ�");
	scanf("%d", &book.num);
	//���Ҹ���
	searchBTree(store, book, r);
	if (r.tag == 1)
	{//���ҳɹ����黹
		printf("���������ͼ��֤��:");
		ReaderNode reader;
		scanf("%d", &reader.cardNum);
		fflush(stdin);
		if (Search_L(r.pt->key[r.i].reader, reader) == NULL)
		{
			printf("�޴˽����ߣ���������ߵ�ͼ��֤��!\n");
			getch();
		}
		else {
			DeQueue(r.pt->key[r.i].reader, reader);
			r.pt->key[r.i].current++;
			printf("����ɹ���");
			fprintf(fp, "%s����%s�ɹ�\n", reader.name, r.pt->key[r.i].name);
			getch();
		}
	}
	else {
		printf("���޴���!����ͼ��ţ�\n");
		fflush(stdin);
	}
}
/**
* Description:�鿴ͼ��״̬
* @param store ���
* @return:void
*/
void bookStatus(BTree store)
{
	printf("������ͼ���ţ�");
	BookNode book;
	scanf("%d", &book.num);
	fflush(stdin);
	Result r;
	searchBTree(store, book, r);
	if (r.tag == 1)
	{//���ҳɹ�
		printf(HEARDER1);
		printf(HEARDER2);
		printf(HEARDER3);
		printf(FORMAT, r.pt->key[r.i].num, r.pt->key[r.i].name, r.pt->key[r.i].writer, r.pt->key[r.i].current, r.pt->key[r.i].total);
		printf(END);
		printf("\n");
		printf("+----------------|--------------------|---------+\n");
		printf("|      ����������|      ������ͼ��֤��|�黹���� |\n");
		printf("|----------------|--------------------|---------|\n");
		LinkList L = r.pt->key[r.i].reader;
		LinkList p = L;
		int i;
		for (i = 1; i <= ListLength_L(L); i++)
		{
			printf("|%16s|%20lu|%7d��|\n",p->data.name,p->data.cardNum,p->data.time );
			printf("|----------------|--------------------|---------|\n");
			p = p->next;
		}
		printf("+-----------------------------------------------+\n");
		printf("\n");
		printf("+----------------|--------------------+\n");
		printf("|      ԤԼ������|      ԤԼ��ͼ��֤��|\n");
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
		printf("���޴��飬����ͼ���ţ�\n");
		getch();
	}
}
/**
* Description:���Դ���
* @param store ���
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
		InitList(book.reader);//��ʼ������������
		InitList(book.preBooker);//��ʼ��ԤԼ�߶���
		insertBTree(store, book);
		insertCSTree(T, book);
	}
	fclose(fp);
}
/**
* Description:��ʼ��¼����
* @return:���ص�ǰ�ƶ����ļ�ָ��
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
* Description:������¼����
* @param fp		��ǰ���ļ�ָ��
* @return:void
*/
void logEnd(FILE *fp)
{
	fprintf(fp, "------------------end-------------------\n");
	fclose(fp);
}
/**
* Description:��������ߵ���
* @param store ���
* @param T	�����ֵ�ɭ��ָ��
* @return:void
*/
void Writer(BTree store, CSTree T)
{
	printf("����������:");
	char a[NAME];
	scanf("%s", a);
	if (ERROR == findWriter(T, a)) {
		printf("�Ҳ���������");
	}
	getch();
}
void main()
{
	BTree store;
	CSTree T;//������
	initBTree(store);
	InitTree(T);
	welcome();
	test(store,T);
	FILE* fp=logStart();
	while (1)
	{
		system("cls");
		mainMenu();
		gotoxy(x0, y0++); printf("��ѡ����:");
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