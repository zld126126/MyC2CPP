#include <stdio.h>
#include <string.h>

int main() {
	char buf[1000];
	memset(buf, 0, 100);
	buf[0] = "Hello";
	//sprintf_s(buf, "Hello %d", 100);
	printf("value:%s", buf);
	return 0;
}