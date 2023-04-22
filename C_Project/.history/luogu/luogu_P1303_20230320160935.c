#include<stdio.h>
#include<string.h>
int a[2001];
int b[2001];
char a1[2001];
char b1[2001];
int c[4002];
int main(){
    scanf("%s\n%s", &a1, &b1);
    int i = 0;
    int la = strlen(a1);
    int lb = strlen(b1);
    for(i = 0; i < la; i++)
      a[la - 1 - i] = a1[i] - 48;
    for(i = 0; i < lb; i++)
      b[lb - 1 - i] = b1[i] - 48;
    int m = la + lb;
    for(int i = 0; i < la; i++){
        for(int j = 0; j< lb; j++){
            c[i+j] = a[i] * b[j];
        }
    }
    for(int i = 0; i < m; i++){
        c[i+1] += c[i] / 10;
        c[i] %= 10;
    }
    while(c[m] == 0 && m >=1)m--;
    for(i = m; i>= 0; i--)
     printf("%d",c[i]);
}