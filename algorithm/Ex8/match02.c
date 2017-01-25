/*
	文字列探索（KMP法）
*/

#include <stdio.h>

void kmpMatch(const char txt[], const char pat[]);

int main(void) {
	char str_text[256];		// テキスト
	char str_pattern[256];		// パターン

	/* 入力 */
	printf("Text    : ");
	scanf("%s", str_text);
	printf("Pattern : ");
	scanf("%s", str_pattern);

	/* 文字列検索実行 */
	kmpMatch(str_text, str_pattern);

	return 0;
}

/* KMP法で文字列探索を行う */
void kmpMatch(const char str_text[], const char str_pattern[]) {
	int pt = 1;				// txtをなぞるカーソル
	int pp = 0;				// ptをなぞるカーソル
	int skip[1024];			// スキップテーブル
	int blank;				// 3段目の表示の際に挿入すべき空白の数を格納
	int ismatch;			// 現在の比較が一致したかどうか 1:一致 0:不一致
	int cont_cmp = 0;		// 比較回数カウンタ
	int i;

	/* スキップテーブル作成 */
	skip[pt] = 0;
	while (str_pattern[pt] != '\0') {
		if(str_pattern[pt] == str_pattern[pp])
			skip[++pt] = ++pp;
		else if(pp == 0)
			skip[++pt] = pp;
		else
			pp = skip[pp];
	}

	/* 文字列の探索 */
	pt = pp = 0;
	while (str_text[pt] != '\0' && str_pattern[pp] != '\0') {
		blank = pt-pp;		// ここの状態のptとppの値を使用したいのではじめに計算

		/*
			1段目の表示
			テキストを表示
		*/
		printf("%s\n", str_text);

		/*
			2段目の表示
			比較する場所にくるまで空白を挿入 ptの数だけ表示すればよい
			その後、比較した文字が一致した場合は+、一致しない場合は|を表示
		*/
		for (i=0; i<pt; i++)
			putchar(' ');

		if(str_text[pt] == str_pattern[pp]) {
			puts("+");
			pt++;
			pp++;
			ismatch = 1;
		} else if(pp == 0) {
			puts("|");
			pt++;
			ismatch = 0;
		} else {
			puts("|");
			pp = skip[pp];
			ismatch = 0;
		}

		/*
			3段目の表示
			パターンとテキストの比較する位置が揃うように空白を挿入した後パターンを表示
			ここでループのはじめに計算しておいた値を使用
		*/
		for (i=0; i<blank; i++)
			putchar(' ');
		printf("%s\n", str_pattern);

		if(ismatch)		puts("");
		else			puts("---");		// 一致しなかったときだけ区切り線を表示

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
