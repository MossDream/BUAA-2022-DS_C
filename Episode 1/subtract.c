#define  _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main() {
	char s1[90] = { 0 }, s2[90] = { 0 };
	int num1[90] = { 0 }, num2[90] = { 0 }, pri[90] = { 0 };
	scanf("%s", s1);
	scanf("%s", s2);
	int i, j, cnt1 = 0, cnt2 = 0, flag = 1;
	
	if (strlen(s1) < strlen(s2)) {
		for (i = strlen(s2)-1; i >= 0; i--) {
			num1[cnt1++] = s2[i]-'0';
		}
		for (i = strlen(s1)-1; i >= 0; i--) {
			num2[cnt2++] = s1[i]-'0';
		}
		flag = 0;
	}
	else if (strlen(s1) == strlen(s2)) {
		if (strcmp(s1, s2) < 0) {
			for (i = strlen(s2)-1; i >= 0; i--) {
				num1[cnt1++] = s2[i]-'0';
			}
			for (i = strlen(s1)-1; i >= 0; i--) {
				num2[cnt2++] = s1[i]-'0';
			}
			flag = 0;
		}
		else {
			for (i = strlen(s1)-1; i >= 0; i--) {
				num1[cnt1++] = s1[i]-'0';
			}
			for (i = strlen(s2)-1; i >= 0; i--) {
				num2[cnt2++] = s2[i]-'0';
			}
		}
	}
	else {
		for (i = strlen(s1)-1; i >= 0; i--) {
			num1[cnt1++] = s1[i]-'0';
		}
		for (i = strlen(s2)-1; i >= 0; i--) {
			num2[cnt2++] = s2[i]-'0';
		}
	}
	int max = 0;
	if (cnt1 > cnt2) {
		max = cnt1;
	}
	else {
		max = cnt2;
	}
	for (i = 0; i <= max; i++) {
		if (num1[i] < num2[i]) {
			pri[i] = num1[i] + 10 - num2[i];
			if (i < max) num1[i + 1]--;
		}
		else {
			pri[i] = num1[i] - num2[i];
		}
	}
	
	int sign = 0, tag = 1;
	if (flag) {
		for (j = i ; j >= 0; j--) {
			if (pri[j] != 0) {
				sign = 1;
			}
			if (sign) {
				printf("%d", pri[j]);
				tag = 0;
			}
		}
	}
	else {
		printf("-");
		for (j = i; j >= 0; j--) {
			if (pri[j] != 0) {
				sign = 1;
			}
			if (sign) {
				printf("%d", pri[j]);
				tag = 0;
			}
		}
	}
	if (tag) {
		printf("0");
	}
	return 0;
}
