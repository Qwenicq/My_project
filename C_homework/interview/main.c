#include<stdio.h>
#include<string.h>
int main()
{
   char a[0x8]={0};
   char b[0x8]={0};
   const char s[]="hahaha";


    printf("hello,there is a gift for you :\na=%p\nb=%p\nNow,do what you want to do:\n",a,b);
    gets(b);

    if(!strncmp(a,s,6))
    printf("congratulate\n");



    return 0;
}
