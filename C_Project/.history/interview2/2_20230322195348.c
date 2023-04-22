#include<stdio.h>
int main(){
   int i, j, n,counter=0;
   scanf("%d",&n);
   long int a[10001];
   long int temp;
   for(i = 0;i < n;i++){
    scanf("%d",&a[i]);
   }
   
    for(j = 0;j < n; j++){
        if(a[j]>a[j+1]){
            temp = a[j];
            a[j+1] = a[j];
            a[j] = temp;
            counter++;
            printf("%d",a[j]);
        }
    }
   
   printf("%d",counter);
}