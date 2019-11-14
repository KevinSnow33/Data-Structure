#define TRUE 1 
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#include"malloc.h"
#include"stdlib.h"
#include <stdio.h>
#include <string.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
//Status是函数的类型，其值是函数结果状态代码
typedef int Status;
typedef int ElemType;
typedef int Status;
typedef int QElemType;
typedef struct BiTNode
{
	char data;
	struct BiTNode *lchild,*rchild;
}BitNode,*BiTree;
typedef struct CSnode
{
	char data;
	struct CSnode *firstchild,*nextsibling;
} CSNode,*CSTree;
typedef CSTree SElemType;
typedef struct{
	SElemType *base;
    SElemType *top;
    int stacksize;	
}SqStack;

Status CreateBiTree(BiTree &T);
Status Printdata(char data);
Status PreOrderTraverse(BiTree &T,Status(*Visit)(char data));
Status LevelTraverse(BiTree &T);
Status LR_Exchange(BiTree &T);
BiTree Find_x(BiTree &T);
Status CreateCSTree(CSTree &T); 
Status InitStack(SqStack &S);
Status GetTop(SqStack S,SElemType &e);
Status Push(SqStack &S,SElemType e);
Status Pop(SqStack &S,SElemType &e);
Status StackEmpty(SqStack S);
Status InOrderTraverse(CSTree &T,Status(*Visit)(char data)) ;
int leaf_count=0;
Status LeafNode_Count(CSTree &T) ;
Status Tree_Count(CSTree &T);
Status FirstTreeDepth(CSTree &T);

int main()
{
	int i,j;
	while(1)
	{
		printf("**********************\n");
  		printf("** 1:判断完全二叉树 **\n");
  		printf("** 2:森林的系列操作 **\n");
  		printf("**********************\n");
  		printf("请输入想进行操作的序号：\n");
  		scanf("%d",&i);
  		switch(i)
  		{
  			case 1:				
  					BiTree Tree;
  					printf("请按先序输入树的数据（输入#则为空树）：\n");
  					CreateBiTree(Tree);
  					printf("该树按先序输出数据结果为：");
  					PreOrderTraverse(Tree,Printdata);
  					printf("\n");
  					LevelTraverse(Tree); //非先序遍历算法要传根节点的左子树，才是真正的根节点 
//  					LR_Exchange(Tree->lchild);   //交换所有左右子树 
//  					PreOrderTraverse(Tree,Printdata);
//  					printf("\n");	
//						Find_x(Tree->lchild);  //非递归（层次遍历）寻找值为x的结点并返回地址 
  				
  					break;
  			case 2:
  			        CSTree forest;
  			    	printf("请按先序输入森林的数据（输入#则为空树）：\n");
  					CreateCSTree(forest);
  					printf("该森林中序遍历输出数据结果为：\n");
  					InOrderTraverse(forest,Printdata);
  					LeafNode_Count(forest->firstchild);  //根节点的左子树，才是真正的根节点 
  					printf("该森林中叶子节点数为：%d\n",leaf_count);
  					leaf_count=0;
  					Tree_Count(forest);
  					printf("第一颗树的高度为:%d\n\n",FirstTreeDepth(forest->firstchild));
  					break;
		}
	}
	return 0;
}


