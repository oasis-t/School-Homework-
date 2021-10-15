#include<stdio.h>
#include<malloc.h> 
typedef  struct node {
	int data;
	struct node* link;     
}node; 
struct node* L = NULL;
struct node* head = NULL;
struct node* p = NULL;

struct node* L1 = NULL;
struct node* head1 = NULL;
struct node* p1 = NULL;

struct node* L2 = NULL;
struct node* q = NULL;
int main() {
	int i = 0, length;
	printf("请输入链表的长度\n");
	scanf_s("%d", &length);
	head = (struct node*)malloc(sizeof(struct  node));
	L = head;
	printf("请依次输入链表的内容\n");
	for (i; i < length; i++) {
		p = (struct node*)malloc(sizeof(struct  node));
		scanf_s("%d", &p->data);
		p->link = NULL;
		head->link = p;
		head = p;
	}
	int i1 = 0, length1;
	printf("请输入链表的长度\n");
	scanf_s("%d", &length1);

	head1 = (struct node*)malloc(sizeof(struct  node));
	L1 = head1;
	printf("请依次输入链表的内容\n");
	for (i1; i1 < length1; i1++) {
		p1 = (struct node*)malloc(sizeof(struct  node));
		scanf_s("%d", &p1->data);
		p1->link = NULL;
		head1->link = p1;
		head1 = p1;
	}
	p = L->link;
	p1 = L1->link;
	L2 = (struct node*)malloc(sizeof(struct  node));
	L2 = L;
	L2->link = NULL;
	q = (struct node*)malloc(sizeof(struct  node));
	while (p || p1) {
		if (!p) {
			q = p1;
			p1 = p1->link;
		}
		else if (!p1) {
			q = p;
			p = p->link;
		}
		else if (p->data <= p1->data) {
			q = p;
			p = p->link;
		}
		else {
			q = p1;
			p1 = p1->link;
		}
		q->link = L2->link;
		L2->link = q;
	}
	free(L1);
	p = L2->link;
	while (p) {
		printf("%d ", p->data);
		p = p->link;
	}
}
