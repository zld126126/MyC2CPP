#include <stdio.h>

typedef struct {
	int age;
} People;

void sayHello() {
	printf("Hello World! \n");
}

typedef void(*Func)();

// typedef
int main() {
	// printf("Hello World! \n");
	People p;
	p.age = 10;
	printf("age:%d\n", p.age);

	Func f = sayHello;
	f();
	return 0;
}