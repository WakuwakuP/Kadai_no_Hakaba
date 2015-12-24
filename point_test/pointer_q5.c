#include <stdio.h>
#include <string.h>

char* searchSpace(char *pmoji, int size);

int main(){
	char str[129], *tmp_str;
	fgets(str, sizeof(str), stdin);
	tmp_str = searchSpace(str, strlen(str));
	if(tmp_str == '\0'){
		printf("this sentence contain no space.\n");
		return 0;
	}
	while(' ' != *tmp_str && '\0' != *tmp_str){
		printf("%c", *tmp_str);
		tmp_str++;
	}
	if(' ' == *tmp_str){
		puts("");
	}
	return 0;
}

char* searchSpace(char *pmoji, int size){
	int i;
	for(i = 0; i < size; ++i){
		if (*pmoji == ' '){
			return pmoji + 1;
		}
		pmoji++;
	}

	return NULL;
}