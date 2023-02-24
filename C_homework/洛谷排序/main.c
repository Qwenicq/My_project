#include<stdio.h>
int a[100],n;
void quicksort(int left,int right)
{
    int temp,i,j,t;
    if(left>right)
        return;
    temp=a[left];
    i=left;
    j=right;
    while(i!=j)
    {
        while(a[j]>=temp && i<j) j--;
        while(a[i]<=temp && i<j) i++;
        if(i<j)
        {
            t=a[i];
            a[i]=a[j];
            a[j]=t;
        }
    }
    a[left]=a[i];
    a[i]=temp;
    quicksort(left,i-1);
    quicksort(i+1,right);
    return;
}
int main()
{
    int m,n,i;
    scanf("%d %d",&n,&m);
    for(i=1;i<=m;i++)
    {
        scanf("%d",&a[i]);
    }
    quicksort(1,m);
    for(i=1;i<=m;i++)
        printf("%2d",a[i]);
    printf("\n");
    return 0;
}
