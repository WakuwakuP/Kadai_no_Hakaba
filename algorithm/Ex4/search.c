#include <stdio.h>
#include <string.h>

typedef struct {
  char name[10];
  int height;
  int weight;
} Person;

int npcmp(const Person *x, const Person *y){
  return strcmp(x->name, y->name);
}

void *binserch(const void *key, const void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)){
  size_t lowid = 0, midid, highid = nmemb - 1;
  int n;
  do {
    midid = (lowid + highid) / 2;
    printf("lowid=%d, midid=%d, highid=%d\n", (int)lowid, (int)midid, (int)highid);   // 動作デバック用出力
    n = compar((const void *)((char *)base+size*midid), key);

    if (0 == n){
      return (void *)((char *)base+size*midid);
    } else if(0 > n) {
      lowid = midid + 1;
    } else {
      highid = midid - 1;
    }
  } while(lowid <= highid);
  return NULL;
}

int main() {
  Person x[]= {
    {"ABE",      179, 79},
    {"NANGOH",   172, 63},
    {"SHIBATA",  176, 52},
    {"SUGIYAMA", 165, 51},
    {"TAKAOKA",  181, 73},
    {"TSURUMI",  172, 84}
  };

  int nx = sizeof(x) / sizeof(x[0]);
  int retry;

  puts("名前による探索を行います。");
  do{
    Person temp, *p;

    printf("名前\n:");
    scanf("%s", temp.name);

    p = binserch(&temp, x, nx,sizeof(Person), (int (*)(const void *, const void *))npcmp);

    if(p == NULL){
      puts("探索に失敗しました。");
    } else {
      puts("探索成功!! 以下の要素を見つけました。");
      printf("x[%d] : %s %dcm %dkg\n", (int)(p - x), p->name, p->height, p->weight);
    }
    printf("もう一度探索しますか? (1…yes/0…no)\n:");
    scanf("%d", &retry);
  } while (retry == 1);
  return 0;
}
