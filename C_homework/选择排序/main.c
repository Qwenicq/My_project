#include <stdio.h>
#include <stdlib.h>
void swap(int *p1,int *p2)
{
    int temp;
    temp=*p1;
    *p1=*p2;
    *p2=temp;
}
int selectsort(int *a,int n)
{
    int i,j,minNum,maxNum,ileft,iright;
    ileft=0;
    iright=n-1;
    while(ileft<iright)
    {
        maxNum=minNum=ileft;
    for(i=ileft;i<iright;i++)
    {
        if(a[i]<a[minNum])
            minNum=i;
        if(a[i]>a[maxNum])
            maxNum=i;
    }
    if(minNum!=ileft) swap(&a[ileft],&a[minNum]);
    if(maxNum==ileft) maxNum=ileft;
    if(maxNum!=iright) swap(&a[iright],&a[maxNum]);
    ileft++;
    iright--;
    }
}
int main()
{
    int a[7]={3,6,4,7,12,2,9};
    int i;
    selectsort(a,7);
    for(i=0;i<7;i++)
        printf("%5d",a[i]);
    printf("\n");
    return 0;
}
