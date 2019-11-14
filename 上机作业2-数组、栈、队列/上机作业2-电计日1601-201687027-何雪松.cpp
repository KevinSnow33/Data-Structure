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
//Status是函数的类型，其值是函数结果状态代码
typedef int Status;
typedef int ElemType;
typedef int Status;
typedef char SElemType;
typedef int QElemType;
#define MAXN 200
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef struct node
{
    char s[310];
    int top;
}Stack;
typedef struct{
    QElemType *base;
    int front;
    int rear;
}SqQueue;

typedef struct{
	SElemType *base;
    SElemType *top;
    int stacksize;	
}SqStack;

void Reverse(ElemType a[],int m,int n);     
Status Move(void);
int weight(char ch, int flag); 
void transform(char str[]);
Status InitStack(SqStack &S);
Status GetTop(SqStack S,SElemType &e);
Status Push(SqStack &S,SElemType e);
Status Pop(SqStack &S,SElemType &e);
Status Fibonacci(void);

int main()
{
	int i,n,k;       
	printf("*1.数组右移*\n");
	Move();
	
	
	printf("\n\n*2.逆波兰式*\n");
	char str[100];
	printf("请输入表达式：");
    scanf("%s",str);
    printf("逆波兰式为：");
    transform(str);
	
	printf("\n\n*3.斐波那契数列*\n");	
    Fibonacci();
//	Fibonacci(&seq);
	
	return 0;
}


void Reverse(ElemType a[],int m,int n)             
{
	int temp;
	for (;m<n;m++,n--)
	{
		temp=a[m];
		a[m]=a[n];
		a[n]=temp; 
	}
}
Status Move(void)
{
	
 int n,i,k;
    ElemType *a;
    printf("输入数组的长度n：");
    scanf("%d",&n);
    a=(ElemType*)malloc(sizeof(ElemType)*n);
    printf("输入数组元素：");
    for(i=0;i<n;i++)
    scanf("%d",&a[i]);
    printf("输入右移位数k：");
    scanf("%d",&k);
    k=k%n;
	Reverse(a,0,n-k-1);
	Reverse(a,n-k,n-1);
	Reverse(a,0,n-1);
	printf("数组右移%d位结果：",k);
    for(i=0;i<n;i++)
        printf("%d ",a[i]);
        printf("\n");
    return OK;
}


int weight(char ch,int flag)
{
 	if(ch=='+'||ch=='-') return 1;
	if(ch=='*'||ch=='/') return 2;
	if(ch=='('&&flag==1) return 0;
	if(ch=='('&&flag==0) return 3;
}
void transform(char str[])
{
	Stack a;
	a.top=-1;
	int i,f=0,m=strlen(str);
	for(i=0;i<m;i++)
 	{
	 if(str[i]>='A'&&str[i]<'Z')
 	 {
		printf("%c",str[i]);
     }
	 else
	 {
	      if(a.top==-1)
		  { 
		 	a.s[++a.top]=str[i];
	        continue;
	      }
		  if(str[i]==')')
	      {
	         while(a.top!=-1&&a.s[a.top]!='(') 
	         printf("%c",a.s[a.top--]);
 			 --a.top;
	         continue;
	      }
		  if(weight(str[i],0)>weight(a.s[a.top],1))
		  {
	          a.s[++a.top]=str[i];
			  continue;
	 	  }
	 	     	  
	 	  while(a.top!=-1&&weight(str[i],0)<=weight(a.s[a.top],1)) 
		  {  										  
			 printf("%c",a.s[a.top]); 				   
			 --a.top; 
			 f=1;
		  }
		  if(f==1)
	  	  {
			   a.s[++a.top]=str[i];
			   f=0;
		  }
	 }
   }

   while(a.top!=-1)
   {
	 printf("%c",a.s[a.top--]);
   }
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
Status Fibonacci(void)
{
    SqQueue Q;
    int i,k,t,Max,e;
    printf("输入循环队列容量k的值:");
    scanf("%d",&k);
    printf("输入max的值:");
    scanf("%d",&Max);
    Q.base=(QElemType*)malloc((k+1)*sizeof(QElemType));
    if(!Q.base)
        exit(OVERFLOW);
    Q.front=Q.rear=0;
    while((Q.rear+1)%k!=Q.front)
    {
        Q.base[Q.rear]=0;
        Q.rear=(Q.rear+1)%k;
    }
    Q.base[Q.rear]=1;
    printf("斐波那契：\n");
    while(1)
    {
        t=0;
        for(i=0;i<k;i++)
        	t+=Q.base[(Q.front+i)%k];
        if(t>Max)
        	break;
        printf("%d ",Q.base[Q.front]);
        Q.front=(Q.front+1)%k;
        Q.rear=(Q.rear+1)%k; 
        Q.base[Q.rear]=t;
    }
    for(i=0;i<k;i++)
    	printf("%d ",Q.base[(Q.front+i)%k]);
    printf("\n");
    return OK;
}

