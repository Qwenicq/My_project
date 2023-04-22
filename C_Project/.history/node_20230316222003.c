#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    int data;
    struct node *next;
}node;

node *startlist(node *phead){   //初始化链表
    phead =  (node*)malloc(sizeof(node));
    phead -> next = NULL;
    return phead;
}

void creatformhead(node *phead){  //头插法建立单链表
    node* p;
    int i = 1;
    int j;
    while(i != 0){
        scanf("%d",&j);
        if(j != -1){
        p = (node*)malloc(sizeof(node));
        p -> data = j;
        p -> next = phead -> next;
        phead -> next = p;
        }
        else{
            i = 0;  //如果输入-1则结束单链表输入
        }
    }
}

void creatformtail(node* hpead){  //尾插法建立链表
    node *p; //建立一个结点指针
    node *r; //建立一个尾指针
    int i = 1;
    int j;
    r = hpead;
    while(i != 0){
        scanf("%d",&j);
        if(j != -1){
            p = (node*)malloc(sizeof(node));
            p -> data = j;
            r -> next = p;
            r = p; //使尾指针放在p后面
        }
        else{
            i = 0;
            r -> next = NULL;
        }
    }
}

node *search(node *phead, int i){ //按序号查找
    node *p;
    int j = 0;
    if(i <= 0)
     return NULL;
    p = phead;//从第一个节点开始扫描
    while(p -> next != NULL && j<i){
        p = p -> next;
        j++;//计数
    }
    if (i == j)
     return p;
    else
     return NULL;
}

node *search2(node *phead, int e){  //按值查找
    node *p;
    p = phead -> next;
    while(p != NULL){
        if(p -> data != e)
         p = p -> next;
        else
         break;//找到则退出循环
    }
    return p;
}

int length(node *phead){
    node *p;
    p = phead -> next;
    int j = 0;
    while(p != NULL){
        p = p -> next;
        j++;
    }
    return j;
}

void enterlist(node *phead, int i, int e){ //单链表插入
    node *p, *s;
    int k = 0;
    if(i <= 0)
     printf("插入位置不合适\n");
    p = phead; 
    while(p != NULL && k < i-1){
        p = p -> next;
        k++;
    }
    if(p =  NULL){
     printf("插入位置不合适\n");
    }
    else{
        s = (node*)malloc(sizeof(node));
        s -> data = e;
        s -> next = p -> next;
        p -> next = s;
        printf("插入成功\n");
    }
}

void dellist(node *phead, int i){//删除节点
    node *p, *r;
    int k = 0; 
    p = phead;
    while(p -> next != NULL && k < i-1){
        p = p -> next;
        k++;
    }
    if(p -> next == NULL){
        printf("删除位置不合法\n");
    }
    r = p -> next;
    p -> next = r -> next;
    printf("删除元素是%d", r -> data);
    free(r);
}

void printlist(node *phead){ //输出链表
    printf("该链表的内容为:");
    while(phead -> next != NULL){
        printf("%d", phead -> next -> data);
        phead = phead -> next;
    }
    printf("\n");
}

int main(void){
    node *phead, *m;
    phead = startlist(phead);
    m = startlist(m);
    printf("链表已初始化\n");
    printf("使用头插法插入链表phead:");
    creatformhead(phead);
    printf("该链表的内容为：");
    printlist(phead);
    printf("通过尾插法插入链表m:");
    creatformtail(m);
    printf("该链表的内容为：");
    printlist(m);
    printf("你想查找的链表是：\n");
    node *p, *s;
    int i;
    scanf("%s",&*p);
    p = (node*)malloc(sizeof(node));
    printf("你想查询的是：\n");
    scanf("%d",&i);
    s = search(p, i);
    printf("该结点的值为：%d\n", s -> data);
    printf("你想插入的链表为：\n");
    node *y;
    int b, c;
    scanf("%s",&y);
    y = (node*)malloc(sizeof(node));
    printf("你想在哪个结点插入多少值：\n");
    scanf("%d %d",&b, &c);
    enterlist(y, b, c);
    printlist(y);
    printf("删除链表m第二个位置的值：\n");
    dellist(m, 2);
    return 0;
}