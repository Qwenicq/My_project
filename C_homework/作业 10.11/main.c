#include <stdio.h>
#define PI 3.14159
int main(void)
{
   float r,h,l,v;
    printf("����뾶=\n");
    printf("�����=\n");
    scanf("%f%f",&r,&h);

   N:if(r<=0||h<=0)//�жϰ뾶�͸߶ȵĺ�����
    {
        printf("����뾶 =");
        printf("�����=");
        scanf("%f %f",&r,&h);
        goto N;                  //����ѭ��
    }else
   {
    v=(PI*r*r*h)/3;         //����Բ׶�����
    printf("���=%.2f\n",v);
       l=sqrt(r*r+(h*h));
    printf("ĸ�߳�=%.2f\n",l*l);
    printf("�����=%.2f\n",(r*r*PI)+(PI*r*l));
   }
return 0;
}
