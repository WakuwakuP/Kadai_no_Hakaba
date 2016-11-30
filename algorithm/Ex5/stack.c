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

/* サンプル */
int main(void) {
  Stack s;
  init(&s);

  while (1) {
    int  menu;
    char x;

    printf("Number of data : %d\n", Size(&s));
    printf("/ 1:Push / 2:Pop / 3:Peek / 4:Print / 5:Clear / 6:Search / 0:Exit / : ");
    scanf("%d", &menu);

    if(menu == 0) break;

    switch (menu) {
      case 1:	// プッシュ
        printf("Data : ");
        scanf("%c", &x);
        if (Push(&s, x) == -1) {
          puts("[ERROR]Failed to push the data.");
        } else {
          puts("Pushed successfully.");
        }
        break;
      case 2:	// ポップ
        if (Pop(&s, &x) == -1) {
          puts("[ERROR]Failed to pop the data.");
        } else {
          printf("Poped successfully : %c\n", x);
        }
        break;
      case 3:	// ピーク
        if (Peek(&s, &x) == -1)
        puts("[ERROR]Failed to peek the data.");
        else
        printf("Peeked successfully : %c\n", x);
        break;
      case 4:	// 表示
        Display(&s);
        break;
      case 5:	// クリア
        Clear(&s);
        puts("Cleared.");
        break;
      case 6:	// サーチ
      printf("Data : ");
      scanf("%c", &x);
      printf("\"%c\" is ", x);

      if((x = Search(&s, &x)) == -1) {
        puts("nothing.");
        break;
      }
      switch (x) {
        case 1:
          puts("the 1st from the top.");
          break;
        case 2:
          puts("the 2nd from the top.");
   	      break;
        case 3:
          puts("the 3rd from the top.");
          break;
        default:
          printf("the %dth from the top.\n", x);
      }
    }

  	puts("----------");
  }
  Clear(&s);

  return 0;
}
