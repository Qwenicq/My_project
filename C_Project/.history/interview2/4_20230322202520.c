#include<stdio.h>
#include<string.h>
int main(){
   char str[100];
   scanf("%s",&str);
   int n = strlen(str);
   int i = 0,j,counter = 1;
   for ( i = 0; i < n; i++)
   {
    for(j=1;j<n;j++){
        if(str[i] == str[j])
        counter++;
    }
   }
   if(counter%2 == 0)
   printf("Yes");
   else
   printf("No");
}