#include <stdio.h>
#include <stdlib.h>



typedef struct node { // 노드 구조체
	int key;
	struct node *left;
	struct node *right;
} Node;

// 스택 선언 및 초기화 그리고 관련 함수
#define MAX_STACK_SIZE 20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop(); // 스택에 데이터를 삽입하는 함수
void push(Node* aNode); // 스택에서 데이터를 삭제하는 함수

// 큐 선언 및 초기화, 그리고 관련 함수
#define MAX_QUEUE_SIZE 20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue(); // 큐에서 데이터를 삭제하는 함수
void enQueue(Node* aNode); // 큐에 데이터를 삽입하는 함수


int initializeBST(Node** h); // 이진탐색트리 초기화 함수

void recursiveInorder(Node* ptr);	  // recursive방식으로 중위 순회
void iterativeInorder(Node* ptr);     // iterative방식으로 중위 순회
void levelOrder(Node* ptr);	          // level order로 순회
int insert(Node* head, int key);      // 이진탐색트리에 노드를 삽입하는 함수
int deleteNode(Node* head, int key);  // 입력값을 가진 노드를 삭제하는 함수
int freeBST(Node* head); // 이진탐색트리에 할당된 메모리를 모두 해제하는 함수

void printStack(); // 스택을 출력하는 함수

