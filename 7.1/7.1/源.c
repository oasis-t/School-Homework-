#include<stdio.h>
#include<malloc.h>
typedef struct bstnode
{
    int element;
    struct bstnode* lchild, * rchild;
}BSTNode, * BSTree;

BSTree InsertBST(BSTree T, int element)
{
    if (!T)     //结点为空则申请动态空间
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

BSTree Deletemax(BSTree T)  //删除最大元素
{
    if (!T)   //T为空直接返回
        return NULL;
    if (!T->rchild && T->lchild)   //根节点存在且只有左子树
    {
        BSTree p = T->lchild;
        free(T);
        return p;
    }
    BSTree p, q;//根节点右子树不为空
    p = T->rchild;
    q = T;
    while (p->rchild)
    {
        p = p->rchild;
        q = q->rchild;
    }
    if (!p->lchild && !p->rchild)//p是叶结点
    {
        q->rchild = NULL;
        free(p);
        return T;
    }
    else if (!p->rchild && p->lchild)//p只有左孩子
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
    while (element != 0)  //以0结束
    {
        T = InsertBST(T, element);
        scanf_s("%d", &element);
    }
    return T;
}

void PrintBST(BSTree T)  //运用递归中序遍历输出
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
    printf("中序遍历输出序列为：");
    PrintBST(T);
    T = Deletemax(T);
    printf("\n删除最大元素后中序遍历输出序列为：");
    PrintBST(T);
    return 0;
}