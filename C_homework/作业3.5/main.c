#include <stdio.h>
int main(viod)
{
    const double PI=3.14159;
    double r;
     printf("����뾶=");
    scanf("%lf",&r);
   N:if(r<=0)
    {
        printf("����뾶");
        scanf("%lf",&r);
        goto N;
    }else
   {


    printf("�ܳ�=%f\n",2*PI*r);
    printf("���=%f\n",r*r*PI);
   }
return 0;

}
