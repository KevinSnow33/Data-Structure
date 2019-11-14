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
//Status�Ǻ��������ͣ���ֵ�Ǻ������״̬����
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
  		printf("** 1:�ж���ȫ������ **\n");
  		printf("** 2:ɭ�ֵ�ϵ�в��� **\n");
  		printf("**********************\n");
  		printf("����������в�������ţ�\n");
  		scanf("%d",&i);
  		switch(i)
  		{
  			case 1:				
  					BiTree Tree;
  					printf("�밴���������������ݣ�����#��Ϊ��������\n");
  					CreateBiTree(Tree);
  					printf("����������������ݽ��Ϊ��");
  					PreOrderTraverse(Tree,Printdata);
  					printf("\n");
  					LevelTraverse(Tree); //����������㷨Ҫ�����ڵ�������������������ĸ��ڵ� 
//  					LR_Exchange(Tree->lchild);   //���������������� 
//  					PreOrderTraverse(Tree,Printdata);
//  					printf("\n");	
//						Find_x(Tree->lchild);  //�ǵݹ飨��α�����Ѱ��ֵΪx�Ľ�㲢���ص�ַ 
  				
  					break;
  			case 2:
  			        CSTree forest;
  			    	printf("�밴��������ɭ�ֵ����ݣ�����#��Ϊ��������\n");
  					CreateCSTree(forest);
  					printf("��ɭ���������������ݽ��Ϊ��\n");
  					InOrderTraverse(forest,Printdata);
  					LeafNode_Count(forest->firstchild);  //���ڵ�������������������ĸ��ڵ� 
  					printf("��ɭ����Ҷ�ӽڵ���Ϊ��%d\n",leaf_count);
  					leaf_count=0;
  					Tree_Count(forest);
  					printf("��һ�����ĸ߶�Ϊ:%d\n\n",FirstTreeDepth(forest->firstchild));
  					break;
		}
	}
	return 0;
}


Status CreateBiTree(BiTree &T)	//�������� ����������������ڵ��������Ϊ�գ���ڵ���������ĸ��ڵ㣩
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

Status Printdata(char data)     //print����data 
{
	printf("%c",data);
}

Status PreOrderTraverse(BiTree &T,Status(*Visit)(char data))  //��������������� 
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

Status LevelTraverse(BiTree &T)  //��α����ж��Ƿ�Ϊ��ȫ������ 
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
		printf("������ȫ������\n\n");
	else
		printf("����ȫ������\n\n");	
}

Status LR_Exchange(BiTree &T)  //������������ 
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

BiTree Find_x(BiTree &T)  //�ǵݹ飨��α�����Ѱ��ֵΪx�Ľ�㲢���ص�ַ 
{
	int f=0,r=0;
	BiTree p,q[100];
	q[r++]=T;
			
	while(f<r)
	{
		p=q[f++];
		if(p->data=='a')
		{
			printf("����ֵΪx�Ľ�㣬��ַΪ��"); 
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

Status CreateCSTree(CSTree &T)	//������ɭ�� ���������ɭ�֣����ڵ��������Ϊ�գ���ڵ���������ĸ��ڵ㣩
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

Status InOrderTraverse(CSTree &T,Status(*Visit)(char data))  //����ǵݹ������������
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

Status LeafNode_Count(CSTree &T)   //Ҷ�ӽ����� 
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
	printf("ɭ���й���%d����\n",i); 
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
�������ݣ� 
abd###c###  abd##e##cf####  ��ȫ������ 
abd###ce####  	����ȫ������ 
����������������ǰ��abd###c#e### ������ ace###b#d### 
������ɭ��  ab#c#d##ef##gh#ij##### (ab#cd##e####)  ����������bcdafehjig (bdcea)
*/ 
