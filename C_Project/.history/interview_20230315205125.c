/*
 * @Author: Xu Qiaoan 
 * @Date: 2023-03-15 20:49:00 
 * @Last Modified by: Xu Qiaoan
 * @Last Modified time: 2023-03-15 20:51:25
 */
#include<stdio.h>
int main(){
    int x[5] = {4, 4, 2, 3, 6};
    int *p = (int*)(&x+1);
    printf("%d,%d",*(x+1),*(p-1));
    }