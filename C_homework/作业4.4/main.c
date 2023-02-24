#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char ch;
    printf("please a key and then press enter:");
    ch=getchar();
    if(ch>=65&&ch<=90 )
    ch=ch+32;
    else if(ch>=97&&ch<=122)
        ch=ch-32;
    else
        printf("error");
    printf("%c,%d\n",ch,ch);
    return 0;
}
