#include <stdio.h>

void SayHello() {
	printf("Hello World! \n");
}

int main() {

	// º¯ÊıÖ¸Õë
	void(*p)();
	p = SayHello;
	p();
	return 0;
}