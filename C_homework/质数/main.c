#include <stdio.h>
#include <stdlib.h>

int main()
{
   int n,i,j,m=0;
   scanf("%d",&n);
   int a[1000000];
   a[m]=2;
   for(i=3;i<100000;i+=2)
      {
          for(j=2;j<100000;j++)
{


           if(i%j==0) {
                break;
           }
}
                if(i==j)
           {
               a[m]=i;
               m++;}
      }

   printf("%d",a[n-2]);
   return 0;
}
