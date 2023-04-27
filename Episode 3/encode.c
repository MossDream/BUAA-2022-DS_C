#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include <time.h> 
typedef struct node {
    char data;
    struct node* next;
}node;
typedef node* linklist;
typedef struct info {
	int tmp;
	linklist pos;
}info;
typedef struct table {
	char code;
	char original;
}table;
void unique(char* str) {
	int i, j, k;
	for (i = 0; i < strlen(str); i++) {
		for (j = 0; j <= i - 1; j++) {
			if (str[i] == str[j]) {
				for (k = i; k < strlen(str); k++) {
					str[k] = str[k + 1];
				}
				i--;
				break;
			}
		}
	}
}
int check(char* str, char c) {
	int i;
	for (i = 0; i < strlen(str); i++) {
		if (c == str[i]) {
			return 1;
		}
	}
	return 0;
}
void splice(char* str) {
	int i;
	char cpy[32] = { 0 };
	char c[3] = { 0 };
	strcpy(cpy, str);
	for (i = 32; i <= 126; i++) {
		 c[0] = i;
		if (check(cpy, c[0]) == 0) {
			strcat(str, c);
		}
	}
}
void create(linklist* L, char* str) {
	linklist p, q;
	int i = 1;
	*L = (linklist)malloc(sizeof(node));
	(*L)->data = str[0];
	(*L)->next = NULL;
	q = *L;
    while (str[i] != '\0') {
		p = (linklist)malloc(sizeof(node));
		p->data = str[i];
		q->next = p;
		q = p;
		i++;
	}
	q->next = (*L)->next;
}
info delete(linklist* L, int i) {
	int j;
	linklist p, q;
	info a = { 0 };
	p = *L;
	for (j = 1; j < i - 1; j++) {
		p = p->next;
	}
	q = p->next;
	p->next = q->next;
	a.pos = q->next;
	a.tmp = (int)(q->data);
	free(q);
	return a;
}
int compare(const void* a, const void* b) {
	table* c = (table*)a;
	table* d = (table*)b;
	return c->original - d->original;
}
int main(){
    clock_t start, end; 
    double cpu_time_used; 
    start = clock(); 
	char key[100] = { 0 };
	fgets(key, 32, stdin);
	strtok(key, "\n");
	unique(key);
	splice(key);
	linklist ring = NULL;
	create(&ring, key);
	int cnt = 0;
	int num = ring->data;
	table t[100] = { 0 };
	int i = 0;
	t[0].original = ring->data;
	linklist ringcpy = ring;
	ring = ring->next;
	free(ringcpy);
	for (cnt = 0; cnt < 94; cnt++) {
			info rec = delete(&ring, num);
			num = rec.tmp;
			t[i++].code = num;
			t[cnt + 1].original = num;
			ring = rec.pos;
	}
	t[i].code = key[0];
	qsort(t, 95, sizeof(table), compare);
	FILE* fpr = fopen("in.txt", "r");
	FILE* fpw = fopen("in_crpyt.txt", "w");
	if (fpr == NULL) {
		perror("In open in.txt:");
	}
	if (fpw == NULL) {
		perror("In open in_crpyt.txt:");
	}
    int c = 0;
	while ((c=fgetc(fpr)) != EOF) {
		if (c >= 32 && c <= 126) {
			fputc(t[c - 32].code, fpw);
		}
		else {
			fputc(c, fpw);
		}	
	}
	fclose(fpr);
	fpr = NULL;
	fclose(fpw);
	fpw = NULL;
   end = clock(); 
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    //printf("The code took % f seconds to execute.\n", cpu_time_used);
      return 0;
}