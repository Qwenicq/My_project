#include<stdio.h>
#include<math.h>
const int N=100;
int check(int x,int *p1,int *p2,int n,long int m)
    ;

int main()
{
    int a[N],b[N];
    int n,i;
    long int m;
    //printf("请输入牌的种类和空白牌的数量：");
    scanf("%d %ld",&n,&m);
    for(i=0;i<n;i++)scanf("%d",&a[i]);
    for(i=0;i<n;i++)scanf("%d",&b[i]);
    int l=1,r=4*n;

    while(l<r)
    {
        int mid=l+r+1;


   if(check(mid,a,b,n,m)==1)
        l=mid;

   else {r=mid-1;
   l++;}



}
printf("%d",l);
return 0;
}
int check(int x,int *p1,int *p2,int n,long int m)
    {
    int left=0;
    int i;
    long int sum=0;

    for(i=0;i<n;i++)
    {
        if(p1[i]<x)
            left=x-p1[i];
        if(left>p2[i])
            return 0;
        else sum+=left;

    }
    if(sum>m)
    return 0;
   return 1;
}


