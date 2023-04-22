#include<stdio.h>
int main(){
    int player1 = 0, player2 = 0, i = 1, j;
    char a[100];
    scanf("%c",&a[0]);
    while(a[i-1] != 'E'){
        scanf("%c", &a[i]);
        i++;
    }
    for(j = 0; j < i-1; j++){
        if(a[j] == 'W') 
          player1++;
        else if(a[j] == 'L')
          player2++;
        if((player1 >= 11 && player1 > player2 && player1 - player2 >= 2) || (player2 >= 11 && player2 > player1 && player2 - player1 >= 2))
          {
          printf("%d:%d\n",player1,player2);
          player1 = 0;
          player2 = 0;
          }
    }
    printf("%d:%d\n",player1,player2);
    player1 = 0; 
    player2 = 0;
    printf("\n");
    for(j = 0; j < i - 1; j++){
        if(a[j] == 'W')
         player1++;
        else if(a[j] == 'L')
         player2++;
        if((player1 >= 21 && player1 > player2 && player1 - player2 >= 2) || (player2 >= 21 && player2 > player1 && player2 - player1 >= 2))
          {
          printf("%d:%d\n",player1,player2);
          player1 = 0;
          player2 = 0;
          }
    }
    printf("%d:%d\n",player1, player2);
    player1 = 0;
    player2 = 0;
}