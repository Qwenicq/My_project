#include<stdio.h>
#include<string.h>
#define N 80
#define max_len 120
int MyComparefuc1(char str1[],char str2[]);
char *MyComparefuc2(char *str1,char *str2);
void SortString(char str[][max_len],int n);
int main(void)
{

    char str[N][max_len];
    char *pstr[N];
    int i,n,j;
    printf("how many string:");
    scanf("%d",&n);
    getchar();
    for(i=0;i<n;i++)
    {
        printf("Input string%d",i+1);
        pstr[i]=str[i];
        gets(str[i]);
    }
    SortString(str,n);
    for(i=0;i<n;i++)
    {
        puts(str[i]);
    }
    for(i=0;i<n-1;i++){
    	for(j=i+1;j<n;j++)
    	{ 
		    printf("The D-valu is:%d\n",MyComparefuc1(str[j],str[i]));
    		printf("The big one is:%s\n",MyComparefuc2(pstr[i],pstr[j]));
		}
	}
    return 0;
}
int MyComparefuc1(char str1[],char str2[])
{
    int i=0;
    while((str1[i]!='\0')&&(str1[i]==str2[i]))
    {
        i++;
    }
    return (str1[i]-str2[i]);
}
char *MyComparefuc2(char *str1,char *str2)
{
    char *pstr1=str1;
    char *pstr2=str2;
    while((*str1='\0')&&(*str1==*str2))
    {
        str1++;
        str2++;
    }
    if((*str1-*str2)>0)
        return pstr1;
    else
        return pstr2;
}
void SortString(char str[][max_len],int n)
{
    int i,j;
    char temp[max_len];
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(MyComparefuc1(str[j],str[i])<0)
            {
                strcpy(temp,str[i]);
                strcpy(str[i],str[j]);
                strcpy(str[j],temp);
            }
          
        }
    }
    
}
