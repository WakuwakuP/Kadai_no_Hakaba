/*
文字列探索（力まかせ法）
*/

#include <stdio.h>

void bfMatch(const char txt[], const char pattern[]);

int main(void) {
  char txt[256];		// テキスト
  char str_pattern[256];		// パターン

  /* 入力 */
  printf("Text    : ");
  scanf("%s", txt);
  printf("pattern : ");
  scanf("%s", str_pattern);

  /* 文字列検索実行 */
  bfMatch(txt, str_pattern);

  return 0;
}

/* 力任せ法で文字列探索を行う */
void bfMatch(const char txt[], const char str_pattern[]) {
  int pt = 0;				// txtをなぞるカーソル
  int pp = 0;				// ptをなぞるカーソル
  int match_head = -1;	// パターンの先頭と比較するテキストの位置
  int cont_cmp = 0;		// 比較回数カウンタ
  int i;

  /* 文字列の探索 */
  while (txt[pt] != '\0' && str_pattern[pp] != '\0') {
    /*
    1段目の表示
    比較するパターンが先頭のときは、それと比較するテキストの場所（数字）とテキストを表示
    そうでないときは位置揃えのため空白を挿入しテキストを表示
    */
    if(pp == 0)
    printf("%3d %s\n", ++match_head, txt);
    else
    printf("    %s\n", txt);

    /*
    2段目の表示
    比較する場所にくるまで空白を挿入 match_headにppと前の空白部分を足した数がそれである
    その後、比較した文字が一致した場合は+、一致しない場合は|を表示
    */
    for (i=0; i<match_head+pp+4; i++)
    putchar(' ');

    if(txt[pt] == str_pattern[pp]) {
      puts("+");
      pt++;
      pp++;
    } else {
      puts("|");
      pt = pt-pp+1;
      pp = 0;
    }

    /*
    3段目の表示
    パターンとテキストの比較する位置が揃うように空白を挿入した後パターンを表示
    */
    for (i=0; i<match_head+4; i++)
    putchar(' ');
    printf("%s\n\n", str_pattern);

    cont_cmp++;		// 比較回数カウント
  }

  /* 結果表示 */
  printf("一致場所 : ");
  if(str_pattern[pp] == '\0')
  printf("%d\n", pt-pp);
  else
  puts("none");

  printf("比較回数 : %d\n", cont_cmp);
}