int main()
{
	char command;
	int key;
	Node* head = NULL;

	printf("[----- [김지민] [2021041068] -----]\n");

	do{
		

		printf("\n\n"); // 메뉴 출력
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z      Print values in Stack        = p \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		// 기능 선택
		printf("Command = ");
		scanf(" %c", &command);

		switch(command) { // 기능에 따른 동작 수행
		case 'z': case 'Z': // z, Z 기능키 선택 시, BST 초기화
			initializeBST(&head);
			break;
		case 'q': case 'Q': // q, Q 기능키 선택 시, BST에 할당된 메모리 모두 해제
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = "); // i, I 기능키 선택 시, 입력값을 가진 노드 삽입
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D': // d, D 기능키 선택 시, 입력값을 갖는 노드 삭제
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R': // r, R 기능키 선택 시, recursive식으로 중위순회
			recursiveInorder(head->left);
			break;
		case 't': case 'T': // t, T 기능키 선택 시, iterative식으로 중위순회
			iterativeInorder(head->left);
			break;

		case 'l': case 'L': // l, L 기능키 선택 시, levelOrder 순회
			levelOrder(head->left);
			break;

		case 'p': case 'P': // p, P 기능키 선택 시, 스택의 값들을 출력
			printStack();
			break;

		default: // 그 이외의 기능키 선택 시, 안내 메시지 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // q, Q 기능키 선택 시에만 프로그램 종료

	return 1;
}

int initializeBST(Node** h) { // BST 초기화하는 함수

	if(*h != NULL) // 트리가 존재할 경우, 트리에 할당된 메모리 모두 해제 
		freeBST(*h);

	// 헤드노드 생성
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	// root 노드를 포인팅할 부분
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1; // 스택의 Top 인덱스를 가리키는 top 초기화

	front = rear = -1; // 큐의 앞과 끝 인덱스를 가리키는 front와 rear 초기화

	return 1;
}



void recursiveInorder(Node* ptr) // recursive식으로 중위순회
{
	if(ptr) { // 노드가 존재할 경우, traversal
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

void iterativeInorder(Node* node) // iterative식으로 중위순회
{
	while(1){
		for (; node; node = node->left)
		{
			push(node); // 스택에 노드 주소값 Push
		}

		node = pop(); // 스택에서 노드 주소값 Pop

		if (!node)
		{ break; } // 스택에 어떤 노드 주소값도 있지 않을 경우, 순회 중단

		printf("[%d] ", node->key); // 노드의 값을 출력

		node = node->right;
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr) // levelOrder로 순회
{

	if(ptr == NULL){ // 노드가 존재하지 않을 경우, 오류 메시지 출력
		printf("Nothing");
		return;
	}

	enQueue(ptr); // root노드의 주소값 큐에 삽입

	while(1)
	{
		ptr = deQueue(); // 큐에서 노드의 주소값을 가져온다.
		if(ptr!=NULL) // 큐에 값이 존재할 경우
		{
			printf("[%d] ", ptr->key); // 가져온 노드의 값을 출력
			
			if(ptr->left!=NULL) // 가져온 노드의 왼쪽 자식 노드가 존재할 경우, 큐에 자식 노드의 주소값 삽입
			{
				enQueue(ptr->left);
			}

			if(ptr->right!=NULL) // 가져온 노드의 오른쪽 자식 노드가 존재할 경우, 큐에 자식 노드의 주소값 삽입
			{
				enQueue(ptr->right);
			}
		}else break;	
	}
}


int insert(Node* head, int key) // BST에 입력값을 가진 노드를 삽입하는 함수
{
	// 입력값을 갖는 노드 생성
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	// root노드가 존재하지 않을 경우, root노드에 노드 삽입
	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) { // 

		// 입력값과 동일한 값을 가진 노드가 존재할 경우, 함수 종료
		if(ptr->key == key) return 1;

		parentNode = ptr;
		// 입력값에 따라 탐색할 방향 설정
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	// 탐색 결과에 따라 입력값을 가진 노드 삽입
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key) // 입력값과 동일한 값을 가진 노드를 삭제하는 함수
{	
	if (head == NULL) { // 헤드노드가 존재하지 않을 경우, 오류 메시지 출력
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) { // root노드 존재하지 않을 경우, 오류 메시지 출력
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	Node* root = head->left;

	Node* parent = NULL;
	Node* ptr = root;

	// 입력값을 가진 노드를 탐색, 즉 삭제하려는 노드를 탐색
	while((ptr != NULL)&&(ptr->key != key)) {
		if(ptr->key != key) {

			parent = ptr;

			if(ptr->key > key)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}
	}

	// 입력값과 동일한 값을 가진 노드가 존재하지 않을 경우, 메시지 출력
	if(ptr == NULL)
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	// 삭제하려는 노드가 Leaf노드일 경우
	if(ptr->left == NULL && ptr->right == NULL)
	{
		if(parent != NULL) { // root노드가 아닐 경우
			if(parent->left == ptr)
				parent->left = NULL;
			else
				parent->right = NULL;
		} else { // root노드일 경우
			head->left = NULL;

		}

		free(ptr);
		return 1;
	}

	// 삭제하려는 노드가 하나의 자식 노드만 가졌을 경우
	if ((ptr->left == NULL || ptr->right == NULL))
	{
		Node* child;
		if (ptr->left != NULL) // 왼쪽 자식노드가 존재하는 경우
			child = ptr->left;
		else // 오른쪽 자식 노드가 존재하는 경우
			child = ptr->right;

		if(parent != NULL) // root노드가 아닐 경우
		{
			if(parent->left == ptr)
				parent->left = child;
			else
				parent->right = child;
		} else { // root노드일 경우
			root = child;
		}

		free(ptr);
		return 1;
	}

	// 삭제하려는 노드가 2개의 자식 노드를 가진 경우
	Node* candidate;
	parent = ptr;


	candidate = ptr->right;

	while(candidate->left != NULL) // 오른쪽 서브트리에서 최소값을 가진 노드 탐색
	{
		parent = candidate;
		candidate = candidate->left;
	}

	// 최소값을 가진 노드가 오른쪽 자식 노드를 가진 경우
	if (parent->right == candidate)
		parent->right = candidate->right;
	else
		parent->left = candidate->right;

	ptr->key = candidate->key; // 삭제하려는 노드를 삭제하는 대신 오른쪽 서브트리에서 최소값으로 대체

	free(candidate);
	return 1;
}


void freeNode(Node* ptr) // 노드에 할당된 메모리를 해제
{
	if(ptr) { // 
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head) // BST에 할당된 메모리를 모두 해제
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p); // root노드에 할당된 메모리 해제

	free(head); // 헤드노드에 할당된 메모리 해제
	return 1;
}



Node* pop() // Stack에서 데이터를 가져오는(삭제하는) 함수
{
	if(top>-1) // 데이터가 존재한다면, 해당 데이터를 반환
	{
		return stack[top--];
	}else {
		return NULL;
	}
}

void push(Node* aNode) // Stack에 노드의 주소값을 삽입하는 함수
{
	if(top < MAX_STACK_SIZE-1) // Stack에 공간이 있을 경우, 노드의 주소값을 삽입
	{
		stack[++top] = aNode;
	}else {printf("Stack is Full.\n\n");}
}



Node* deQueue() // 큐에서 데이터를 가져오는(삭제하는) 함수
{
	if(front!=rear) // 큐에 데이터가 존재한다면, 노드의 주소값을 반환
	{
		front = (front+1)%MAX_QUEUE_SIZE;
		return queue[front];		
	}
	return NULL;
}

void enQueue(Node* aNode) // 큐에 데이터를 삽입하는 함수
{
	if(front ==  (rear+1) % MAX_QUEUE_SIZE) // 큐가 꽉 찼을 경우, 메시지 출력
	{
		printf("Queue is Full.\n\n");
		return; 
	}
	else // 그렇지 않을 경우, 큐에 노드의 주소값 삽입
	{
		rear = (rear+1) % MAX_QUEUE_SIZE;
		queue[rear] = aNode;
	}
}


void printStack() // 스택을 출력하는 함수
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top) // 0~ top인덱스까지 Stack을 출력
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
		i++;
	}
}
