#include <stdio.h>

#define MAX 10                    // 最大値

int siguma_for(int n);            // forを使った関数
int siguma_while(int n);          // whileを使った関数
int siguma_do(int n);             // do-whileを使った関数
int siguma_rec(int n);            // 再帰を使った関数

int siguma_for(int n) {
  int i;
  int ans = 0;
  for (i = 1; i <= n; i++) {
    ans += i;
  }
  return ans;
}

int siguma_while(int n) {
  int ans = 0;
  while (0 != n) {
    ans += n;
    n--;
  }
  return ans;
}

int siguma_do(int n){
  int ans = 0;
  do {
    ans += n;
    n--;
  } while(0 != n);
  return ans;
}

int siguma_rec(int n) {
  if (0 < n) {
    return n + siguma_rec(n - 1);
  } else {
    return 0;
  }
}

int main() {
  printf("siguma_for   = %d\n", siguma_for(MAX));    // for
  printf("siguma_while = %d\n", siguma_while(MAX));  // while
  printf("siguma_do    = %d\n", siguma_do(MAX));     // do-while
  printf("siguma_rec   = %d\n", siguma_rec(MAX));    // Recursion
  return 0;
}
