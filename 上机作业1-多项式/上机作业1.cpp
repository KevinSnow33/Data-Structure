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
typedef int Status;  //Status是函数的类型，其值是函数结果状态代码

typedef struct LNode
{
	int coe;  //系数 coefficient
	int exp;  // 指数 exponential
	struct LNode *next;
}LNode,*LinkList;


Status Create_L(LinkList &L,int n);
void Print_L(LinkList L);
void Reverse_L(LinkList &L,int n);  
void Calculate_L(LinkList &L,int n);
void AddPolyn(LinkList &ha,LinkList &hb);


int main(void)
{
	LinkList L1;
	int n1;	
	printf("请输入多项式项数：");
	scanf("%d",&n1);
	
	Create_L(L1,n1);  
	Print_L(L1); 
	Reverse_L(L1,n1);
	Print_L(L1); 
	Calculate_L(L1,n1);
	
	LinkList La,Lb;
	int na,nb;
	printf("\n\n*求2个一元多项式的和多项式*\n");
	printf("请输入第1个多项式项数：");
	scanf("%d",&na);
	Create_L(La,na);  
	printf("\n请输入第2个多项式项数：");
	scanf("%d",&nb);
	Create_L(Lb,nb);  
	
	AddPolyn(La,Lb);
	Print_L(La); 
	
	return 0;
}
 

Status Create_L(LinkList &L,int n)  
{
	LinkList p,s;  int i;
	
	L=(LinkList)malloc(sizeof(LNode));
	if(!L)
		exit(OVERFLOW);
	L->coe=0,L->exp=0;  L->next=NULL;
	s=L;
	
//	int coe[3]={1,2,3},exp[3]={1,2,3}; //测试用数据 
//	for(i=0;i<3;i++)				// 测试用程序 
//	{
//		p=(LinkList)malloc(sizeof(LNode));
//		p->coe=coe[i];
//		p->exp=exp[i];
//		p->next=NULL;
//		s->next=p;
//		s=p;
//	}	
	
	printf("\n请按指数升序输入数据");	 
	for(i=1;i<=n;i++)
	{
		p=(LinkList)malloc(sizeof(LNode));
		printf("\n  请输入第%d项系数(整数)：",i);
		scanf("%d",&p->coe);
		printf("  请输入第%d项指数(整数)：",i);
		scanf("%d",&p->exp);
		p->next=NULL;
		s->next=p;
		s=p;
	}	
	
	return OK;
}

void Print_L(LinkList L) 
{
	LinkList p=L;  int i=1;
	p=p->next;
	
	printf("\n*现在的多项式各项数据如下*"); 
		 
	while(p)
	{
		printf("\n第%d项系数为：%d",i,p->coe);
		printf("    第%d项指数为：%d",i,p->exp);
		p=p->next;  i++;
	}	
}

void Reverse_L(LinkList &L,int n)
{
	int i,j;
	
	printf("\n\n*就地逆置多项式*\n"); 
	
	for(i=0;i<n-1;i++)
	{
		LinkList p=L->next,q=L;
		
		for(j=0;j<n-2;j++)	//找到表尾节点的前一节点的指针 
			p=p->next;
		for(j=0;j<i;j++)	//找到要插入位置节点的前一节点的指针 
			q=q->next;
		
		p->next->next=q->next;	 //尾节点中next指向插入位置节点的后继 
		q->next=p->next;		//插入位置节点的前一节点的指针指向尾节点 
		p->next=NULL;		//尾节点的前一节点变为尾节点，next指向空		
	}
}

void Calculate_L(LinkList &L,int n)
{
	int i,j;
	int x,result=0,exp_result=1;
	printf("\n\n*多项式求值*\n请输入自变量的值(整数)：");
	scanf("%d",&x);
	
	for(i=1;i<=n;i++)
	{
		LinkList p=L->next; //p初始指向第1项 
		for(j=1;j<i;j++)	//p指向第i项	
			p=p->next;
		for(j=0,exp_result=1;j<p->exp;j++)	
			exp_result*=x;
		result+=(p->coe)*exp_result;			
	}
	printf("多项式值为:%d",result); 
}

void AddPolyn(LinkList &ha,LinkList &hb)
{
	LinkList qa,qb,u,pre;  
	int x;  //系数加减结果 
	
	qa=ha->next,qb=hb->next;  pre=ha;
	
	while((qa!=NULL)&&(qb!=NULL))
	{
		if(qa->exp<qb->exp)
		{
			pre=qa;
			qa=qa->next;
		}
		else if(qa->exp==qb->exp)
		{
			x=qa->coe+qb->coe;
			
			if(x!=0)
			{
				qa->coe=x;
				pre=qa;
			}
			else
			{
				pre->next=qa->next;
				free(qa);
			}
			qa=pre->next;
			u=qb;  qb=qb->next;
			free(u);
		}
		else if(qa->exp>qb->exp)
		{
			u=qb->next;  qb->next=qa;
			pre->next=qb; pre=qb; qb=u;
		}
	}
	
	if(qa==NULL)
		pre->next=qb;
		
	free(hb);	
}

