#pragma once
# include <stdio.h>
# include <conio.h>
# include <stdlib.h>
# include <windows.h>
# include <string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define SUCCESS 1
#define m 3                    //B���Ľף�����Ϊ3
#define NAME 20					//�������ֵĳ���
#define X0 12					//��ʼ��Ļx��λ��
#define Y0 7					//��ʼ��Ļy��λ��
#define HEARDER1 "+--------------------------�鱾��Ϣ---------------------------+\n"
#define HEARDER2 "|    ���|       ����         |      ����    | �ִ��� |�ܿ�� |\n"
#define HEARDER3 "|--------|--------------------|--------------|--------|-------|\n"
#define FORMAT   "|%8lu|%20s|%14s|%8d|%7d|\n"
#define DATA p->username,p->fee_date,p->incount_date,p->money,p->money_afterfee,p->type,p->num,p->adress
#define END	     "|--------|--------------------|--------------|--------|-------|\n"

typedef int Status;

//�����ߵ���Ϣ
typedef struct ReaderNode {
	unsigned long int	cardNum;//ͼ��֤��
	char	name[NAME];			//ѧ������
	int    time;				//�����鱾��ʱ�䣨Ϊʲô�����ﲻʹ�ý��ĵ��鱾�������أ���
}ReaderNode, *ReaderList;
typedef ReaderNode ElemType;//�����߷��������У�ԤԼ�����ݴ���ڶ�����
typedef struct LNode {
	ElemType data;     //������
	struct LNode *next;//ָ����ָ����һ�����
}LNode, *LinkList;

typedef struct {
	ElemType *elem;//�洢�ռ�Ļ�ַ
	int front;     //��ͷλ��
	int rear;      //��βλ�ָ꣬ʾ��βԪ�ص���һλ��
	int maxSize;   //�洢����
}SqQueue;
//�鱾����Ϣ
typedef struct BookNode {//��š����������ߡ��ִ������ܿ����
	unsigned long int num;//���
	char name[NAME];		  //����
	char writer[NAME];		  //����
	int  current;			  //�ִ���
	int  total;				  //�ܿ����
	LinkList	reader;		  //����������
	LinkList	preBooker;	      //ԤԼ�߶���
}BookNode, *BookList;
typedef BookNode KeyType;
typedef struct BTNode {
	int keynum;                //��㵱ǰ�Ĺؼ��ָ���
	KeyType key[m + 1];        //�ؼ������飬key[0]δ��
	struct BTNode *parent;    //˫�׽��ָ��
	struct BTNode *ptr[m + 1];//���ӽ��ָ������
							  //Record *recptr[m+1];    //��¼ָ��������0�ŵ�Ԫδ��
}BTNode, *BTree;            //B���Ľ�㼰ָ������

typedef struct {            //���ڷ��ز��ҵ���Ϣ
	BTree pt;                //ָ���ҵ��Ľ��
	int       i;                //1<=i<=m,�ڽ���еĹؼ���λ��
	int  tag;                //1:���ҳɹ���0:����ʧ��
}Result;                    //B���Ĳ��ҽ������
typedef BookNode TElemType;
typedef struct CSTNode {
	TElemType data; //������
	struct CSTNode *firstChild, *nextSibling;//������ָ�룬���ֵ�ָ��    
}CSTNode, *CSTree, CSForest;  //�����ֵ�����
