#include <stdio.h>
#include <stdlib.h>

int main()
{
    float w,h;
    int t;
    printf("������������(m)��");
    scanf("%f",&h);
    printf("�������������(kg)��");
    scanf("%f",&w);
    t=(int)(w/(h*h));
    printf("��֬��=%d\n",t);
    if(t<18)
     {
         printf("������\n");
    }else if(t>=18&&t<25)
      {
          printf("��������\n");
    }else  if(t>=25&&t<27)
       {
        printf("��������\n");
    }else
        printf("����\n");

    return 0;

}
