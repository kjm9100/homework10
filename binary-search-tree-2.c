#include <stdio.h>
#include <stdlib.h>



typedef struct node { // ��� ����ü
	int key;
	struct node *left;
	struct node *right;
} Node;

// ���� ���� �� �ʱ�ȭ �׸��� ���� �Լ�
#define MAX_STACK_SIZE 20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop(); // ���ÿ� �����͸� �����ϴ� �Լ�
void push(Node* aNode); // ���ÿ��� �����͸� �����ϴ� �Լ�

// ť ���� �� �ʱ�ȭ, �׸��� ���� �Լ�
#define MAX_QUEUE_SIZE 20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue(); // ť���� �����͸� �����ϴ� �Լ�
void enQueue(Node* aNode); // ť�� �����͸� �����ϴ� �Լ�


int initializeBST(Node** h); // ����Ž��Ʈ�� �ʱ�ȭ �Լ�

void recursiveInorder(Node* ptr);	  // recursive������� ���� ��ȸ
void iterativeInorder(Node* ptr);     // iterative������� ���� ��ȸ
void levelOrder(Node* ptr);	          // level order�� ��ȸ
int insert(Node* head, int key);      // ����Ž��Ʈ���� ��带 �����ϴ� �Լ�
int deleteNode(Node* head, int key);  // �Է°��� ���� ��带 �����ϴ� �Լ�
int freeBST(Node* head); // ����Ž��Ʈ���� �Ҵ�� �޸𸮸� ��� �����ϴ� �Լ�

void printStack(); // ������ ����ϴ� �Լ�

