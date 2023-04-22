#include <stdio.h>
#include <stdlib.h>

typedef int DataType;
struct Node
{
    DataType data;
    struct Node *next;
};
typedef struct Node *LinkList;
typedef struct Node *PNode;

LinkList SetNullList_Link()
{
    LinkList head = (LinkList)malloc(sizeof(struct Node));
    if (head != NULL)
        head->next = NULL;
    else
        printf("alloc failure");
    return head;
}
LinkList CreateList(LinkList head)
{
    PNode p = NULL;
    int data, i = 1;
    while (i != 0)
    {
        scanf("%d", &data);
        if (data != -1)
        {
            p = (struct Node *)malloc(sizeof(struct Node));
            p->data = data;
            p->next = head->next;
            head->next = p;
        }
        else
        {
            i = 0;
        }
    }
    return head;
}
LinkList Findmax(LinkList head, PNode q)
{
    PNode p = head->next;
    int max = p->data;
    q = head->next;
    p = p->next;
    while (p->next != NULL)
    {
        if (p->data > max)
        {
            max = p->data;
            q = p;
            p = p->next;
        }
    }
    return q;
}
LinkList Delete(LinkList head, PNode q)
{
    PNode pre = head;
    PNode p = head;
    while (pre->next != NULL)
    {
        if (pre->next == q)
        {
            p = pre->next;
            pre->next = q->next;
            free(p);
            break;
        }
        pre = pre->next;
    }
    return head;
}

void Print(LinkList head)
{
    PNode p = head->next;
    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
}

int main()
{
    LinkList head = NULL;
    PNode q;
    head = SetNullList_Link();
    CreateList(head);
    Findmax(head, q);
    Delete(head, q);
    Print(head);

    return 0;
}