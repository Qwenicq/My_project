/*
输入要打印的回形矩阵的行和列，并根据输入的行和列进行矩阵的赋值；
形如：3 行4列矩阵：
1	2	3	4
10	11	12	5
9	8	7	6
*/

#include<stdio.h>

int  main(void){
int c,m,n,i,j;
int t=1;
int a[100][100];
printf("请输入回形矩阵的行和列：\n");
scanf("%d%d",&m,&n);
if(m > n)
{
if(n%2 == 0)
c=n/2;
else
c=n/2+1;
}
else
{
if(m%2 == 0)
c=m/2;
else
c=m/2+1;
}
for(i=0;i<c;i++)
{
for(j=i;j<n-i-1;j++)//输入当前行的数
a[i][j]=t++;
for(j=i;j<m-i-1;j++)//输入当前列的数
a[j][n-i-1]=t++;
for(j=n-i-1;j>i;j--)
{
if(t <= m*n)
a[m-i-1][j]=t++;//输入第m-i-1行的数
}
for(j=m-i-1;j>i;j--)
{
if(t <= m*n)
a[j][i]=t++; //输入第i列的数
}
}
if(t-1 < m*n) //判断当输入行和列是奇数时最中心的那个数有没有输入，即最后一个数有没有输入
a[m/2][n/2] = m*n;


printf("\n");
for(i=0;i<m;i++)
for(j=0;j<n;j++)
{
printf("%4d", a[i][j]);
if(((j+1)%n) == 0)
printf("\n");
}
return 0;
}