Status CreateBiTree(BiTree &T)	//先序建立树 （建立后的树，根节点的右子树为空，左节点才是真正的根节点）
{
	char ch='#';
	scanf("%c",&ch);
	if(ch=='#')
		T=NULL;
	else
	{
		if(!(T=(BiTNode*)malloc(sizeof(BiTNode))))
			exit(OVERFLOW);
		T->data=ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return OK;		
}

Status Printdata(char data)     //print数据data 
{
	printf("%c",data);
}

Status PreOrderTraverse(BiTree &T,Status(*Visit)(char data))  //先序遍历操作函数 
{
	if(T)
	{
		if(Visit(T->data))
		{
			if(PreOrderTraverse(T->lchild,Visit))
			{
				if(PreOrderTraverse(T->rchild,Visit))
					return OK;
				else
					printf("#");
			}		
			else
				printf("#");
		}
		else
			printf("#");
		
		return ERROR;
	}
	else
		printf("#");
	return OK;
}

Status LevelTraverse(BiTree &T)  //层次遍历判断是否为完全二叉树 
{
	int f=0,r=0;
	int a[100]={0},i=0,j=0,flag=1;
	BiTree p,q[100];
	q[r++]=T->lchild;	
	if(T->lchild)
	{
		a[0]=1;
		i++,j++;
	}	
		
	while(f<r)
	{
		p=q[f++];
		j++;
		if(p->lchild)
		{
			q[r++]=p->lchild;
			a[i++]=j;		
		}
		j++;
		if(p->rchild)
		{
			q[r++]=p->rchild;
			a[i++]=j;		
		}    
	}

	for(i=0;i<99;i++)
	{
		if((a[i+1]-a[i])>1)
		{
			flag=0;
			break;
		}	
	}
	
	if(flag==0)
		printf("不是完全二叉树\n\n");
	else
		printf("是完全二叉树\n\n");	
}

Status LR_Exchange(BiTree &T)  //交换左右子树 
{
	BiTree t;
	if(T)
	{
		if(T->lchild||T->rchild)
		{	
			if(T->lchild)
				LR_Exchange(T->lchild);
			if(T->rchild)
			LR_Exchange(T->rchild);	
			t=T->rchild;
			T->rchild=T->lchild;
			T->lchild=t;
		}	
	}	
	return OK;
}

BiTree Find_x(BiTree &T)  //非递归（层次遍历）寻找值为x的结点并返回地址 
{
	int f=0,r=0;
	BiTree p,q[100];
	q[r++]=T;
			
	while(f<r)
	{
		p=q[f++];
		if(p->data=='a')
		{
			printf("存在值为x的结点，地址为："); 
			return p; 
		}	

		if(p->lchild)
		{
			q[r++]=p->lchild;		
		}
		if(p->rchild)
		{
			q[r++]=p->rchild;		
		}
	}
	
} 

Status CreateCSTree(CSTree &T)	//先序建立森林 （建立后的森林，根节点的右子树为空，左节点才是真正的根节点）
{
	char ch='#';
	scanf("%c",&ch);
	if(ch=='#')
		T=NULL;
	else
	{
		if(!(T=(CSNode*)malloc(sizeof(CSNode))))
			exit(OVERFLOW);
		T->data=ch;
		CreateCSTree(T->firstchild);
		CreateCSTree(T->nextsibling);
	}
	return OK;		
}

Status InitStack(SqStack &S)
{
	S.base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!S.base)
		exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return OK;	
}
Status GetTop(SqStack S,SElemType &e)
{
	if(S.top==S.base)
		return ERROR;
	e=*(S.top-1);
	return OK;
}
Status Push(SqStack &S,SElemType e)
{
	if(S.top-S.base>=S.stacksize)
	{
		S.base=(SElemType*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!S.base)
		exit(OVERFLOW);
		S.top=S.base+S.stacksize;
		S.stacksize+=STACKINCREMENT;
	}
	*S.top++=e;
	return OK;
}
Status Pop(SqStack &S,SElemType &e)
{
	if(S.top==S.base)
		return ERROR;
	e=*--S.top;
	return OK;	
}
Status StackEmpty(SqStack S)
{
	if(S.top==S.base)
		return TRUE;
	else
		return FALSE;	
}

Status InOrderTraverse(CSTree &T,Status(*Visit)(char data))  //中序非递归遍历操作函数
{
	CSTree p; SqStack S;
	InitStack(S); Push(S,T);
	while(!StackEmpty(S))
	{
		while(GetTop(S,p)&&p)
			Push(S,p->firstchild);
		Pop(S,p);
		if(!StackEmpty(S))
		{
			Pop(S,p); 
			if(!Visit(p->data))
				return ERROR;
			Push(S,p->nextsibling);	
		}	
	}
}

Status LeafNode_Count(CSTree &T)   //叶子结点计数 
{
	if(T)
	{	
		if(T->firstchild)
			LeafNode_Count(T->firstchild);	
		else
			leaf_count++; 
		if(T->nextsibling)			 
			LeafNode_Count(T->nextsibling);
	}
	return OK;
}

Status Tree_Count(CSTree &T)
{	
	CSTree q=T->firstchild;
	if(!q)
		return ERROR;
	int i=1;	
	while(q->nextsibling)
	{
		i++;
		q=q->nextsibling;
	}
	printf("森林中共有%d颗树\n",i); 
	return OK;
}

Status FirstTreeDepth(CSTree &T)
{
	int depth=0,d;
	CSTree p;
	if(!T)
		return 0;
	p=T->firstchild;
	while(p)
	{
		d=FirstTreeDepth(p);
		if(d>depth)
			depth=d;
		p=p->nextsibling;
	}
	return depth+1;		
}


/*
测试数据： 
abd###c###  abd##e##cf####  完全二叉树 
abd###ce####  	非完全二叉树 
所有左右子树交换前：abd###c#e### 交换后： ace###b#d### 
先序建立森林  ab#c#d##ef##gh#ij##### (ab#cd##e####)  中序输出结果bcdafehjig (bdcea)
*/ 
