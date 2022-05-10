/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {//node를 struct로 선언(지정)
	int key; //정수형 변수 key 선언
	struct node *left; //node에 대한 포인터 left 선언
	struct node *right; //node에 대한 포인터 rignt 선언
} Node; //구조체 별칭 Node

int initializeBST(Node** h); //headNode에 메모리를 할당하여 초기화하는 함수 선언 (이중포인터를 매개변수로 함)
//이중포인터를 매개변수로 할 경우 포인터 h의 값을 변경할 수 있음
//싱글포인터를 매개변수로 할 경우 값을 변경할 수 없음.
//해당 코드의 linitialize는 포인터의 값을 변경하기 위해 이중포인터를 매개변수로 받도록 구현함.

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal*/
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command; 
	int key;
	Node* head = NULL; //Node에 대한 포인터 head 선언 후 초기화
	Node* ptr = NULL;	/* temp */ //Node에 대한 포인터 ptr 선언 후 초기화

	do{
		printf("\n\n");
		printf("[----- [Gahyun.Kim] [2020045070] -----]");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) { //command 값에 따른 switch 조건문
		case 'z': case 'Z': //z를 입력받았을 경우 (대소문자 모두 가능)
			initializeBST(&head);  //head의 주소를 매개변수로 하는 initializeBST 함수를 호출하여 메모리 할당 
			break;
		case 'q': case 'Q': //q를 입력받았을 경우 (대소문자 모두 가능)
			freeBST(head); //head에 할당된 메모리를 해제하는 함수 호출
			break;
		case 'n': case 'N': //n를 입력받았을 경우 (대소문자 모두 가능)
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key); //노드를 추가하는 insert 함수를 호출
			break;
		case 'd': case 'D': //d를 입력받았을 경우 (대소문자 모두 가능)
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);//단말 노드를 삭제하는 함수 deleteLeafNode 함수 호출
			break;
		case 'f': case 'F': //f를 입력받았을 경우 (대소문자 모두 가능)
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key); 
			if(ptr != NULL) //만약 값이 NULL이 아니라면 찾은 노드 출력
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key); //NULL이라면 노드 찾기 실패
			break;
		case 's': case 'S'://s를 입력받았을 경우 (대소문자 모두 가능)
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I'://i를 입력받았을 경우 (대소문자 모두 가능)
			inorderTraversal(head->left);
			break;
		case 'p': case 'P'://p를 입력받았을 경우 (대소문자 모두 가능)
			preorderTraversal(head->left);
			break;
		case 't': case 'T'://t를 입력받았을 경우 (대소문자 모두 가능)
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');//q가 입력될때까지 반복

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h); 

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //포인터 h에 Node의 크기만큼의 메모리 할당
	(*h)->left = NULL;	/* root */ //포인터 h의 left 생성후 초기화
	(*h)->right = *h; //포인터 h의 right에 포인터 h 저장
	(*h)->key = -9999; //포인터 h의 key에 -9999로 초기화
	return 1;
}



void inorderTraversal(Node* ptr)//중위순회함수
{
	if(ptr) {
		inorderTraversal(ptr->left); //왼쪽 노드로 재귀
		printf(" [%d] ", ptr->key);//ptr의 key값 출력(root)
		inorderTraversal(ptr->right);//오른쪽노드로재귀

}

void preorderTraversal(Node* ptr)//전위순회
{
	if(ptr) {
		printf(" [%d] ", ptr->key);//root노드출력
		preorderTraversal(ptr->left);//왼쪽노드로재귀
		preorderTraversal(ptr->right);//오른쪽노드로재귀
	}
}

void postorderTraversal(Node* ptr)//후위순회
{
	if(ptr) {
		postorderTraversal(ptr->left);//왼쪽노드로재귀
		postorderTraversal(ptr->right);//오른쪽노드로재귀
		printf(" [%d] ", ptr->key);//root값출력
	}
}


int insert(Node* head, int key)//노드추가
{
	Node* newNode = (Node*)malloc(sizeof(Node));//Node 포인터 newNode에 Node 크기만큼의 메모리할당
	newNode->key = key;//newNode의 key자리에 입력받은 key값 저장
	newNode->left = NULL;//newNode의 left 초기화
	newNode->right = NULL;//newNode의 right 초기화

	if (head->left == NULL) { //head의 left가 NULL일경우
		head->left = newNode;//head의 left에 newNode저장
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;//Node의 포인터 ptr에 head의 left저장 즉 head의 left가 root

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left;


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head;

	while(ptr != NULL) {

		if(ptr->key == key) {
			if(ptr->left == NULL && ptr->right == NULL) {

				/* root node case */
				if(parentNode == head)
					head->left = NULL;

				/* left node case or right case*/
				if(parentNode->left == ptr)
					parentNode->left = NULL;
				else
					parentNode->right = NULL;

				free(ptr);
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;


	}

	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL)
		return NULL;

	if(ptr->key < key)
		ptr = searchRecursive(ptr->right, key);
	else if(ptr->key > key)
		ptr = searchRecursive(ptr->left, key);

	/* if ptr->key == key */
	return ptr;

}
Node* searchIterative(Node* head, int key)
{
	/* root node */
	Node* ptr = head->left;

	while(ptr != NULL)
	{
		if(ptr->key == key)
			return ptr;

		if(ptr->key < key) ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	return NULL;
}

void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}


