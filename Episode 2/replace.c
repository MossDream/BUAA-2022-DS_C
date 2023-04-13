#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<ctype.h>
int main() {
	char ori[50] = { 0 }, rep[50] = { 0 };
	int i;
	for (i = 0; i < strlen(ori); i++) {
		ori[i] = tolower(ori[i]);
	}
	scanf("%s %s",ori, rep);
	FILE* fpr=fopen("filein.txt", "r");
	if (fpr == NULL) {
		perror("Open filein.txt:");
	}
	FILE* fpw = fopen("fileout.txt", "w");
	if (fpw == NULL) {
		perror("Open fileout.txt:");
	}
	char c, str[50] = { 0 }, strr[50] = { 0 };
	while (fgets(str,50,fpr)!=NULL) {
		for (i = 0; i < strlen(str); i++) {
			if (isalpha(str[i])) {
				strr[i] = tolower(str[i]);
			}
			else {
				strr[i] = str[i];
			}
		}
		int j, cnt = 0;
		for (i = 0; i < strlen(str);) {
			for (j = 0; j < strlen(ori); j++) {
				if (strr[i + j] == ori[j]) {
					cnt++;
				}
			}
			if (cnt == strlen(ori)) {
				fputs(rep, fpw);
				i += strlen(ori);
			}
			else {
				fputc(str[i], fpw);
				i++;
			}
			cnt = 0;
		}
		for (i = 0; i < strlen(str); i++) {
			str[i] = 0; strr[i] = 0;
		}
	}
	fclose(fpr); fpr = NULL;
	fclose(fpw); fpw = NULL;
	return 0;
}