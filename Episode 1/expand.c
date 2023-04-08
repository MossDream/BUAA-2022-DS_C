#define  _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
int small(char c) {
	if (c >= 'a' && c <= 'z') {
		return 1;
	}
	else { return 0; }
}
int big(char c) {
	if (c >= 'A' && c <= 'Z') {
		return 1;
	}
	else { return 0; }
}
int dig(char c) {
	if (c >= '0' && c <= '9') {
		return 1;
	}
	else { return 0; }
}
int judge(char* ss, int i) {
	if ((ss[i - 1] < ss[i + 1]) && ((small(ss[i - 1]) && small(ss[i + 1])) || (big(ss[i - 1]) && big(ss[i + 1])) || (dig(ss[i - 1]) && dig(ss[i + 1])))) {
		return 1;
	}
	else { return 0; }
}
void myexp(char *s,size_t n) {
	int i = 0, j = 0;
	for (i = 0; i < n; i++) {
		if (s[i] == '-' && i != 0 && i != n) {
			if (judge(s, i)) {
				for (j = 1; j <= (s[i + 1] - s[i - 1] - 1); j++) {
					printf("%c", s[i - 1] + j);
				}
			}
			else { printf("%c", s[i]);}
		}
		else { printf("%c", s[i]); }
	}
}
int main() {
	char s[1000] = { 0 };
	scanf("%s", s);
	myexp(s,strlen(s));
	return 0;
}


