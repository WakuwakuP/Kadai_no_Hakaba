#include <stdio.h>

int main(void) {
    int a, b;

/* 入力 */
    printf("aの値 : ");
    scanf("%d", &a);

/* aより大きいbが入力されるまでループ */
    for (;;) {
        printf("bの値 : ");
        scanf("%d", &b);
        if (b <= a)
            printf("aより大きな値を入力せよ!\n");
        else
            break;
    }

/* 出力 */
    printf("b-aは%dです。\n", b-a);

    return 0;
}
