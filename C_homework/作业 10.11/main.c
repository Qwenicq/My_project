#include <stdio.h>
#define PI 3.14159
int main(void)
{
   float r,h,l,v;
    printf("输入半径=\n");
    printf("输入高=\n");
    scanf("%f%f",&r,&h);

   N:if(r<=0||h<=0)//判断半径和高度的合理性
    {
        printf("输入半径 =");
        printf("输入高=");
        scanf("%f %f",&r,&h);
        goto N;                  //返回循环
    }else
   {
    v=(PI*r*r*h)/3;         //计算圆锥的体积
    printf("体积=%.2f\n",v);
       l=sqrt(r*r+(h*h));
    printf("母线长=%.2f\n",l*l);
    printf("表面积=%.2f\n",(r*r*PI)+(PI*r*l));
   }
return 0;
}
