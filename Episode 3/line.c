#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <malloc.h>
#include <time.h> 
typedef struct line {
    int x1;
    int y1;
    int x2;
    int y2;
}Line;
typedef struct point {
	int x;
	int y;
}Point;
int compare_point(Point a, Point b) {
    if (a.x > b.x) {
        return 1;
    }
    else if (a.x < b.x) {
        return -1;
    }
    else {
        if (a.y > b.y) {
            return 1;
        }
        else if (a.y < b.y) {
            return -1;
        }
        else {
            return 0;
        }
    }
}
int compare(const void* a, const void* b) {
    Line* l1=(Line*)a;
    Line* l2=(Line*)b;
    Point p1 = { l1->x1,l1->y1 };
    Point p2 = { l2->x1,l2->y1 };
    return compare_point(p1, p2);
}
int main(){
    clock_t start, end; 
    double cpu_time_used; 
    start = clock(); 
    int n;
    scanf("%d", &n);
    Line* lines = (Line*)malloc(n * sizeof(Line));
    int i, j, x, y;
    for (i = 0; i < n; i++) {
        scanf("%d %d %d %d", &lines[i].x1, &lines[i].y1, &lines[i].x2, &lines[i].y2);
    }
    qsort(lines, n, sizeof(Line), compare);
    int max_len = 1;
    for (i = 0; i < n; i++) {
        int now_len = 1;
        int pos = i;
        for (j = i + 1; j < n; j++) {
            if (lines[pos].x2 == lines[j].x1 && lines[pos].y2 == lines[j].y1) {
            now_len++;
            pos = j;
            }
        }
        if(now_len>max_len){
            max_len = now_len;
            x = lines[i].x1;
            y = lines[i].y1;
		}
    }
    printf("%d %d %d", max_len, x, y);
    free(lines);
    end = clock(); 
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC; 
    //printf("The code took % f seconds to execute.\n", cpu_time_used);
      return 0;
}