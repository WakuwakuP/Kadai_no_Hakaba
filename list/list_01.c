#include <stdio.h>
#include <stdlib.h>

struct p{
	char name[20];
	struct p *next;
};

void add_membar(struct p *sp);
void display_list(struct p *sp);
void delete_member(struct p *sp);
int list_size(struct p *p);

void add_membar(struct p *sp){
	struct p *new;
	struct p *next;
	display_list(sp);
	new = (struct p *)malloc(sizeof(struct p));
	new->next = NULL;
	next = sp;
	while(next->next != NULL){
		next = next->next;
	}
	printf("Add data? :");
	scanf("%s", new->name);
	next->next = new;
}

void delete_member(struct p *sp){
	int n, i;
	int del_mode;
	struct p *prev, *tmp;
	prev = sp;
	if(prev->next == NULL){
		printf("---------------------------\n");
		printf("NO DATA\n");
		printf("---------------------------\n");
	}
	else{
		printf("delele mode?\nnumber : 1 | text : 2\n:");
		scanf("%d", &del_mode);
		if(del_mode == 1){
			printf("What number?\n:");
			scanf("%d", &n);
			for(i = 0; i < n || prev->next != NULL; i++){
				prev = prev->next;
			}
			tmp = prev->next->next;
			free(prev->next);
			prev->next = tmp;
			return;
		}
		else if(del_mode == 2){
			char text[20];
			printf("What text?\n:");
			scanf("%s", &text);
			while(prev->next->next != NULL){
				if(prev->next->name == text){
					if(prev->next->next != NULL){
						tmp = prev->next->next;
						free(prev->next);
						prev->next = tmp;
						return;
					}
					free(prev->next);
					prev->next = NULL;
					return;
				}
				prev = prev->next;
			}
		}
	}
}

void display_list(struct p *sp){
	int count = 1;
	struct p *h;
	h = sp->next;
	printf("---------------------------\n");
	if(h == NULL){
		printf("NO DATA\n");
	}
	else{
		while(h != NULL){
			printf("%2d | %s\n", count, h->name);
			h = h->next;
			count++;
		}
	}
	printf("---------------------------\n");
}

int list_size(struct p *sp){
	int count = 0;
	struct p *h;
	h = sp;
	while(h != NULL){
		h = h->next;
		count++;
	}
	return count;
}

int main(){
	int n = 1;
	int operation;
	struct p *s_player;
	s_player->next = NULL;

	while(n){
		printf("\n\nAdd member : 1\nDelete member : 2\nDisplay list : 3\nExit : 4\n: ");
		scanf("%d", &operation);
		if(1 == operation){
			add_membar(s_player);
		}
		else if(2 == operation) {
			delete_member(s_player);
		}
		else if(3 == operation){
			display_list(s_player);
		}
		else if(4 == operation){
			n = 0;
		}
	}
	return 0;
}