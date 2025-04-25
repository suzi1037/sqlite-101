#include "stdio.h"


typedef struct Point {
    int x;
    int y;
} Point;

int main() {
    printf("Hello, World!\n");
    Point p = {1, 2};
    printf("%d, %d\n", p.x, p.y);
    return 0;
}