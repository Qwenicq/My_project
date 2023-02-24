#include <stdio.h>
#include <stdlib.h>

int main()
{
    float w,h;
    int t;
    printf("请输入你的身高(m)：");
    scanf("%f",&h);
    printf("请输入你的体重(kg)：");
    scanf("%f",&w);
    t=(int)(w/(h*h));
    printf("体脂率=%d\n",t);
    if(t<18)
     {
         printf("低体重\n");
    }else if(t>=18&&t<25)
      {
          printf("正常体重\n");
    }else  if(t>=25&&t<27)
       {
        printf("超重体重\n");
    }else
        printf("超重\n");

    return 0;

}
