#include<stdio.h>
#include<string.h>
int main(){
   char str[100];
   scanf("%s",&str);
   int n = strlen(str);
   printf("%d\n",n);
   int i,j,counter = 0, f=0, sum=0;
   for( i = 0; i < (n/2);i++){
    for(j=(i+1);j<n+1;j++){
        if(str[j] == str[i])
        counter++;
    }
    printf("%d\n",counter);
    f = counter%2;
    counter = 0;
    sum += f;
    f = 0;
   }
   if(sum == 0)
   printf("Yes");
   else
   printf("No");
   return 0;
}