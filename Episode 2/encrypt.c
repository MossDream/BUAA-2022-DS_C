#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
char cmp[27] = "abcdefghijklmnopqrstuvwxyz";
char change(char ori, char key[]) {
	int i, j, k;
	char final[60] = { 0 };
	char copy[27] = "zyxwvutsrqponmlkjihgfedcba";
	strcpy(final, key);
	for (i = 0; i < strlen(final); i++) {
		for (j = 0; j <= i - 1; j++) {
			if (final[j] == final[i]) {
				for (k = i; k < strlen(final); k++) {
					final[k] = final[k + 1];
				}
				i--;
				break;
			}
		}
	}
	for (i = 0; i < strlen(copy); i++) {
		for (j = 0; j < strlen(final); j++) {
			if (final[j] == copy[i]) {
				for (k = i; k < strlen(copy); k++) {
					copy[k] = copy[k + 1];
				}
				i--;
				break;
			}
		}
	}
	j = 0;
	for (i = strlen(final); i < 26; i++,j++) {
		final[i] = copy[j];
	}
	for (i = 0; i < 26; i++) {
		if (ori == cmp[i]) {
			return final[i];
		}
	}
}
int main() {
	char key[60] = { 0 }, str[60] = { 0 };
	scanf("%s", key);
	FILE* fpr = fopen("encrypt.txt", "r");
	if (fpr == NULL) {
		perror("Open encrypt.txt:");
	}
	FILE* fpw = fopen("output.txt", "w");
	if (fpw == NULL) {
		perror("Open output.txt:");
	}
	while (fgets(str, 60,  fpr) != NULL) {
		int i;
		for (i = 0; i < strlen(str); i++) {
			if (islower(str[i])) {
				fputc(change(str[i], key), fpw);
			}
			else {
				fputc(str[i], fpw);
			}
		}
		for (i = 0; i < strlen(str); i++) {
			str[i] = 0;
		}
	}
	fclose(fpr); fpr = NULL;
	fclose(fpw); fpw = NULL;
	return 0;
}