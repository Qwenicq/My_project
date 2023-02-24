#include <stdio.h>
#include<stdlib.h>
int main()
{
    int n,count,i,m;
    int a[100];
    printf("input");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    a[i]=0;
    i=count=n=0;
    while(count<n-1)
     {
    if(a[i]==0)
        m++;
    if(m==3)
      {
          a[i]=1;
        m=0;
        count++;
     }
     }
     i++;
     if(i==n)
     i=0;

     while(a[i])
        i++;
         printf("%d",i+1);


     return 0;
}
