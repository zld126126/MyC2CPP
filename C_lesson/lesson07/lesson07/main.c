#include <stdio.h>

int main() {
	//printf("Hello World! \n");
	for (int i = 0; i < 10; printf("%d\n", i++))
	{
		printf("<<<<<<\n");
	}

	int i = 0;
	while (i < 10) {
		printf("%d\n", i++);
	}

	do
	{
		printf("%d\n", i--);
	} while (i > 0);
}