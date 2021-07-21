#include <stdio.h>

struct People {
	int age;
	char *name;

};

int main() {
	// printf("Hello World! \n");
	struct People p;
	p.age = 10;
	p.name = "dong";
	printf("%d,%s \n",p.age,p.name);

	struct People p1 = p;
	printf("%d,%s \n", p1.age, p1.name);
}