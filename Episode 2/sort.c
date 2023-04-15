#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct infor {
	char name[25];
	char tel[12];
	int cnt;
}infor;
int compare(const void* a, const void* b) {
	return strcmp((*(infor*)a).name, (*(infor*)b).name);
}
int main(){
	int num;
	scanf("%d", &num);
	infor a[100] = { 0 };
	infor b[100] = { 0 };
	int i, j, num1 = 0;
	for (i = 0; i < num; i++) {
		scanf("%s %s", a[i].name, a[i].tel);
	}
	for (i = 0; i < num; i++) {
		if (a[i].cnt == 0) {
			strcpy(b[num1].tel, a[i].tel);
			strcpy(b[num1].name, a[i].name);
			num1++;
			b[num1].cnt = 0;
                for (j = i + 1; j < num; j++) {
				if (a[j].cnt == 0 && strcmp(a[i].name, a[j].name) == 0 && strcmp(a[i].tel, a[j].tel) == 0) {
					a[j].cnt = -1;		
		}
			}
		}
	}
	int key = 1;
	for (i = 0; i < num1; i++) {
		if (b[i].cnt == 0) {
			for (j = i + 1; j < num1; j++) {
				if (strcmp(b[i].name, b[j].name) == 0) {
					char end[5] = { 0 };
					sprintf(end, "_%d", key++);
					strcat(b[j].name, end);
					b[j].cnt = 1;
					b[i].cnt = 1;
				}
			}
		}
		key = 1;
	}
	qsort(b, num1, sizeof(infor), compare);
	for (i = 0; i < num1; i++) {
		printf("%s %s\n", b[i].name, b[i].tel);
	}
	return 0;
}