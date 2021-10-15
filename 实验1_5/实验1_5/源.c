#include<stdio.h>
#include<stdlib.h>

typedef struct PNode
{
    int coef;             //ϵ��
    int exp;              //ָ��
    struct PNode* link;
}PNode;
typedef struct
{
    struct PNode* head;
}polynominal;

//����ʽ�Ĵ���
void Create(polynominal* p) 
{
    PNode* pn, * pre, * q;
    p->head = (PNode*)malloc(sizeof(PNode));
    p->head->exp = -1;
    p->head->link = p->head;                            
    for (;;) {
        pn = (PNode*)malloc(sizeof(PNode));
        printf("coef:\n");
        scanf_s("%d", &pn->coef);
        printf("exp:\n");
        scanf_s("%d", &pn->exp);
        if (pn->exp < 0) break;
        pre = p->head;
        q = p->head->link;
        while (q && q->exp > pn->exp) {
            pre = q;
            q = q->link;
        }
        pn->link = q;
        pre->link = pn;
    }
}

//����ʽ���
void Output(polynominal p)
{
    PNode* q;
    int flag = 1;                                   //����,��¼�Ƿ�Ϊ��һ��
    q = p.head->link;
    if (!q) 
    {
        return;
    }
    while (q != p.head) 
    {
        if (!flag && (q->coef > 0)) printf("+");    //�ڷǵ�һ�����ϵ��ǰ���+��
        flag = 0;                                  
        if (q->coef == 0)
        {                           
            return;
        }
        printf("%d", q->coef);                       //��ǰ��ϵ����Ϊ0
        switch (q->exp) 
        {                             //�жϵ�ǰ��ָ��
        case 0:break;                           //��ǰ��ָ��Ϊ0,�˳�
        case 1:printf("X"); break;               //��ǰ��ָ��Ϊ1,���X
        default:printf("X^%d", q->exp); break;    //��ǰ��ָ����Ϊ0,Ҳ��Ϊ1
        }
        q = q->link;
    }
}

//����ʽ�����,�������qx��
void Add(polynominal* px, polynominal* qx)
{
    PNode* q, * q1 = qx->head, * p, * p1, * temp;    //q1ָ�����ʽqx�ı�ͷ���
    p = px->head->link;                       //pָ�����ʽpx�ĵ�һ�����
    p1 = px->head;
    q = q1->link;                             //q1��q��ǰ��
    while (p->exp >= 0) 
    {
        while (p->exp < q->exp) 
        {               //����q->exp�����
            q1 = q;
            q = q->link;
        }
        if (p->exp == q->exp) 
        {                 //��ָ�����ʱ,ϵ�����
            q->coef = q->coef + p->coef;
            if (q->coef == 0)
            {                 //����Ӻ�ϵ��Ϊ0
                q1->link = q->link;           //ɾ��q
                free(q);                      //�ͷ�q�Ŀռ�
                q = q1->link;                 //����qָ��
                p = p->link;
            }
            else
            {                             //����Ӻ�ϵ����Ϊ0
                q1 = q;                       //q1����
                q = q->link;
                p = p->link;                  //pҲ����
            }
        }
        else 
        {                                 //p->exp > q->exp�����
            temp = malloc(sizeof(PNode));     //��p��ϵ����ָ�������½��
            temp->coef = p->coef;
            temp->exp = p->exp;
            temp->link = q1->link;
            q1->link = temp;
            q1 = q1->link;
            p = p->link;
        }
    }
}


//����ʽ�˷�
void Multiply(polynominal* px, polynominal* qx) 
{
    polynominal qx1, qx2;
    PNode* q1, * q2, * q3, * q4, * pre=NULL;
    qx1.head = (PNode*)malloc(sizeof(PNode));       //�����¶���ʽqx1
    qx1.head->exp = -1;
    qx1.head->link = qx1.head;                      //qx1�����ѭ������
    q1 = px->head->link;                            //q1ָ��px�ĵ�һ��
    q2 = qx->head->link;                            //q2ָ��qx�ĵ�һ��
    while (q2->exp != -1)
    {                           //��q2��ָ����Ϊ-1ʱ,px�Ⱥ�qx��ÿһ�����
        q3 = (PNode*)malloc(sizeof(PNode));         //q3�����˵Ľ��
        q3->coef = q1->coef * q2->coef;
        q3->exp = q1->exp + q2->exp;
        if (qx1.head->link->exp == -1) 
        {              //q3���뵽qx1����ʽ��һ����
            q3->link = qx1.head->link;
            qx1.head->link = q3;
            pre = qx1.head->link;
        }
        else
        {                                       //q3���뵽qx1����ʽ���һ����
            q3->link = qx1.head;
            pre->link = q3;
            pre = pre->link;
        }
        q2 = q2->link;
    }
    q1 = q1->link;                                 //q1����һλ
    while (q1->exp != -1) 
    {                          //pxʣ����ÿһ���qxÿһ�����
        q2 = q2->link;
        qx2.head = (PNode*)malloc(sizeof(PNode));  //�����¶���ʽqx2
        qx2.head->exp = -1;
        qx2.head->link = qx2.head;
        while (q2->exp != -1) 
        {
            q4 = (PNode*)malloc(sizeof(PNode));
            q4->coef = q1->coef * q2->coef;
            q4->exp = q1->exp + q2->exp;
            if (qx2.head->link->exp == -1)
            {
                q4->link = qx2.head->link;
                qx2.head->link = q4;
                pre = qx2.head->link;
            }
            else 
            {
                q4->link = qx2.head;
                pre->link = q4;
                pre = pre->link;
            }
            q2 = q2->link;
        }
        Add(&qx2, &qx1);                            //�ϲ�ͬ����
        q1 = q1->link;
    }
    Output(qx1);
}

int main()
{
    polynominal p, q;
    int x;
    printf("Please enter the first poly:\n");
    Create(&p);
    Output(p);
    printf("\n\nPlease enter the second poly:\n");
    Create(&q);
    Output(q);
    printf("\n\nPlease choose the function:\n");
    scanf_s("%d", &x);
    switch (x) 
    {                                   //ѡ��ӷ����ǳ˷�����
    case 0:printf("Add:\n");
        Add(&p, &q);
        Output(q);
        break;
    case 1:printf("Multiply:\n");
        Multiply(&p, &q);
    default:break;
    }
    return 0;
}