#include <stdio.h>
#include <stdlib.h>
int shellsort(int *a,int n)
{
    int i,istep,j,temp;
    for(istep=n/2;istep>0;istep/=2)
    {
        for(i=istep;i<n;i++)
         {
             temp=a[i];
            for(j=i-istep;j>=0&&temp<a[j];j-=istep)
          a[j+istep]=a[j];

         a[j+istep]=temp;
    }
    }
}
int main()
{
    int n,i,a[10010];
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    shellsort(a,n);
    for(i=0;i<n;i++)
        printf("%2d",a[i]);
        printf("\n");
    system("pause");
    return 0;
}
