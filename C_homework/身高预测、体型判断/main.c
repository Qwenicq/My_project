#include <stdio.h>
int main()
{
  float moHight,faHight,h;
  char sex,diet,sport;
  printf("����������Ա���ΪM/ŮΪF)");
  scanf("%c",&sex);
  printf("�������㸸�׵����=");
  scanf("%f",&faHight);
  printf("��������ĸ�׵����=");
  scanf("%f",&moHight);
  printf("��ϲ�������˶���(Y/N)");
  scanf(" %c",&sport);
  printf("���кõ���ʳϰ����Y/N)");
  scanf(" %c",&diet);
  if(sex=='M'||sex=='m')
      h=(moHight+faHight)*0.54;
else
    h=(faHight*0.923+moHight)/2;

if(sport=='y'||sport=='Y')
    h=h*(1+0.02);
if(diet=='y'||diet=='Y')
    h=h*(1+0.015);
printf("���Ԥ�����Ϊ%.2f cm",h);


    return 0;
}

