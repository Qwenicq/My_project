/*
����Ҫ��ӡ�Ļ��ξ�����к��У�������������к��н��о���ĸ�ֵ��
���磺3 ��4�о���
1	2	3	4
10	11	12	5
9	8	7	6
*/

#include<stdio.h>

int  main(void){
int c,m,n,i,j;
int t=1;
int a[100][100];
printf("��������ξ�����к��У�\n");
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
for(j=i;j<n-i-1;j++)//���뵱ǰ�е���
a[i][j]=t++;
for(j=i;j<m-i-1;j++)//���뵱ǰ�е���
a[j][n-i-1]=t++;
for(j=n-i-1;j>i;j--)
{
if(t <= m*n)
a[m-i-1][j]=t++;//�����m-i-1�е���
}
for(j=m-i-1;j>i;j--)
{
if(t <= m*n)
a[j][i]=t++; //�����i�е���
}
}
if(t-1 < m*n) //�жϵ������к���������ʱ�����ĵ��Ǹ�����û�����룬�����һ������û������
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
