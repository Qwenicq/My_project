#include <stdio.h>
#include <stdlib.h>
int N=10000;
int main()
{
   int l,m,u,v,n,sum,t,f,i;
   int a[N];
   sum=0;
   scanf("%d %d",&l,&m);
   for(i=0;i<(m*2);i++)
    scanf("%d",&a[i]);
  i=0;
    while(i<m)
    {
        if((a[i]>a[i+2]&&a[i+1]>a[i+2])||(a[i]<a[i+2]&&a[i+2]<a[i+1]))
           {
               t=a[i+1]-a[i+2];

               i+=4;
              }
        else
       {
           t=a[i+1]-a[i];

        i+=2;
       }
       sum+=t;
    }
    f=l-sum-2;
    printf("%d",f);


    return 0;
}
