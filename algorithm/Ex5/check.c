#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  char data;
  struct node *next;
} Node;

typedef struct {
  Node *head;
  Node *crnt;
} List;

typedef struct {
  int max;
  int num;
  List stk;
} Stack;

/* 初期化 */
void init (Stack *s) {
  s->max = 0;		// 今回は使用しない
	s->num = 0;
	s->stk.head = NULL;
	s->stk.crnt = NULL;
}

/* スタックにデータをプッシュ */
int Push (Stack *s, char x) {
  s->stk.crnt = s->stk.head;
  if ((s->stk.head = calloc(1, sizeof(Node))) == NULL){
    return -1;
  }
  s->stk.head->data = x;
  s->stk.head->next = s->stk.crnt;
  s->num += 1;

  return 0;
}

/* スタックからデータをポップ */
int Pop (Stack *s, char *x) {
  if (s->num <= 0) {
    return -1;
  }
  s->stk.crnt = s->stk.head->next;
  *x = s->stk.head->data;
  free(s->stk.head);
  s->stk.head = s->stk.crnt;
  s->num -= 1;
  return 0;
}

/* スタックの一番上を見る */
int Peek (const Stack *s, char *x) {
  if (s->num <= 0){
    return -1;
  }
  *x = s->stk.head->data;
  return 0;
}

/* スタックのサイズを返す */
int Size (const Stack *s) {
  return s->num;
}

/* スタックが空ならtrueを返す */
int Empty (const Stack *s) {
  return (s->num <= 0);
}

/* Search */
int Search (Stack *s, char *x) {
  int i = 1;

  s->stk.crnt = s->stk.head;
  while (s->stk.crnt != NULL) {
    if (s->stk.crnt->data == *x) {
      return i;
    }
    s->stk.crnt = s->stk.crnt->next;
    i += 1;
  }
  return -1;
}

/* データ表示 */
void Display (Stack *s) {
  if (Empty(s)){
    puts("No Data.");
    return;
  }
  s->stk.crnt = s->stk.head;
  puts("[Top]");
  while (s->stk.crnt != NULL) {
    printf("%c", s->stk.crnt->data);
    s->stk.crnt = s->stk.crnt->next;
  }
  putchar('\n');
  puts("[Bottom]");
}

void Clear (Stack *s) {
  while (s->stk.head != NULL) {
    s->stk.crnt = s->stk.head->next;
    free(s->stk.head);
    s->stk.head = s->stk.crnt;
  }
  init(s);
}

/* check関数 */
int judgment(char *str) {
	Stack stk;
	char top, c;
	int i = 0;

	init(&stk);
	while(str[i] != '\0') {
		/* 入力文字列を1文字ずつ調べる */
		switch(str[i]) {
		 /* 始め括弧のとき...それに対応する閉じ括弧をスタックにプッシュ */
		 case '(':
		 	Push(&stk, ')');
		 	break;
		 case '{':
		 	Push(&stk, '}');
		 	break;
		 case '[':
		 	Push(&stk, ']');
		 	break;

		 /*
		 	閉じ括弧のとき...スタックが空もしくは整合性が取れていないときは0を返す
		 	整合性が取れたときはスタックから1つポップ
		 */
		 case ')':
		 case '}':
		 case ']':
		 	top = -1;
		 	Peek(&stk, &top);
		 	if(Empty(&stk) || top != str[i])
		 		return 0;
		 	else
		 		Pop(&stk, &c);
		 	break;

		 default:
		 	break;
		}
		i++;
	}

	/* 文字列を全て見終わってスタックが空なら1 そうでなければ0を返す */
	if(Empty(&stk))
		return 1;
	else
		return 0;
}

int main(void) {
	char str[101], c;
	int flag_continue = 1;
	int i;

	while (1 == flag_continue) {
		puts("-----");
		puts("Check the string.");
		printf("Please enter a character string. (100 characters or less):");
		/* 1行入力 空白を挟んだ文字列も入力可 */
		for (i = 0; i < 100 && (c = getchar()) != '\n'; ++i)
        	str[i] = c;
        while(c != '\n')	c = getchar();	// 100文字以上の文字列の除去
        str[i] = '\0';	// 末尾にヌル文字追加

		if(judgment(str)) {
			puts("This string has bracket consistency.");
		} else {
			puts("This string does not have parenthesized consistency.");
		}

		printf("Continue?（y:1/n:0）:");
		scanf("%d", &flag_continue);
		c = getchar();	// 改行文字の除去
	}

	return 0;
}
