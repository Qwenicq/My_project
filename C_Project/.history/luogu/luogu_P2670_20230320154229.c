#include<stdio.h>
char a[105][105];
char b[100][100];
int main(){
    int n, m;
    int i, j;
    scanf("%d %d", &n, &m);
    for(i = 1 ; i <= n ; i++){
        for(j = 1 ; j <= m ; j++){
            scanf("%c", &a[i][j]);
        }
        getchar();
    }
    for(i = 1 ; i <= n ; i++){
        for(j = 1 ; j <= m ; j++){
            if(a[i][j] == '*')
               b[i][j] = '*';
            else{
                if(a[i][j-1] == '*')
                   b[i][j]++;
                if(a[i][j+1] == '*')
                   b[i][j]++;
                if(a[i-1][j-1] == '*')
                   b[i][j]++;
                if(a[i-1][j] == '*')
                   b[i][j]++;
                if(a[i-1][j+1] == '*')
                  b[i][j]++;
                if(a[i+1][j-1] == '*')
                  b[i][j]++;
                if(a[i+1][j] == '*')
                   b[i][j]++;
                if(a[i+1][j+1] == '*')
                   b[i][j]++;
        }
      }
    }
    for(i = 1 ; i <= n ; i++){
        for(j = 1 ; j <= m ; j++){
            if(b[i][j] == '*')
              printf("*");
            else
              printf("%d",b[i][j]);
        }
        printf("\n");
    }
}