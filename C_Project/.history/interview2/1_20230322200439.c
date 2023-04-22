#include<stdio.h>
int main(){
    int N,i;
    int a[1000]={0};
    int b;
    scanf("%d", &N);
    for(i = 0; i < N; i++){
        scanf("%d", &b);
        if(b > -1000000 && b < 1000000){
            a[i] = b;
            b = 0;
        }
    }
    int j, temp;
    for(i = 0; i < N; i++){
        for(j = 0; j < i; j++){
            if(a[j] < a[j+1]){
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
     int sum = 0;
    for(i = 1;i < N;i++){
        sum+=a[i];
    }
    printf("%d",sum);
    return 0;
}