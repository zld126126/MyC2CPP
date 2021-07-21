#include <stdio.h>
#include <stdlib.h>

struct People {
	int age;
	char *name;
};

int main() {
	// printf("Hello World! \n");
	struct People p;
	p.name = "dong";
	p.age = 10;
	printf("age:%d \n",p.age);

	struct People p1 = p;
	p1.age = 20;
	printf("age:%d \n", p.age);
	printf("age:%d \n", p1.age);

	// 结构体指针
	struct People *p2 = malloc(sizeof(struct People));
	p2->name = "dong";
	p2->age = 10;
	printf("p2 age:%d \n", p2->age);
	struct People *p3 = p2;
	p3->age = 20;

	// 释放内存
	free(p2);
	printf("p2 age:%d \n", p2->age);
}