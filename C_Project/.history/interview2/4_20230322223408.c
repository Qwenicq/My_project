#include<stdio.h>
#include<string.h>
int main(){
   char str[100];
   char temp;
   scanf("%s",&str);
   int n = strlen(str);
   int i,j,counter = 1, f=0, sum=0;
   for( i = n; i > 0;i--){
    for(j = 0;j<i;j++){
        if(str[j]>str[j+1]){
      temp = str[j];
      str[j]=str[j+1];
      str[j+1]=temp;
    }
   }
 }
 for(i=1;i<n;i++){
  if(str[i]==str[0]){
  counter++;
  f = counter%2;
  sum += f;}
  else str[0] =str[i];
 }
   if(sum == 0)
   printf("Yes");
   else
   printf("No");
   return 0;
}