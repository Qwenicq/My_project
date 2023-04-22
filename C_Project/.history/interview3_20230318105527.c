#include<stdio.h>
#include<stdlib.h>
int main() {
char c1[] = "nice";
char c2[] = "to";
char c3[] = "meet";
char c4[] = "you";
char c5[] = "at";
char c6[] = "3g";
char* str[2][3] = { {c1,c2,c3},{c4,c5,c6} };
char** p = (char**)malloc(sizeof(char*));
p = *(str+1);
printf("%s\n", *p);
printf("%s\n", *(p + 1));
printf("%s\n", *(p)+1);
return 0;
}