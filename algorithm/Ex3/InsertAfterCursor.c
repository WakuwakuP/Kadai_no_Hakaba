#include <stdio.h>
#include <stdlib.h>

#define Null -1
#define SIZE 1024

typedef int Index;
/* Member定義 */
typedef struct {
	int no;
	char name[20];
} Member;

/* Node定義 */
typedef struct node {
	Member data;
	Index next;
	Index Dnext;
} Node;

/* List定義 */
typedef struct {
	Node *n;
	Index head;
	Index max;
	Index deleted;
	Index crnt;
} List;

/* 出力関数 */
void PrintList(const List *list){
	Index ptr = list->head;
	if (Null == ptr) {
		printf("No Data.\n");
	} else {
		puts("  Data");
		puts("|---|--------------------|");
		puts("| No|        Name        |");
		puts("|---|--------------------|");
		while (ptr != Null) {
			printf("|%3d|%20s|\n", list->n[ptr].data.no, list->n[ptr].data.name);
			ptr = list->n[ptr].next;
		}
		puts("|---|--------------------|");
	}
}

/* 空いている配列要素の取得 */
static Index getIndex(List *list){
	if (list->deleted == Null) {
		return ++(list->max);
	} else {
		Index rec = list->deleted;
		list->deleted = list->n[rec].Dnext;
		return rec;
	}
}

/* データをセット */
static void setNode(Node *n, const Member *x, Index next){
	n->data = *x;
	n->next = next;
}

/* 先頭挿入関数 */
void InsertFront (List *list, const Member *x) {
	Index ptr = list->head;
	list->head = list->crnt = getIndex(list);
	setNode(&list->n[list->head], x, ptr);
}

/* 位置任意挿入関数 */
void InsertAfter(List *list, Index idx, const Member *x){
	list->crnt = getIndex(list);
	setNode(&list->n[list->crnt], x, list->n[idx].next);
	list->n[idx].next = list->crnt;
}

int main() {
	List list;
	char text[10];
/* 初期化 */
	list.n       = calloc(SIZE, sizeof(Node));
	list.head    = Null;
	list.crnt    = Null;
	list.max     = Null;
	list.deleted = Null;

	for(;;){
		printf("何をしますか。(データの表示 : print / データの追加 : add / 終了 : exit)\n : ");
		scanf("%s", text);
		/* 頭文字のみ見る */
		if ('p' == text[0]) {
			PrintList(&list);
		} else if ('a' == text[0]) {
			int n, i;
			Member addMember;
			Index ptr = list.head;
			if (Null == ptr){			// リストが空の場合
				printf("no   : "); scanf("%d", &addMember.no);
				printf("name : "); scanf("%s", addMember.name);
				InsertFront(&list, &addMember);
			} else {
				printf("何個目の次に挿入しますか\n: "); scanf("%d", &n);
				if (0 == n) {				// 先頭の場合
					printf("No   : "); scanf("%d", &addMember.no);
					printf("name : "); scanf("%s", addMember.name);
					InsertFront(&list, &addMember);
				} else {
					for(i = 1; i < n; i++){
						if (Null == list.n[ptr].next) {
							printf("指定値が大きすぎです。\n最後に追加します。\n");
							break;
						}
						ptr = list.n[ptr].next;
					}
					printf("No   : "); scanf("%d", &addMember.no);
					printf("name : "); scanf("%s", addMember.name);
					InsertAfter(&list, ptr, &addMember);
				}
			}
		} else if ('e' == text[0]){
			printf("終了します\n");
			/* メモリ解放 */
			while (Null == list.head){
				Index ptr = list.n[list.head].next;
				Index del = list.deleted;
				list.deleted = list.head;
				list.n[list.head].Dnext = del;
				list.head = ptr;
			}
			free(list.n);
			break;
		}
	}
	return 0;
}
