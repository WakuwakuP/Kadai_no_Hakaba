#include <stdio.h>
#include <stdlib.h>

/* Member定義 */
typedef struct {
	int no;
	char name[20];
} Member;

/* Node定義 */
typedef struct node {
	Member data;
	struct node *next;
} Node;

/* List定義 */
typedef struct {
	Node *head;
	Node *crnt;
} List;

/* 出力関数 */
void PrintList(const List *list){
	Node *ptr = list->head;
	if (NULL == ptr) {
		printf("No Data.\n");
	} else {
		puts("  Data");
		puts("|---|--------------------|");
		puts("| No|        Name        |");
		puts("|---|--------------------|");
		while (ptr != NULL) {
			printf("|%3d|%20s|\n", ptr->data.no, ptr->data.name);
			ptr = ptr->next;
		}
		puts("|---|--------------------|");
	}
}

/* Node領域確保 */
Node *AllocNode(void){
	return calloc(1, sizeof(Node));
}

/* 先頭挿入関数 */
void InsertFront (List *list, const Member *x) {
	Node *ptr = list->head;
	list->crnt = AllocNode();
	list->head = list->crnt;
	list->crnt->data = *x;
	list->crnt->next = ptr;
	list->crnt =NULL;
}

/* 位置任意挿入関数 */
void InsertAfter(List *list, Node *p, const Member *x){
	list->crnt = AllocNode();
	list->crnt->data = *x;
	list->crnt->next = p->next;
	p->next = list->crnt;
	list->crnt = NULL;
}

int main() {
	List list;
	char text[10];
 /* 初期化 */
	list.head = NULL;
	list.crnt = NULL;

	for(;;){
		printf("何をしますか。(データの表示 : print / データの追加 : add / 終了 : exit)\n:");
		scanf("%s", text);
		if ('p' == text[0]) {
			PrintList(&list);
		} else if ('a' == text[0]) {
			int n, i;
			Member addMember;
			Node *ptr = list.head;
			if (NULL == ptr){				// リストが空の場合
				printf("no   : "); scanf("%d", &addMember.no);
				printf("name : "); scanf("%s", addMember.name);
				InsertFront(&list, &addMember);
			} else {
				printf("何個目の次に挿入しますか\n: "); scanf("%d", &n);
				if (0 == n) {					// 先頭の場合
					printf("No   : "); scanf("%d", &addMember.no);
					printf("name : "); scanf("%s", addMember.name);
					InsertFront(&list, &addMember);
				} else {
					for(i = 1; i < n; i++){
						if (NULL == ptr->next) {
							printf("指定値が大きすぎです。\n最後に追加します。\n");
							break;
						}
						ptr = ptr->next;
					}
					printf("No   : "); scanf("%d", &addMember.no);
					printf("name : "); scanf("%s", addMember.name);
					InsertAfter(&list, ptr, &addMember);
				}
			}
		} else if ('e' == text[0]){
			printf("終了します\n");
			/* メモリ解放 */
			while (NULL != list.head){
				Node *ptr = list.head->next;
				free(list.head);
				list.head = ptr;
			}
			break;
		}
	}
	return 0;
}
