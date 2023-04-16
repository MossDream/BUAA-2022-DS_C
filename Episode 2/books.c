#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct lib {
	char infor[120];
}lib;
int compare(const void* a, const void* b) {
	return strcmp((*((lib*)a)).infor, (*((lib*)b)).infor);
}
int add(lib a[], char* s, int num) {
	strcpy(a[num].infor, s);
	num++;
	qsort(a, num, sizeof(lib), compare);
	return num;
}
void find(lib a[], char* s, int num) {
	s = strtok(s, "\n");
	int i, j, k = 0;
	int pos[5] = { 0 };
	for (i = 0; i < num; i++) {
		if (strstr(a[i].infor, s)) {
			char t[120] = { 0 };
			strcpy(t, a[i].infor);
			strtok(t, "\n");
			for (j = 0; j < strlen(a[i].infor); j++) {
				if (t[j] == ' ') {
					pos[k++] = j;
					t[j] = '\0';
				}
			}
			k = 0;
			printf("%-50s%-20s%-30s%-10s\n", t, t + pos[0] + 1, t + pos[1] + 1, t + pos[2] + 1);
		}
	}
}
int delete(lib a[], char* s, int num) {
	int i, j;
	s = strtok(s, "\n");
	for (i = 0; i < num; i++) {
		if (strstr(a[i].infor, s)) {
			for (j = i; j < num; j++) {
				strcpy(a[j].infor, a[j + 1].infor);
			}
			num--;
			i--;
		}
	}
	qsort(a, num, sizeof(lib), compare);
	return num;
}
int main() {
	FILE* fpr = fopen("books.txt", "r");
	if (fpr == NULL) {
		perror("Open books.txt:");
	}
	FILE* fpw = fopen("ordered.txt", "w");
	if (fpw == NULL) {
		perror("Open ordered.txt:");
	}
	lib a[505] = { 0 }, b[505] = { 0 };
	char s[120] = { 0 };
	int num = 0;
	while ((fgets(a[num].infor, 120, fpr) != NULL)) {
		num++;
	}
	qsort(a, num, sizeof(lib), compare);
	int op;
	do {
		scanf("%d", &op);
		switch (op) {
		case 1:
			getchar();
			fgets(s, 120, stdin);
			num = add(a, s, num); 
			break;
		case 2:
			getchar();
			fgets(s, 120, stdin);
			find(a, s, num);
			break;
		case 3:
			getchar();
			fgets(s, 120, stdin);
			num = delete(a, s, num);
		    break;
		default:break;
		}
	} while (op);
	int i, j, k = 0, pos[5] = { 0 };
	for (i = 0; i < num; i++) {
		strcpy(b[i].infor, a[i].infor);
		strtok(b[i].infor, "\n");
		for (j = 0; j < strlen(a[i].infor); j++) {
			if (b[i].infor[j] == ' ') {
				pos[k++] = j;
				b[i].infor[j] = '\0';
			}
		}
		k = 0;
		fprintf(fpw, "%-50s%-20s%-30s%-10s\n", b[i].infor, b[i].infor + pos[0] + 1, b[i].infor + pos[1] + 1, b[i].infor + pos[2] + 1);
	}
	fclose(fpr); fpr = NULL;
	fclose(fpw); fpw = NULL;
	return 0;
}