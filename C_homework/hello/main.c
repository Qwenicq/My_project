#include <stdio.h>
//#include <algorithm>
using namespace std;
int cap(int x,int y,int z){
    return x<y?((x<z)?x:z):((y<z?y:z));
}
int main(){
    int n,m,a[110][110],f[110][110];
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&a[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            if(a[i][j]==1) f[i][j]=cap(f[i-1][j],f[i-1][j-1],f[i][j-1])+1;
            //�ж������(i,j)�Ƿ����1,����f[i][j]��ֵΪ��Χ��������Сֵ+1
            else f[i][j]=0;   //����������a[i][j]==0
        }
    int bmax=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            bmax=max(bmax,f[i][j]);
    printf("%d",bmax);
    return 0;
}
