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

/* ----------- 개인 정의 함수 -----------*/
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

/* 이중 포인터를 써서, 단일 포인터 h@main의 값을 변경한다.
	singly-linked-list 에서는 initialize의 headNode* 형 반환값을 h@main에 대입하는 방식이었다. 
	두 방식 모두 h@main의 값을 변경하는 효과가 있다.*/
int initialize(headNode** h) {
	if (*h != NULL)		// *h = h@main의 값. 헤드 노드를 가리키게 될 것임.
		freeList(*h);

	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;

	return 1;
}


/* (초기화가 되었다면) h@main는 헤드 노드를 가리킬 것이다.
	단일 포인터인 매개변수로 h의 주소를 가져온다면 헤드 노드에 접근할 수 있을 것이다.
	그것으로, h가 가리키는 헤드 노드까지를 free 하는 것이 목적이기 때문에 단일 포인터를 매개변수로 사용했다. */
 /* 이중 포인터로 h를 변경하는 목적은 없다. */
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
	free(h);

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
	/* 전처리 */
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	listNode* newNode = (listNode*)malloc(sizeof(listNode));
	newNode->key = key;

	/* 공백 리스트인 경우 */
	if (IS_EMPTY(h->first)) {
		newNode->rlink = NULL;
		newNode->llink = NULL;
		h->first = newNode;

		return 0;
	}

	/* 공백 리스트가 아니면, */
	listNode* searchLast = h->first;

	/* 마지막 노드까지 탐색. searchLast->rlink == NULL이면 마지막 노드를 의미 */
	while (searchLast->rlink != NULL)
		searchLast = searchLast->rlink;
	
	/* newNode->rlink = NULL로 하면서 마지막 노드로 삽입 */
	newNode->rlink = NULL;
	newNode->llink = searchLast;
	searchLast->rlink = newNode;

	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	/* 전처리 */
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	/* 공백 리스트인 경우 */
	if (IS_EMPTY(h->first)) {
		printf("Nothing to delete.\n");
		return 1;
	}


	listNode* searchLast = h->first;

	while (searchLast->rlink != NULL)		// 마지막 노드까지 탐색
		searchLast = searchLast->rlink;

	searchLast->llink->rlink = NULL;		// 마지막 노드 이전 노드의 rlink를 NULL로 변경하는 것을 잊지 말아야 한다!
	free(searchLast);					// 마지막 노드 제거

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	/* 전처리 */
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	listNode* newNode = (listNode*)malloc(sizeof(listNode));
	newNode->key = key;

	/* 공백 리스트인 경우 */
	 /* newNode의 양쪽 끝을 NULL로 하고 h->first = newNode */
	if (IS_EMPTY(h->first)) {
		newNode->rlink = NULL;
		newNode->llink = NULL;
		h->first = newNode;

		return 0;
	}

	/* 공백 리스트가 아닌 경우 */
	 /* newNode의 h->first와 이전 첫 노드와의 link 관계를 수정
		다만 newNode의 llink = NULL */
	newNode->rlink = h->first;
	newNode->llink = NULL;
	h->first->llink = newNode;
	h->first = newNode;

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	/* 전처리 */
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	/* 공백 리스트인 경우, 제거할 것 없음. */
	if (IS_EMPTY(h->first)) {
		printf("Nothing to delete.\n");
		return 1;
	}


	listNode* temp = h->first;		// temp를 이용해 첫 노드 제거
	h->first = temp->rlink;			//  리스트의 끝을 NULL로 설정하기 위한 것이다.
	temp->rlink->llink = NULL;
	free(temp);

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	/* 전처리 */
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	/* 공백 리스트일 때 */
	if (IS_EMPTY(h->first)) {
		printf("Nothing to invert.\n");
		return 1;
	}

	/* 마지막 노드를 가리킬 때까지 first를 움직이면서 link들을 수정한다. */
	 /* 한 노드의 llink, rlink 값을 교환하면 그 앞, 뒤 노드 순서 관계가 뒤바뀌게 된다. */

	listNode* temp = NULL;				// 교환을 위한 임시 변수(포인터)

	while (h->first->rlink != NULL) {		// 하지만 마지막 노드까지 이 반복문 내에서 작업하면
		temp = h->first->llink;				//  h->first가 끝에서 NULL이 될 수 있다.
		h->first->llink = h->first->rlink;	//  때문에 마지막 노드 그 이전 노드 까지 작업하고
		h->first->rlink = temp;				//  이 반복문 밖에서 마지막 노드까지 수정한다.

		h->first = h->first->llink;
	}

	/* 마지막 노드 작업 */
	temp = h->first->llink;
	h->first->llink = h->first->rlink;
	h->first->rlink = temp;

	//  결과적으로, 수행 후 h->first가 원래의 마지막 노드를 정상적으로 가리키게 할 수 있다.
	
	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
