#include <stdio.h>

int main() {
	// printf("Hello World! \n");
	puts("Hello C\n");

	// char buf
	char buf[100];
	gets(buf);
	puts(buf);

	// 获取控制台输入
	int a;
	scanf("%d", &a);
	printf("%d\n", a);
	return 0;
}