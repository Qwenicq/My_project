#include <stdio.h>
int main()
{
  float moHight,faHight,h;
  char sex,diet,sport;
  printf("请输入你的性别（男为M/女为F)");
  scanf("%c",&sex);
  printf("请输入你父亲的身高=");
  scanf("%f",&faHight);
  printf("请输入你母亲的身高=");
  scanf("%f",&moHight);
  printf("你喜欢体育运动吗(Y/N)");
  scanf(" %c",&sport);
  printf("你有好的饮食习惯吗（Y/N)");
  scanf(" %c",&diet);
  if(sex=='M'||sex=='m')
      h=(moHight+faHight)*0.54;
else
    h=(faHight*0.923+moHight)/2;

if(sport=='y'||sport=='Y')
    h=h*(1+0.02);
if(diet=='y'||diet=='Y')
    h=h*(1+0.015);
printf("你的预测身高为%.2f cm",h);


    return 0;
}

