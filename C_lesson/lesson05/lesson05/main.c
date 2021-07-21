#include <stdio.h>

// 宏方法 ["\"转义多行]
#define MAX(A,B) \
A>B?A:B

int main() {
	//printf("Hello World! \n");
	printf("最大值:%d",MAX(3, 4));
}