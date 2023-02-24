#include <stdio.h>
int main(viod)
{
    const double PI=3.14159;
    double r;
     printf("输入半径=");
    scanf("%lf",&r);
   N:if(r<=0)
    {
        printf("输入半径");
        scanf("%lf",&r);
        goto N;
    }else
   {


    printf("周长=%f\n",2*PI*r);
    printf("面积=%f\n",r*r*PI);
   }
return 0;

}
