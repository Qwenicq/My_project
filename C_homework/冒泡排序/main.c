#include <stdio.h>
#include <stdlib.h>
int bubblesort(int *a,int n)
{
    int i,j,tmp,count;
    for(i=n-1;i>0;i--)
    {

        for(j=0;j<i;j++)
        {
            if(a[j]>a[j+1])
            {tmp=a[j+1];
            a[j+1]=a[j];
            a[j]=tmp;
            count++;

            }
        }
    }
    printf("%d",count);

}
int main()
{
    int a[10000];
    int j,n,i;
   scanf("%d",&n);
   for(i=0;i<n;i++)
    scanf("%d",&a[i]);
   bubblesort(a,n);

    return 0;
}
