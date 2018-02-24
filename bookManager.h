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
#define m 3                    //B树的阶，此设为3
#define NAME 20					//各种名字的长度
#define X0 12					//初始屏幕x的位置
#define Y0 7					//初始屏幕y的位置
#define HEARDER1 "+--------------------------书本信息---------------------------+\n"
#define HEARDER2 "|    书号|       书名         |      著者    | 现存量 |总库存 |\n"
#define HEARDER3 "|--------|--------------------|--------------|--------|-------|\n"
#define FORMAT   "|%8lu|%20s|%14s|%8d|%7d|\n"
#define DATA p->username,p->fee_date,p->incount_date,p->money,p->money_afterfee,p->type,p->num,p->adress
#define END	     "|--------|--------------------|--------------|--------|-------|\n"

typedef int Status;

//借阅者的信息
typedef struct ReaderNode {
	unsigned long int	cardNum;//图书证号
	char	name[NAME];			//学生姓名
	int    time;				//借阅书本的时间（为什么我这里不使用借阅的书本的链表呢？）
}ReaderNode, *ReaderList;
typedef ReaderNode ElemType;//借阅者放在链表中，预约者数据存放在队列中
typedef struct LNode {
	ElemType data;     //数据域
	struct LNode *next;//指针域，指向下一个结点
}LNode, *LinkList;

typedef struct {
	ElemType *elem;//存储空间的基址
	int front;     //队头位标
	int rear;      //队尾位标，指示队尾元素的下一位置
	int maxSize;   //存储容量
}SqQueue;
//书本的信息
typedef struct BookNode {//书号、书名、著者、现存量和总库存量
	unsigned long int num;//书号
	char name[NAME];		  //书名
	char writer[NAME];		  //著者
	int  current;			  //现存量
	int  total;				  //总库存量
	LinkList	reader;		  //借阅者链表
	LinkList	preBooker;	      //预约者队列
}BookNode, *BookList;
typedef BookNode KeyType;
typedef struct BTNode {
	int keynum;                //结点当前的关键字个数
	KeyType key[m + 1];        //关键字数组，key[0]未用
	struct BTNode *parent;    //双亲结点指针
	struct BTNode *ptr[m + 1];//孩子结点指针数组
							  //Record *recptr[m+1];    //记录指针向量，0号单元未用
}BTNode, *BTree;            //B树的结点及指针类型

typedef struct {            //用于返回查找的信息
	BTree pt;                //指向找到的结点
	int       i;                //1<=i<=m,在结点中的关键字位序
	int  tag;                //1:查找成功，0:查找失败
}Result;                    //B树的查找结果类型
typedef BookNode TElemType;
typedef struct CSTNode {
	TElemType data; //数据域
	struct CSTNode *firstChild, *nextSibling;//最左孩子指针，右兄弟指针    
}CSTNode, *CSTree, CSForest;  //孩子兄弟链表
