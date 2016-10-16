#include <stdio.h>

int sumof(int a, int b);

int sumof(int a, int b){
    int sub = (a > b)? a - b + 1 : b - a + 1;
    int sum = a + b;
    return sum * sub / 2;
}

/* 入力テスト */
int main() {
    printf("%d\n", sumof(1,100));
    printf("%d\n", sumof(1,99));
    printf("%d\n", sumof(-1, 99));
    printf("%d\n", sumof(-20, 18));
    return 0;
}