int main()
{
	char command;
	int key;
	Node* head = NULL;

	printf("[----- [������] [2021041068] -----]\n");

	do{
		

		printf("\n\n"); // �޴� ���
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z      Print values in Stack        = p \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		// ��� ����
		printf("Command = ");
		scanf(" %c", &command);

		switch(command) { // ��ɿ� ���� ���� ����
		case 'z': case 'Z': // z, Z ���Ű ���� ��, BST �ʱ�ȭ
			initializeBST(&head);
			break;
		case 'q': case 'Q': // q, Q ���Ű ���� ��, BST�� �Ҵ�� �޸� ��� ����
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = "); // i, I ���Ű ���� ��, �Է°��� ���� ��� ����
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D': // d, D ���Ű ���� ��, �Է°��� ���� ��� ����
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R': // r, R ���Ű ���� ��, recursive������ ������ȸ
			recursiveInorder(head->left);
			break;
		case 't': case 'T': // t, T ���Ű ���� ��, iterative������ ������ȸ
			iterativeInorder(head->left);
			break;

		case 'l': case 'L': // l, L ���Ű ���� ��, levelOrder ��ȸ
			levelOrder(head->left);
			break;

		case 'p': case 'P': // p, P ���Ű ���� ��, ������ ������ ���
			printStack();
			break;

		default: // �� �̿��� ���Ű ���� ��, �ȳ� �޽��� ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // q, Q ���Ű ���� �ÿ��� ���α׷� ����

	return 1;
}

int initializeBST(Node** h) { // BST �ʱ�ȭ�ϴ� �Լ�

	if(*h != NULL) // Ʈ���� ������ ���, Ʈ���� �Ҵ�� �޸� ��� ���� 
		freeBST(*h);

	// ����� ����
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	// root ��带 �������� �κ�
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1; // ������ Top �ε����� ����Ű�� top �ʱ�ȭ

	front = rear = -1; // ť�� �հ� �� �ε����� ����Ű�� front�� rear �ʱ�ȭ

	return 1;
}



void recursiveInorder(Node* ptr) // recursive������ ������ȸ
{
	if(ptr) { // ��尡 ������ ���, traversal
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

void iterativeInorder(Node* node) // iterative������ ������ȸ
{
	while(1){
		for (; node; node = node->left)
		{
			push(node); // ���ÿ� ��� �ּҰ� Push
		}

		node = pop(); // ���ÿ��� ��� �ּҰ� Pop

		if (!node)
		{ break; } // ���ÿ� � ��� �ּҰ��� ���� ���� ���, ��ȸ �ߴ�

		printf("[%d] ", node->key); // ����� ���� ���

		node = node->right;
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr) // levelOrder�� ��ȸ
{

	if(ptr == NULL){ // ��尡 �������� ���� ���, ���� �޽��� ���
		printf("Nothing");
		return;
	}

	enQueue(ptr); // root����� �ּҰ� ť�� ����

	while(1)
	{
		ptr = deQueue(); // ť���� ����� �ּҰ��� �����´�.
		if(ptr!=NULL) // ť�� ���� ������ ���
		{
			printf("[%d] ", ptr->key); // ������ ����� ���� ���
			
			if(ptr->left!=NULL) // ������ ����� ���� �ڽ� ��尡 ������ ���, ť�� �ڽ� ����� �ּҰ� ����
			{
				enQueue(ptr->left);
			}

			if(ptr->right!=NULL) // ������ ����� ������ �ڽ� ��尡 ������ ���, ť�� �ڽ� ����� �ּҰ� ����
			{
				enQueue(ptr->right);
			}
		}else break;	
	}
}


int insert(Node* head, int key) // BST�� �Է°��� ���� ��带 �����ϴ� �Լ�
{
	// �Է°��� ���� ��� ����
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	// root��尡 �������� ���� ���, root��忡 ��� ����
	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) { // 

		// �Է°��� ������ ���� ���� ��尡 ������ ���, �Լ� ����
		if(ptr->key == key) return 1;

		parentNode = ptr;
		// �Է°��� ���� Ž���� ���� ����
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	// Ž�� ����� ���� �Է°��� ���� ��� ����
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key) // �Է°��� ������ ���� ���� ��带 �����ϴ� �Լ�
{	
	if (head == NULL) { // ����尡 �������� ���� ���, ���� �޽��� ���
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) { // root��� �������� ���� ���, ���� �޽��� ���
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	Node* root = head->left;

	Node* parent = NULL;
	Node* ptr = root;

	// �Է°��� ���� ��带 Ž��, �� �����Ϸ��� ��带 Ž��
	while((ptr != NULL)&&(ptr->key != key)) {
		if(ptr->key != key) {

			parent = ptr;

			if(ptr->key > key)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}
	}

	// �Է°��� ������ ���� ���� ��尡 �������� ���� ���, �޽��� ���
	if(ptr == NULL)
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	// �����Ϸ��� ��尡 Leaf����� ���
	if(ptr->left == NULL && ptr->right == NULL)
	{
		if(parent != NULL) { // root��尡 �ƴ� ���
			if(parent->left == ptr)
				parent->left = NULL;
			else
				parent->right = NULL;
		} else { // root����� ���
			head->left = NULL;

		}

		free(ptr);
		return 1;
	}

	// �����Ϸ��� ��尡 �ϳ��� �ڽ� ��常 ������ ���
	if ((ptr->left == NULL || ptr->right == NULL))
	{
		Node* child;
		if (ptr->left != NULL) // ���� �ڽĳ�尡 �����ϴ� ���
			child = ptr->left;
		else // ������ �ڽ� ��尡 �����ϴ� ���
			child = ptr->right;

		if(parent != NULL) // root��尡 �ƴ� ���
		{
			if(parent->left == ptr)
				parent->left = child;
			else
				parent->right = child;
		} else { // root����� ���
			root = child;
		}

		free(ptr);
		return 1;
	}

	// �����Ϸ��� ��尡 2���� �ڽ� ��带 ���� ���
	Node* candidate;
	parent = ptr;


	candidate = ptr->right;

	while(candidate->left != NULL) // ������ ����Ʈ������ �ּҰ��� ���� ��� Ž��
	{
		parent = candidate;
		candidate = candidate->left;
	}

	// �ּҰ��� ���� ��尡 ������ �ڽ� ��带 ���� ���
	if (parent->right == candidate)
		parent->right = candidate->right;
	else
		parent->left = candidate->right;

	ptr->key = candidate->key; // �����Ϸ��� ��带 �����ϴ� ��� ������ ����Ʈ������ �ּҰ����� ��ü

	free(candidate);
	return 1;
}


void freeNode(Node* ptr) // ��忡 �Ҵ�� �޸𸮸� ����
{
	if(ptr) { // 
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head) // BST�� �Ҵ�� �޸𸮸� ��� ����
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p); // root��忡 �Ҵ�� �޸� ����

	free(head); // ����忡 �Ҵ�� �޸� ����
	return 1;
}



Node* pop() // Stack���� �����͸� ��������(�����ϴ�) �Լ�
{
	if(top>-1) // �����Ͱ� �����Ѵٸ�, �ش� �����͸� ��ȯ
	{
		return stack[top--];
	}else {
		return NULL;
	}
}

void push(Node* aNode) // Stack�� ����� �ּҰ��� �����ϴ� �Լ�
{
	if(top < MAX_STACK_SIZE-1) // Stack�� ������ ���� ���, ����� �ּҰ��� ����
	{
		stack[++top] = aNode;
	}else {printf("Stack is Full.\n\n");}
}



Node* deQueue() // ť���� �����͸� ��������(�����ϴ�) �Լ�
{
	if(front!=rear) // ť�� �����Ͱ� �����Ѵٸ�, ����� �ּҰ��� ��ȯ
	{
		front = (front+1)%MAX_QUEUE_SIZE;
		return queue[front];		
	}
	return NULL;
}

void enQueue(Node* aNode) // ť�� �����͸� �����ϴ� �Լ�
{
	if(front ==  (rear+1) % MAX_QUEUE_SIZE) // ť�� �� á�� ���, �޽��� ���
	{
		printf("Queue is Full.\n\n");
		return; 
	}
	else // �׷��� ���� ���, ť�� ����� �ּҰ� ����
	{
		rear = (rear+1) % MAX_QUEUE_SIZE;
		queue[rear] = aNode;
	}
}


void printStack() // ������ ����ϴ� �Լ�
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top) // 0~ top�ε������� Stack�� ���
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
		i++;
	}
}
