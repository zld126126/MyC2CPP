#include <stdio.h>

void SayHello() {
	printf("Hello World! \n");
}

int main() {

	// ����ָ��
	void(*p)();
	p = SayHello;
	p();
	return 0;
}