#include<stdio.h>
int main(){
   int n,a[1000]={0};
   scanf("%d",&n);
   if(n < 3 || n > 10000)
   {return -1;}
   int i,count=0;
   for(i=0;i<n;i++){
    scanf("%d",&a[i]);
   }
   
   for(i =1;i<n;i++){
    if(i<9998){
    if(a[i]<a[i-1] ){
     if((a[i]<a[i+1])||(a[i]==a[i+1] && a[i+1]<a[i+2]))
       count++;
     }
   }
   else break;
   }
   printf("%d",count);
   return 0;
}