#include<stdio.h>
#include<malloc.h>
typedef struct Node_n
{
    char data;
    struct Node_n* link;
}Node, * Node_node;
Node_node Init(Node* L)
{
    Node* p, * q;
    char x;
    L = (Node*)malloc(sizeof(Node));
    L->link = NULL;
    q = L;
    x = getchar();
    while (x != '\n')
    {
        p = (Node*)malloc(sizeof(Node));
        p->data = x;
        q->link = p;
        q = p;
        x = getchar();
    }
    q->link = NULL;
    return L;
}
void Output(Node* L)
{
    Node* p = L->link;
    while (p != NULL)
    {
        printf("%c", p->data);
        p = p->link;
    }
    printf("\n");
}
Node_node Inverse(Node* L)
{
    Node* p = L->link, * q = L->link;
    q = q->link;
    p->link = NULL;
    p = q;
    while (p != NULL)
    {
        q = q->link;
        p->link = L->link;
        L->link = p;
        p = q;
    }
    return L;
}
void Destroy(Node* L)
{
    Node* p = L, * q = p->link;
    while (q != NULL)
    {
        free(p);
        p = q;
        q = p->link;
    }
    printf("\n");
}
int main()
{
    Node* p = NULL;
    printf("请输入链表中的元素:\n");
    p = Init(p);
    printf("逆置前：\n");
    Output(p);
    p = Inverse(p);
    printf("逆置后：\n");
    Output(p);
    Destroy(p);
    return 0;
}

