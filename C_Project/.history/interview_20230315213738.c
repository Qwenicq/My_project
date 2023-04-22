/*
 * @Author: Xu Qiaoan 
 * @Date: 2023-03-15 20:49:00 
 * @Last Modified by: Xu Qiaoan
 * @Last Modified time: 2023-03-15 21:37:37
 */
#include<stdio.h>
#include<stdlib.h>
typedef union a{
    double number;
    char string[13];
}b;
typedef struct c{
    b d;
    int e;
    double f;
    char h;
}g;
int main(){
   int nums[] = {1, 5, 7};
   int cnt = 0;
   switch(0){
    case 0:
     cnt = printf("%d\n",sizeof(b));
    case 1:
     printf("%d\n",cnt+=sizeof(g));
    case 2:
     cnt+=1[nums];
     break;
    case 3:
     cnt--;
    case 4:
     cnt ^=2;
   } 
   printf("%d",cnt);
    }