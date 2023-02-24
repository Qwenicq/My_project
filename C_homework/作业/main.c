#include <stdio.h>
#include <stdlib.h>

int main()
{

    int a=2;
    float b=2.3;
    char c='a';
    printf("int=%d B\n",sizeof(int));
    printf("float=%d B\n",sizeof(float));
    printf("char=%d B\n",sizeof(char));
    printf("整数=%d\n",a);
    printf("单精度=%f\n",b);
    printf("字符=%c\n",c);
    return 0;
}
