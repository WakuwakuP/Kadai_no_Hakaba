/*
	GitHub URL :https://github.com/WakuwakuP/Kadai_no_Hakaba/tree/master/mystring/
*/

int mystrlen(const char* str){
	int i = 0;
	while(*(str + i) != '\0'){
		i++;
	}
	return i;
}

char* mystrcpy(char* str1, const char* str2){
	int i = 0;
	while(*(str2 + i) != '\0'){
		*(str1 + i) = *(str2 + i);
		i++;
	}
	*(str1 + i) = '\0';
	return str1;
}

char* mystrcat(char* str1, const char* str2){
	int i = 0, j = 0;
	while(*(str1 + i) != '\0'){
		i++;
	}
	while(*(str2 + j) != '\0'){
		*(str1 + i) = *(str2 + j);
		i++;
		j++;
	}
	*(str1 + i) = '\0';
	return str1;
}

int mystrcmp(const char* str1, const char* str2){
	int i = 0;

	while(*(str1 + i) != '\0' && *(str2 + i) != '\0'){
		if(*(str2 + i) > *(str1 + i)){
			return -1;
		}
		else if(*(str1 + i) > *(str2 + i)){
			return 1;
		}
		else if(*(str1 + i) == *(str2 + i)){
			i++;
		}
		if(*(str1 + i) == '\0'){
			if(*(str2 + i) != '\0'){
				return -1;
			}
		}
		else if(*(str2 + i) == '\0'){
			if(*(str1 + i) != '\0'){
				return 1;
			}
		}
	}
	return 0;
}
