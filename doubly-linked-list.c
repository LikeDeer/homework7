/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */

#define IS_EMPTY(first) (!(first))		// 공백 리스트인지 확인하는 매크로


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int IsInitialized(headNode* h);
int Scanf(int* k);


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	printf("[----- [정준호]    [2020069046] -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			//scanf("%d", &key);
			if (Scanf(&key)) break;			// key에 정수가 아닌 입력값이 들어오면 수행 취소하도록 수정.
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			//scanf("%d", &key);
			if (Scanf(&key)) break;			// key에 정수가 아닌 입력값이 들어오면 수행 취소하도록 수정.
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			//scanf("%d", &key);
			if (Scanf(&key)) break;			// key에 정수가 아닌 입력값이 들어오면 수행 취소하도록 수정.
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			//scanf("%d", &key);
			if (Scanf(&key)) break;			// key에 정수가 아닌 입력값이 들어오면 수행 취소하도록 수정.
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

/*  */
int initialize(headNode** h) {
	if (*h != NULL)
		freeList(*h);

	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;

	return 1;
}


int freeList(headNode* h){
	if (IsInitialized(h))		// initialize 되지 않은 채로 프로그램을 종료하기를 시도하면
		return 1;				// Segmentation fault로 비정상 종료되는 것을 방지.

	listNode* p = h->first;
	listNode* prev = NULL;

	while (p != NULL) {
		prev = p;
		p = p->llink;
		free(prev);
	}

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	listNode* newNode = (listNode*)malloc(sizeof(listNode));
	newNode->key = key;

	if (IS_EMPTY(h->first)) {
		h->first = newNode;
		newNode->llink = newNode;
		newNode->rlink = newNode;

		return 0;
	}

	newNode->llink = h->first;
	newNode->rlink = h->first->llink->rlink;
	h->first->llink = newNode;
	h->first->llink->rlink = newNode;

	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	if (IS_EMPTY(h->first)) {
		printf("Nothing to delete.\n");
		return 1;
	}

	listNode* temp = h->first->llink;

	h->first->llink = temp->llink;
	temp->llink->rlink = h->first;
	free(temp);

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	listNode* newNode = (listNode*)malloc(sizeof(listNode));
	newNode->key = key;

	if (IS_EMPTY(h->first)) {
		h->first = newNode;
		newNode->llink = newNode;
		newNode->rlink = newNode;

		return 0;
	}

	newNode->rlink = h->first;
	newNode->llink = h->first->llink;
	h->first->llink = newNode;
	h->first->llink->rlink = newNode;
	h->first = newNode;

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	if (IS_EMPTY(h->first)) {
		printf("Nothing to delete.\n");
		return 1;
	}

	listNode* temp = h->first;
	temp->rlink->llink = h->first->llink;
	temp->llink->rlink = h->first;
	h->first = temp->rlink;
	free(temp);

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	if (IS_EMPTY(h->first)) {
		
	}

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	if (IS_EMPTY(h->first)) {
		
	}

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	if (IS_EMPTY(h->first)) {
		printf("Nothing to delete.\n");
		return 1;
	}

	return 1;
}


/*-------------- 개인 정의 함수 --------------*/

/* initialize 안하고 insert나 delete의 command를 입력하면 Segmentation fault.
	각 기능을 수행하기 전에 initialized 됐는지 확인하는 전처리용 함수. */
int IsInitialized(headNode* h) {
	if (h == NULL) return 1;
	else return 0;
}

/* main의 scanf("%d", &key)를 대체하는 함수. key에 정수를 입력 받는다 */
 /* 기존에서는 'Your key = '에 정수가 아닌 문자 등 다른 값을 입력하면
 	다음 프로그램 진행에 장애가 생긴다. 정수가 아닌 값을 입력 받으면 insert, delete 등
	수행을 하지 않고 버퍼를 비우도록 하여 문제를 해결하였다. */
int Scanf(int* k) {
	if (scanf("%d", k) == 1) {			// 제대로 정수를 입력 받으면 scanf의 반환값은 1(읽은 항목의 개수)
		while (getchar() != '\n');
		return 0;
	}
	else {
		printf("Not appropriate input. Input must be an integer. Try again.\n");
		while (getchar() != '\n');
		return 1;
	}
}