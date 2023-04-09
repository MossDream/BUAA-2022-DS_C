#define  _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main() {
	char s[150] = { 0 }, p[150] = { 0 };
	scanf("%s", s);
	int i, cnt = 0;
	for (i = 0; s[i] != '.'; i++) {
		cnt++;
	}
	if (cnt == 1) {
		if (s[0] == '0') {
			int j = 2;
			while (s[j] == '0') {
				j++;
			}
			int tmp = j;
			p[0] = s[j];
			if (j != strlen(s) - 1) {
				p[1] = '.';
				int k = 0;
				while (j <= (strlen(s) - 1)) {
					p[2 + k] = s[j + 1];
					k++; j++;
				}
			}
			printf("%se-%d", p, tmp - 1);
		}
		else {
			printf("%se0", s);
		}
	}
	else {
		p[0] = s[0]; p[1] = '.';
		int m = 0, n = 1;
		while (n <= (strlen(s) - 1)){
			if (s[n] != '.') {
				p[2 + m] = s[n]; m++; n++;
			}
			else { n++; }
		}
		printf("%se%d", p, cnt - 1);
	}
	return 0;
}
