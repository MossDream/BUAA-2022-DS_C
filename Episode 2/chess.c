#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
int a[20][20] = { 0 };
int blockcheck(int x, int y) {
	int i, j, cnt1 = 0, cnt2 = 0;
	for (i = x; i <= x + 4; i++) {
		for (j = y; j <= y + 4; j++) {
			if (a[i][j] == 1) {
				cnt1++;
			}
			else if (a[i][j] == 2) {
				cnt2++;
			}
		}
		if (j > y + 4) {
			j--;
		}
		if (cnt1 == 4 && (a[i][y] == 0 || a[i][j] == 0)) {
			if (a[i][y] == 0) {
				printf("1:%d,%d\n", i, y + 1);
			}
			else if(a[i][j] == 0){
				printf("1:%d,%d\n", i, y);
			}
			return 1;
		}
		else if (cnt2 == 4 && (a[i][y] == 0 || a[i][j] == 0)) {
			if (a[i][y] == 0) {
				printf("2:%d,%d\n", i, y + 1);
			}
			else if(a[i][j] == 0){
				printf("2:%d,%d\n", i, y);
			}
			return 1;
		}
		cnt1 = 0; cnt2 = 0;
	}
	for (j = y; j <= y + 4; j++) {
		for (i = x; i <= x + 4; i++) {
			if (a[i][j] == 1) {
				cnt1++;
			}
			else if (a[i][j] == 2) {
				cnt2++;
			}
		}
		if (i > x + 4) {
			i--;
		}
		if (cnt1 == 4 && (a[x][j] == 0 || a[i][j] == 0)) {
			if (a[x][j] == 0) {
				printf("1:%d,%d\n", x + 1, j);
			}
			else if(a[i][j] == 0){
				printf("1:%d,%d\n", x, j);
			}
			return 1;
		}
		else if (cnt2 == 4 && (a[x][j] == 0 || a[i][j] == 0)) {
			if (a[x][j] == 0) {
				printf("2:%d,%d\n", x + 1, j);
			}
			else if(a[i][j] == 0){
				printf("2:%d,%d\n", x, j);
			}
			return 1;
		}
		cnt1 = 0; cnt2 = 0;
	}
	int k;
	for (k = 0; k <= 4; k++) {
		if (a[x + k][y + k]==1) {
			cnt1++;
		}
		else if (a[x + k][y + k] == 2) {
			cnt2++;
		}
	}
	if (cnt1 == 4 && (a[x][y] == 0 || a[x + 4][y + 4] == 0)) {
		if (a[x][y] == 0) {
			printf("1:%d,%d\n", x + 1, y + 1);
		}
		else if(a[x + 4][y + 4] == 0){
			printf("1:%d,%d\n", x, y);
		}
		return 1;
	}
	else if (cnt2 == 4 && (a[x][y] == 0 || a[x + 4][y + 4] == 0)) {
		if (a[x][y] == 0) {
			printf("2:%d,%d\n", x + 1, y + 1);
		}
		else if (a[x + 4][y + 4] == 0) {
			printf("2:%d,%d\n", x, y);
		}
		return 1;
	}
	cnt1 = 0; cnt2 = 0;
	for (k = 0; k <= 4; k++) {
		if (a[x + k][y + 4 - k] ==  1) {
			cnt1++;
		}
		else if (a[x + k][y + 4 - k] == 2) {
			cnt2++;
		}
	}
	if (cnt1 == 4 && (a[x][y + 4] == 0 || a[x + 4][y] == 0)) {
		if (a[x][y + 4] == 0) {
			printf("1:%d,%d\n", x + 1, y + 3);
		}
		else if (a[x + 4][y] == 0) {
			printf("1:%d,%d\n", x, y + 4);
		}
		return 1;
	}
	else if (cnt2 == 4 && (a[x][y + 4] == 0 || a[x + 4][y] == 0)) {
		if (a[x][y + 4] == 0) {
			printf("2:%d,%d\n", x + 1, y + 3);
		}
		else if (a[x + 4][y] == 0) {
			printf("2:%d,%d\n", x, y + 4);
		}
		return 1;
	}
	return 0;
}
int main() {
	int i, j, flag = 1;
	for (i = 1; i <= 19; i++) {
		for (j = 1; j <= 19; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	for (i = 1; i <= 15; i++) {
		for (j = 1; j <= 15; j++) {
			if (blockcheck(i, j)==1) {
				flag = 0;
				break;
			}
		}
		if (flag == 0) {
			break;
		}
	}
	if (flag) {
		printf("No\n");
	}
	return 0;
}