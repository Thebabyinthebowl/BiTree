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
 void create(BiTree* T)//按照先序遍历创建二叉树 
{
	int a;
	printf("输入结点值\n");
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
		printf("错误（%d）：创建栈结点错误！\n", __LINE__);
		exit(0);
	}
	newNode->next = NULL;
	return newNode;
}

// 初始化栈，并返回头结点
Stack initStack() {
	printf("输入指定结点：");
	int targetNode;
	scanf("%d",&targetNode);
	Stack stack = createStackNode();// 头结点存储目标结点数据
	stack->data = targetNode;
	return stack;
}

// 栈头结点是否存在
int isStackExist(Stack S) {
	if (S == NULL) {
		printf("错误（%d）：栈的头结点未初始化！\n", __LINE__);
		exit(0);
	}
	return TRUE;
}

// 栈是否为空
int isStackEmpty(Stack S) {
	if (isStackExist(S) == FALSE) {
		return STACK_EMPTY;
	}
	if (S->next == NULL) {
		return STACK_EMPTY;
	}
	return STACK_NOT_EMPTY;
}

// 入栈，data是要入栈的结点的数据
char push(Stack S, char data) {
	if (isStackExist(S) == TRUE) {
		Stack node = createStackNode();
		node->data = data;
		node->next = S->next;
		S->next = node;
	}
	return data;
}

// 出栈，返回栈顶结点的数据
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

// 查看栈顶元素
char peek(Stack S) {
	return isStackEmpty(S) == STACK_EMPTY ? STACK_EMPTY : S->next->data;
}

int isFindTargetNode(Stack S) {
	if (isStackEmpty(S) == STACK_NOT_EMPTY && peek(S) == S->data) {
		return FOUND;
	}
	return NOT_FOUND;
}
// 寻找路径
int searchPath(BiTree T, Stack S) {
	if (isFindTargetNode(S) == FOUND) {
		return FOUND;
	}
	if (T == NULL) {// 空树
		return NOT_FOUND;
	}
	push(S, T->data);
	// 查找子树
	if (searchPath(T->LChild, S) == FOUND) {
		return FOUND;
	}
	if (searchPath(T->RChild, S) == FOUND) {
		return FOUND;
	}
	pop(S);
	return NOT_FOUND;
}
// 输出路径，递归
void outputPath(Stack S) {
	if (isStackEmpty(S) == STACK_NOT_EMPTY) {
		outputPath(S->next);
		if (isStackEmpty(S->next) == STACK_NOT_EMPTY) {
			printf(" ");
		}
		printf("%d", S->next->data);
	}
}
// 显示路径
void showPath(Stack S) {
	if (isFindTargetNode(S) == FOUND) {
		printf("路径：");
		outputPath(S);
		printf("\n");
	} else {
		printf("未找到结点'%d'\n", S->data);
	}
}
void showMenu()
{
	printf("1.建立二叉树存储结构\n");
	printf("2.求二叉树的先序遍历序列\n");
	printf("3.求二叉树的中序遍历序列\n");
	printf("4.求二叉树的后序遍历序列\n");
	printf("5.求二叉树的层序遍历序列\n");
	printf("6.求根结点到指定结点的路径\n");
	printf("0.退出\n");
}
 int main()
 {
 	showMenu(); 	
 	BiTree T;
 	create(&T);
 	int select;
 	printf("请选择0-6");
 	scanf("%d",&select);
 	switch(select)
 	{
 		case 0:exit(0);break;
 		case 1:create(&T);break;
		case 2:printf("先序遍历为：\n"); 
		PreOrder(T);break; 
 		case 3:	printf("\n");
		InOrder(T);break;
 		case 4:	printf("\n");
		PostOrder(T);break;
 		case 5:printf("\n");
		layerOrder(T);break;
		case 6:Stack stack = initStack();
		searchPath(T, stack);// 寻找路径
		showPath(stack);break;
	 }
 }
 //124005600700300
