#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *append(char *p, char *q){
        char *r;//結合された文字列を納める領域を作るためのポインタ
        int i;
        int plength,qlength,strlength;
        plength = strlen(p);
        qlength = strlen(q);
        strlength = plength + qlength + 1;
        r = (char *)malloc(strlength);
        for(i=0;i<strlength;i++){
                if(i<plength){
                        r[i] =p[i];
                }else{
                        r[i] = q[i - plength];
                }
        }
        r[i]='\0';
        return(r);
}

int main(void){
        char pchars[256],qchars[256];
        char *rchars;

        printf("一つ目の文字列\n");
        printf("=>");scanf("%s",pchars);
        printf("２つ目の文字列\n");
        printf("=>");scanf("%s",qchars);
        printf("1:%s\n",pchars);
        printf("2:%s\n",qchars);
        rchars = append(pchars,qchars);
        printf("append:%s\n",rchars);
        return(0);
}
