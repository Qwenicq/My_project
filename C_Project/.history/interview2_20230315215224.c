#include<stdio.h>
int main(){
    int N,day,peach = 1;
    scanf("%d",&N);
    for(i = 0;i < N;i++){
        peach = ( peach + 1 ) * 2;
    }
    printf("%d",peach);
}