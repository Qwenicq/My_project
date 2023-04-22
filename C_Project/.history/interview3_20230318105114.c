#include<stdio.h>
int main(){
    int day, i = 1, N;
    scanf("%d",&N);
    for(day = 0;day < N;day++){
        i = (i + 1) * 2;
    }
    printf("%d",i);
}