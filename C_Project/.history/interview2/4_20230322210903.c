#include<stdio.h>
#include<string.h>
int main(){
   char str[100];
   scanf("%s",&str);
   int n = strlen(str);
   printf("%d\n",n);
   int i,j,counter = 0, f=0, sum=0;
   for( i = 0; i < n;i++){
    if(str[i++]==str[i])
    counter++;
    f = 0;
   }
   if(sum == 0)
   printf("Yes");
   else
   printf("No");
   return 0;
}