// 삽입이 이뤄지면 return
int insertNode(headNode* h, int key) {
	/* 전처리 */
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	listNode* newNode = (listNode*)malloc(sizeof(listNode));
	newNode->key = key;

	/* 공백 리스트인 경우 */
	 /* 첫 노드로 삽입 */
	if (IS_EMPTY(h->first)) {
		newNode->rlink = NULL;
		newNode->llink = NULL;
		h->first = newNode;
		return 0;
	}
	/* 공백 리스트가 아닌 경우 */
	else {
		/* 첫 노드로 삽입해야 하는 경우 */
		if (key < h->first->key) {
			insertFirst(h, key);
			return 0;
		}

		/* 첫 노드로 삽입해야 하는 경우가 아닐 때, */
		 /* 탐색하다가 searchNode->key > key 이면 그 앞에 삽입
		 	 2개의 노드와 newNode의 link들을 수정한다. */
		listNode* searchNode = h->first->rlink;
		while (searchNode != NULL) {
			if (key < searchNode->key ) {
				newNode->llink = searchNode->llink;
				newNode->rlink = searchNode;
				searchNode->llink->rlink = newNode;
				searchNode->llink = newNode;
				return 0;
			}
			searchNode = searchNode->rlink;
		}

	/* 마지막 노드까지 더 큰 key값이 발견되지 않으면 마지막 노드로 삽입 */
		insertLast(h, key);
		return 0;
	}
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	/* 전처리 */
	if (IsInitialized(h)) {
		printf("Please initialize first and try again.\n");
		return 1;
	}

	/*공백 리스트일 때 */
	if (IS_EMPTY(h->first)) {
		printf("Nothing to delete.\n");
		return 1;
	}
	
	listNode* searchKey = h->first;		// trail이 별도로 필요하던 singly-linked-list와 차별된다.


/*---------------------------------------------------------*/
	/* searchKey는 첫 노드부터 마지막 노드까지 순차적으로 가리키며,
		searchKey->key == key 이면 그 노드를 제거한다.
		결과적으로 리스트의 key값을 가진 모든 노드를 제거한다. */

	/* 기본적인 알고리즘은 다음과 같다.
		1. searchKey가 가리키는 노드가 마지막 노드가 아니면,
			1-1. searchKey->key == key 이면,
				(삭제 알고리즘)
				(삭제할 노드(2), 다음 노드(3), 이전 노드(1))
				1-1-1. (3)->llink가 (1)을 가리키도록 한다.
				1-1-2. searchKey가 (3)을 가리키도록 한다.
				1-1-3. (3)->llink((1))->rlink((2))를 이용해 노드를 삭제한다(free)
				1-1-4. (1)->rlink가 (3)을 가리키도록 한다.
			1-2. searchKey->key != key 이면,
				searchKey는 다음 노드를 가리킨다.
		2. searchKey가 가리키는 노드가 마지막 노드이면,
			그 노드가 searchKey->key == key인지 판별하고
			2-1. 참이면 삭제 후 수행 종료(return)
			2-2. 거짓이면 바로 수행 종료(return) */
	
	/* 하지만 위의 알고리즘을 이용하면 초반에 첫 노드를 가리킬 때는 수행이 달라진다 */
	 /* 정말 특수하게 모든 노드의 key가 입력된 값으로 동일할 수 있다.
	 	이 경우를 포함해서 문제를 해결하는 알고리즘은 다음과 같다.
		 searchKey가 가리키는 노드가 key를 갖고 있으면 제거하고 다음 노드를 가리키는 과정을 반복하다가,
		 searchKey가 마지막 노드까지 제거하고 NULL을 가리키게 되면 수행 종료(return)되도록 한다.
		이러면 첫 노드부터 제거해 나가다가 중간에 key를 갖고있지 않은 노드가 나타나면
		다음 while문으로 넘어간다. */
/*---------------------------------------------------------*/

	// searchKey가 첫 노드를 가리킬 때,
	while ((searchKey) && (searchKey->key == key)) {
		searchKey = searchKey->rlink;
		free(h->first);
		h->first = searchKey;
	}

	
	// 첫 노드가 key를 갖고 있지 않아, 그 이후 노드를 가리킬 때, 
	//	위에 서술한 기본 알고리즘 사용
	while (searchKey) {
		if (searchKey->rlink != NULL) {
			if (searchKey->key == key) {
				searchKey->rlink->llink = searchKey->llink;
				searchKey = searchKey->rlink;
				free(searchKey->llink->rlink);
				searchKey->llink->rlink = searchKey;
			}
			else 
				searchKey = searchKey->rlink;
		}
		else {
			if (searchKey->key == key) {
				searchKey->llink->rlink = NULL;
				free(searchKey);
				return 0;
			}
			else 
				return 0;
		}
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