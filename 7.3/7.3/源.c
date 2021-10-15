#include<stdio.h>
#include<stdlib.h>
typedef struct bstnode
{
	int element; //结点中元素值
	int bf;// 平衡因子balance factor
	struct bstnode* lchild, * rchild;
}BSTNode,*BSTree;
typedef enum { false, true } bool;
//右旋
void RightRotate(BSTree* p)
{
    BSTree lc = (*p)->lchild;
    (*p)->lchild = lc->rchild;
    lc->rchild = *p;
    *p = lc;
}
//左旋
void LeftRotate(BSTree* p)
{
    BSTree rc = (*p)->rchild;
    (*p)->rchild = rc->lchild;
    rc->lchild = *p;
    *p = rc;
}

void LeftBalance(BSTree* T)
{
    BSTree lc, rd;
    lc = (*T)->lchild;//查看以根结点左孩子作为根结点的子树
    switch (lc->bf)
    {
    case 1://LL情形
        (*T)->bf = lc->bf = 0;
        RightRotate(T);
        break;
    case -1://LR情形
        rd = lc->rchild;
        switch (rd->bf)
        {
        case 1:
            (*T)->bf = -1;
            lc->bf = 0;
            break;
        case 0:
            (*T)->bf = lc->bf = 0;
            break;
        case -1:
            (*T)->bf = 0;
            lc->bf = 1;
            break;
        }
        rd->bf = 0;
        LeftRotate(&(*T)->lchild);
        RightRotate(T);
        break;
    }
}

void RightBalance(BSTree* T)
{
    BSTree lc, rd;
    lc = (*T)->rchild;
    switch (lc->bf)
    {
    case -1:
        (*T)->bf = lc->bf = 0;
        LeftRotate(T);
        break;
    case 1:
        rd = lc->lchild;
        switch (rd->bf)
        {
        case 1:
            (*T)->bf = 0;
            lc->bf = -1;
            break;
        case 0:
            (*T)->bf = lc->bf = 0;
            break;
        case -1:
            (*T)->bf = 0;
            lc->bf = 1;
            break;
        }
        rd->bf = 0;
        RightRotate(&(*T)->rchild);
        LeftRotate(T);
        break;
    }
}

int InsertAVL(BSTree* T, int e, bool* taller)
{
    if ((*T) == NULL)//为空直接添加结点
    {
        (*T) = (BSTree)malloc(sizeof(BSTNode));
        (*T)->bf = 0;
        (*T)->element = e;
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;
        *taller = true;
    }
    else if (e == (*T)->element)
    {
        *taller = false;
        return 0;
    }
    else if (e < (*T)->element)
    {
        //如果插入过程，不会影响树本身的平衡，则直接结束
        if (!InsertAVL(&(*T)->lchild, e, taller))
            return 0;
        //判断插入过程是否会导致整棵树的深度 +1
        if (*taller)
        {
            //判断根结点 T 的平衡因子是多少
            switch ((*T)->bf)
            {
            case 1:
                LeftBalance(T);
                *taller = false;
                break;
            case  0:
                (*T)->bf = 1;
                *taller = true;
                break;
            case -1:
                (*T)->bf = 0;
                *taller = false;
                break;
            }
        }
    }
    else
    {
        if (!InsertAVL(&(*T)->rchild, e, taller))
            return 0;
        if (*taller)
        {
            switch ((*T)->bf)
            {
            case 1:
                (*T)->bf = 0;
                *taller = false;
                break;
            case 0:
                (*T)->bf = -1;
                *taller = true;
                break;
            case  -1:
                RightBalance(T);
                *taller = false;
                break;
            }
        }
    }
    return 1;
}
void Print(BSTree T)//中序遍历输出平衡因子
{
    if (T->lchild)
        Print(T->lchild);
    printf("%d ", T->bf);
    if (T->rchild)
        Print(T->rchild);
}
int main()
{
    int i, a[] = { 5,2,4,8,6,7};
    BSTree T = NULL;
    bool taller;
    for (i = 0; i < 6; i++)
    {
        InsertAVL(&T, a[i], &taller);
    }
    Print(T);
    return 0;
}