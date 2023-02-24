#include <stdio.h>
#include <stdlib.h>
int jiafaNum(int a,int c);
int JFNum(int a,int c);
int chengfaNum(int a,int c);
int cfNum(int a,int c);
int qyNum(int a,int c);
int jiecheng(int a);
int main()
{
    int a,b,q;
    char c;
    scanf("%d %c %d",&a,&c,&b);
    switch(c)
   {
    case'x':
    case'X':
        chengfaNum(a,b);
        break;
    case'/':
         cfNum(a,b);
        break;
    case'+':
         jiafaNum(a,b);
         break;
    case'-':
        JFNum(a,b);
        break;
    case'%':
        qyNum(a,b);
        break;
    case'!':
        jiecheng(a);
        break;
    default:
       break;
   }
    return 0;
}
int jiafaNum(int a,int c)
{
    int x,b,q;
    x=a;
    b=c;
    q=a+b;
   printf("%d",q);
}
int JFNum(int a,int c)
{

    int x,b,q;
    x=a;
    b=c;
    q=a-b;
   printf("%d",q);
}
int chengfaNum(int a,int c)
{
     int x,b,q;
    x=a;
    b=c;
    q=a*b;
   printf("%d",q);
}
int cfNum(int a,int c)
{
      int x,b,q;
    x=a;
    b=c;
    q=a/b;
   printf("%d",q);
}
int qyNum(int a,int c)
{
    int x,b,q;
    x=a;
    b=c;
    q=a%b;
   printf("%d",q);
}
int jiecheng(int a)
{
    int n,i,sum=1;
    n=a;5
    for(i=1;i<=n;i++)
    sum*=i;
    printf("%d",sum);

}
