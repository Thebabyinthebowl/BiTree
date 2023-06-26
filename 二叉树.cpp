	#include "stdio.h"
#include "stdlib.h"
#define _CRT_SECURE_NO_WARNINGS
#define TRUE 1
#define FALSE 0
#define STACK_EMPTY TRUE
#define STACK_NOT_EMPTY FALSE
#define FOUND TRUE
#define NOT_FOUND FALSE
typedef struct Node
{
	int data;
	struct Node* LChild;
	struct Node *RChild;
 } BiNode,*BiTree;
 typedef struct StackNode {
	int data;
	struct StackNode* next;
}StackNode, * Stack;
 void create(BiTree* T)//��������������������� 
{
	int a;
	printf("������ֵ\n");
	scanf("%d", &a);
	if (a == 0)
		(*T) = NULL;
	else
	{
		(*T) = (BiTree)malloc(sizeof(BiNode));
		(*T)->data = a;
		create(&(*T)->LChild);
		create(&(*T)->RChild);
	}
}
void PreOrder(BiTree T)
{
	if (T)
	{
		printf("%d", T->data);
		PreOrder(T->LChild);
		PreOrder(T->RChild);
	}
}
void InOrder(BiTree T)
{
	if (T)
	{
		InOrder(T->LChild);
		printf("%d", T->data);
		InOrder(T->RChild);
	}
 }
 void PostOrder(BiTree T)
{
	if (T)
	{
		PostOrder(T->LChild);
		PostOrder(T->RChild);
		printf("%d", T->data);
	}
}
void layerOrder(BiTree T)
 {
   BiTree queue[20],pTemp;
   int cur = 0,pre = 0;
   queue[cur++] = T;
   while(cur!=pre)
   {
   	pTemp = queue[pre++];
   	printf("%d",pTemp->data);
   	if(pTemp->LChild!=NULL)
   	queue[cur++] = pTemp->LChild;
   	if(pTemp->RChild!=NULL)
   	queue[cur++] = pTemp->RChild;
   }
 }
 Stack createStackNode() {
	Stack newNode = (Stack)malloc(sizeof(StackNode));
	if (newNode == NULL) {
		printf("����%d��������ջ������\n", __LINE__);
		exit(0);
	}
	newNode->next = NULL;
	return newNode;
}

// ��ʼ��ջ��������ͷ���
Stack initStack() {
	printf("����ָ����㣺");
	int targetNode;
	scanf("%d",&targetNode);
	Stack stack = createStackNode();// ͷ���洢Ŀ��������
	stack->data = targetNode;
	return stack;
}

// ջͷ����Ƿ����
int isStackExist(Stack S) {
	if (S == NULL) {
		printf("����%d����ջ��ͷ���δ��ʼ����\n", __LINE__);
		exit(0);
	}
	return TRUE;
}

// ջ�Ƿ�Ϊ��
int isStackEmpty(Stack S) {
	if (isStackExist(S) == FALSE) {
		return STACK_EMPTY;
	}
	if (S->next == NULL) {
		return STACK_EMPTY;
	}
	return STACK_NOT_EMPTY;
}

// ��ջ��data��Ҫ��ջ�Ľ�������
char push(Stack S, char data) {
	if (isStackExist(S) == TRUE) {
		Stack node = createStackNode();
		node->data = data;
		node->next = S->next;
		S->next = node;
	}
	return data;
}

// ��ջ������ջ����������
char pop(Stack S) {
	char ret = STACK_EMPTY;
	if (isStackEmpty(S) == STACK_NOT_EMPTY) {
		Stack d = S->next;
		S->next = d->next;
		ret = d->data;
		free(d);
	}
	return ret;
}

// �鿴ջ��Ԫ��
char peek(Stack S) {
	return isStackEmpty(S) == STACK_EMPTY ? STACK_EMPTY : S->next->data;
}

int isFindTargetNode(Stack S) {
	if (isStackEmpty(S) == STACK_NOT_EMPTY && peek(S) == S->data) {
		return FOUND;
	}
	return NOT_FOUND;
}
// Ѱ��·��
int searchPath(BiTree T, Stack S) {
	if (isFindTargetNode(S) == FOUND) {
		return FOUND;
	}
	if (T == NULL) {// ����
		return NOT_FOUND;
	}
	push(S, T->data);
	// ��������
	if (searchPath(T->LChild, S) == FOUND) {
		return FOUND;
	}
	if (searchPath(T->RChild, S) == FOUND) {
		return FOUND;
	}
	pop(S);
	return NOT_FOUND;
}
// ���·�����ݹ�
void outputPath(Stack S) {
	if (isStackEmpty(S) == STACK_NOT_EMPTY) {
		outputPath(S->next);
		if (isStackEmpty(S->next) == STACK_NOT_EMPTY) {
			printf(" ");
		}
		printf("%d", S->next->data);
	}
}
// ��ʾ·��
void showPath(Stack S) {
	if (isFindTargetNode(S) == FOUND) {
		printf("·����");
		outputPath(S);
		printf("\n");
	} else {
		printf("δ�ҵ����'%d'\n", S->data);
	}
}
void showMenu()
{
	printf("1.�����������洢�ṹ\n");
	printf("2.��������������������\n");
	printf("3.��������������������\n");
	printf("4.��������ĺ����������\n");
	printf("5.��������Ĳ����������\n");
	printf("6.�����㵽ָ������·��\n");
	printf("0.�˳�\n");
}
 int main()
 {
 	showMenu(); 	
 	BiTree T;
 	create(&T);
 	int select;
 	printf("��ѡ��0-6");
 	scanf("%d",&select);
 	switch(select)
 	{
 		case 0:exit(0);break;
 		case 1:create(&T);break;
		case 2:printf("�������Ϊ��\n"); 
		PreOrder(T);break; 
 		case 3:	printf("\n");
		InOrder(T);break;
 		case 4:	printf("\n");
		PostOrder(T);break;
 		case 5:printf("\n");
		layerOrder(T);break;
		case 6:Stack stack = initStack();
		searchPath(T, stack);// Ѱ��·��
		showPath(stack);break;
	 }
 }
 //124005600700300
