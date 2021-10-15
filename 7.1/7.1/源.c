#include<stdio.h>
#include<malloc.h>
typedef struct bstnode
{
    int element;
    struct bstnode* lchild, * rchild;
}BSTNode, * BSTree;

BSTree InsertBST(BSTree T, int element)
{
    if (!T)     //���Ϊ�������붯̬�ռ�
    {
        T = malloc(sizeof(BSTNode));
        T->element = element;
        T->lchild = NULL;
        T->rchild = NULL;
    }
    else if (T->element < element)
    {
        T->rchild = InsertBST(T->rchild, element);
    }
    else if (T->element > element)
    {
        T->lchild = InsertBST(T->lchild, element);
    }
    return T;
}

BSTree Deletemax(BSTree T)  //ɾ�����Ԫ��
{
    if (!T)   //TΪ��ֱ�ӷ���
        return NULL;
    if (!T->rchild && T->lchild)   //���ڵ������ֻ��������
    {
        BSTree p = T->lchild;
        free(T);
        return p;
    }
    BSTree p, q;//���ڵ���������Ϊ��
    p = T->rchild;
    q = T;
    while (p->rchild)
    {
        p = p->rchild;
        q = q->rchild;
    }
    if (!p->lchild && !p->rchild)//p��Ҷ���
    {
        q->rchild = NULL;
        free(p);
        return T;
    }
    else if (!p->rchild && p->lchild)//pֻ������
    {
        q->rchild = p->lchild;
        free(p);
        q->rchild->rchild = NULL;
        q->lchild->lchild = NULL;
        return T;
    }
}

BSTree CreateBST(BSTree T)
{
    int element;
    scanf_s("%d", &element);
    while (element != 0)  //��0����
    {
        T = InsertBST(T, element);
        scanf_s("%d", &element);
    }
    return T;
}

void PrintBST(BSTree T)  //���õݹ�����������
{
    if (!T)
        return;
    PrintBST(T->lchild);
    printf("%d ", T->element);
    PrintBST(T->rchild);
}

int main()
{
    BSTree T;
    T = NULL;
    T = CreateBST(T);
    printf("��������������Ϊ��");
    PrintBST(T);
    T = Deletemax(T);
    printf("\nɾ�����Ԫ�غ���������������Ϊ��");
    PrintBST(T);
    return 0;
}