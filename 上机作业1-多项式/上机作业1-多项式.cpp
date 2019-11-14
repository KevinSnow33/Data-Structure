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
typedef int Status;  //Status�Ǻ��������ͣ���ֵ�Ǻ������״̬����

typedef struct LNode
{
	int coe;  //ϵ�� coefficient
	int exp;  // ָ�� exponential
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
	printf("���������ʽ������");
	scanf("%d",&n1);
	
	Create_L(L1,n1);  
	Print_L(L1); 
	Reverse_L(L1,n1);
	Print_L(L1); 
	Calculate_L(L1,n1);
	
	LinkList La,Lb;
	int na,nb;
	printf("\n\n*��2��һԪ����ʽ�ĺͶ���ʽ*\n");
	printf("�������1������ʽ������");
	scanf("%d",&na);
	Create_L(La,na);  
	printf("\n�������2������ʽ������");
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
	
//	int coe[3]={1,2,3},exp[3]={1,2,3}; //���������� 
//	for(i=0;i<3;i++)				// �����ó��� 
//	{
//		p=(LinkList)malloc(sizeof(LNode));
//		p->coe=coe[i];
//		p->exp=exp[i];
//		p->next=NULL;
//		s->next=p;
//		s=p;
//	}	
	
	printf("\n�밴ָ��������������");	 
	for(i=1;i<=n;i++)
	{
		p=(LinkList)malloc(sizeof(LNode));
		printf("\n  �������%d��ϵ��(����)��",i);
		scanf("%d",&p->coe);
		printf("  �������%d��ָ��(����)��",i);
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
	
	printf("\n*���ڵĶ���ʽ������������*"); 
		 
	while(p)
	{
		printf("\n��%d��ϵ��Ϊ��%d",i,p->coe);
		printf("    ��%d��ָ��Ϊ��%d",i,p->exp);
		p=p->next;  i++;
	}	
}

void Reverse_L(LinkList &L,int n)
{
	int i,j;
	
	printf("\n\n*�͵����ö���ʽ*\n"); 
	
	for(i=0;i<n-1;i++)
	{
		LinkList p=L->next,q=L;
		
		for(j=0;j<n-2;j++)	//�ҵ���β�ڵ��ǰһ�ڵ��ָ�� 
			p=p->next;
		for(j=0;j<i;j++)	//�ҵ�Ҫ����λ�ýڵ��ǰһ�ڵ��ָ�� 
			q=q->next;
		
		p->next->next=q->next;	 //β�ڵ���nextָ�����λ�ýڵ�ĺ�� 
		q->next=p->next;		//����λ�ýڵ��ǰһ�ڵ��ָ��ָ��β�ڵ� 
		p->next=NULL;		//β�ڵ��ǰһ�ڵ��Ϊβ�ڵ㣬nextָ���		
	}
}

void Calculate_L(LinkList &L,int n)
{
	int i,j;
	int x,result=0,exp_result=1;
	printf("\n\n*����ʽ��ֵ*\n�������Ա�����ֵ(����)��");
	scanf("%d",&x);
	
	for(i=1;i<=n;i++)
	{
		LinkList p=L->next; //p��ʼָ���1�� 
		for(j=1;j<i;j++)	//pָ���i��	
			p=p->next;
		for(j=0,exp_result=1;j<p->exp;j++)	
			exp_result*=x;
		result+=(p->coe)*exp_result;			
	}
	printf("����ʽֵΪ:%d",result); 
}

void AddPolyn(LinkList &ha,LinkList &hb)
{
	LinkList qa,qb,u,pre;  
	int x;  //ϵ���Ӽ���� 
	
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

