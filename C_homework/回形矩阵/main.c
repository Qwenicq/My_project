#include<stdio.h>
int main(void)
{
    int c,i,j,m,n;
    int t=1;
    int a[100][100];
    printf("请输入行和列：");
    scanf("%d%d",&m,&n);
    if(m>n)
    {
        if(n%2==0)
            c=n/2;
        else c=n/2+1;
    }else
    {
        if(m%2==0)
            c=m/2;
        else c=m/2+1;
    }
    for(i=0;i<c;i++)
    {
        for(j=i;j<n-i-1;j++)
            a[i][j]=t++;
        for(j=i;j<m-i-1;j++)
            a[j][n-i-1]=t++;
        for(j=n-i-1;j>i;j--)
        {
            if(t<=m*n)
                a[m-i-1][j]=t++;
        }
        for(j=m-i-1;j>i;j--)
    {
    if(t <= m*n)
     a[j][i]=t++;
    }
    }
    if(t-1<m*n)
        a[m/2][n/2]=m*n;
    printf("\n");
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
        {printf("%4d",a[i][j]);
    if((j+1)%n==0)
        printf("\n");}
    return 0;
}
