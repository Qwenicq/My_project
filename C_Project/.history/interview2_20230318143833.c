#include<stdio.h>
int main(){
    int N,day,peach=1;
    scanf("%d",&N);//输入共有几天
    for(day = 0;day <= N;day++){
        peach = ( peach + 1 ) * 2;//j计算桃子数量
    }
    printf("%d",peach);
}