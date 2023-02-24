#include <stdio.h>
#include <stdlib.h>
#include<time.h>

int main()
{
    printf("Hello Xu Qiaoan!\n");
    int guess,counter=0;
    int ret,magic;
    srand(time(NULL));
     magic=rand()%100+1;
    do{
        n:printf("please input guess number:");
        ret=scanf("%d",&guess);
        while(ret!=1){
            while(getchar()!='\n');
            goto n;
        }
        counter++;
        if(guess>magic)
            printf("Too large\n");
            else if(guess<magic)
                printf("Too small\n");
            else printf("right\n");
    }while(guess!=magic&&counter<10);
    printf("counter=%d\n",counter);
    return 0;
}
