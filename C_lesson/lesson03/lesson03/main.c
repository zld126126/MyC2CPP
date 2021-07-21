#include <stdio.h>

// ×î´óÖµ
int Max(int a, int b) {
	if (a > b) {
		return a;
	}
	return b;
}

int main() {
	printf("Hello World! \n");
	printf("Max:%d", Max(3, 4));
}