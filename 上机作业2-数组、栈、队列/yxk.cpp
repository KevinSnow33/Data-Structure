#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int ElemType;
typedef int Status;
typedef char SElemType;
typedef int QElemType;
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
Status Move(void);
void Reverse(int a[],int start,int end) ;
void ReversePolish(void);
Status InitStack(SqStack &S);
Status GetTop(SqStack S,SElemType &e);
Status Push(SqStack &S,SElemType e);
Status Pop(SqStack &S,SElemType &e);
Status Fibonacci(void);
int main()
{
	int k;
  	while(1)
  	{
  		printf("********************\n");
  		printf("** 1:数组循环右移 **\n");
  		printf("** 2:后缀表达式   **\n");
  		printf("** 3:斐波那契数列 **\n");
  		printf("** 0:退出程序     **\n");
  		printf("********************\n");
  		scanf("%d",&k);
  		switch(k)
  		{
  			case 1:
  				Move();
  				break;
  			case 2:
  				ReversePolish();
  				break;
  			case 3:
  				Fibonacci();
  				break;
  			case 0:
  				printf("程序已结束");
  				return 0;
  		}
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
void ReversePolish(void)
{
    int i,Length=0;
    SElemType ch;
    char A[100];
    printf("输入表达式：");
    scanf("%s",A);
    SqStack S,M;
    InitStack(S);
    InitStack(M);
    Push(S,'#');
    for(i=0;A[i]!='\0';i++)
    {
       switch (A[i])
        {
        case'(':
            Push(S,A[i]);
			break;
        case')':
        	GetTop(S,ch);
            while(ch!='(')
            {
                Pop(S,ch);
                Push(M,ch);
                GetTop(S,ch);
            }
            Pop(S,ch);
			break;
        case'+':
        case'-':
        	GetTop(S,ch);
            while(ch!='#')
            {
                if(ch=='(')
                   break;
                else
                {
                	Pop(S,ch);
                    Push(M,ch);
					GetTop(S,ch);
                }
            }
			Push(S,A[i]);
			Length++;
			break;
        case'*':
        case'/':
        	GetTop(S,ch);
            while(ch!='#'&&ch!='+'&&ch!='-')
            {
                if(ch=='(')
                    break;
                else
                {
                	Pop(S,ch);
                    Push(M,ch);
					GetTop(S,ch);
                }
        	}
			Push(S,A[i]);
			Length++;
			break;
        default:
            Push(M,A[i]);
            Length++;
        }
    }
    GetTop(S,ch);
    while(S.top!=S.base&&ch!='#')
    {
        Pop(S,ch);
        Push(M,ch);
        Length++;
        GetTop(S,ch);
    }
    char *result;
    result=(char*)malloc(sizeof(char)*(Length+1));
    result+=Length;
    *result='\0';
    result--;
    for(;M.top!=M.base;result--)
    {
        Pop(M,ch);
        *result=ch;
    }
    ++result;
    printf("后缀表达式为：");
    for(i=0;result[i]!='\0';i++)
        printf("%c",result[i]);	
    printf("\n");
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

    
