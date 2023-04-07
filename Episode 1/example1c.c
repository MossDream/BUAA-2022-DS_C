#define  _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void clear1(char s[],char c) {
	int i, j;
	for (i = j = 0; s[i] != '\0'; i++) {
		if (s[i] != c) {
			s[j++] = s[i];
		}
	}
	s[j] = '\0';
}
void clear2(int s[], int c,int n) {
	int i, j;
	for (i = j = 0; i<n; i++) {
		if (s[i] != c) {
			s[j++] = s[i];
		}
	}
}
int cal(int opn1, int opn2, char op) {
	switch (op) {
	case '+':return opn1 + opn2; break;
	case '-':return opn1 - opn2; break;
	case '*':return opn1 * opn2; break;
	case '/':return opn1 / opn2; break;
	default:break;
	}
}
int main() {
	char s[1000] = { 0 }, op[600] = { 0 };
	int opn[600] = { 0 };
	gets(s);
	clear1(s,' ');
	int i = 0, j = 0, k = 0;
	while (s[i]!='=') {
		if (s[i] >= '0' && s[i] <= '9') {
			opn[j] = s[i] - '0';
			i++;
			while (s[i] >= '0' && s[i] <= '9') {
				opn[j] = opn[j] * 10 + s[i] - '0';
				i++;
			}
			j++; 
		}
		else {
			op[k++] = s[i];
			i++;
		}
	}
	for (i = 0; i < k; i++) {
		if (op[i] == '*' || op[i] == '/') {
			opn[i + 1] = cal(opn[i], opn[i + 1], op[i]);
			opn[i] = -100000;
		}
	}
	clear2(opn,-100000,j);
	clear1(op, '*');
	clear1(op, '/');
	long res = opn[0];
	for (i = 0; op[i]!='\0'; i++) {
		if (op[i] == '-') {
			res -= opn[i + 1];
		}
		else {
			res += opn[i + 1];
		}
	}
	printf("%ld\n", res);
	return 0;
}
