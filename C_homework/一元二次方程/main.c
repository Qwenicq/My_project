#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()

{
 float a,b,c,d,x1,x2;
  printf("input a.b,c:");
  scanf("%f %f %f",&a,&b,&c);
  d=b*b-4*a*c;
 x1=(float)(b+sqrt(d))/(-2*a);
 x2=(float)(b-sqrt(d))/(-2*a);
  printf("x1=%f\n,x2=%f\n",x1,x2);
    return 0;
}
