#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	// printf("Hello World! \n");
	srand((int)time(NULL));
	int randNum = rand() % 100;
	printf("������һ��1-100������:");
	int userInput;
	while (1) {
		scanf_s("%d", &userInput);
		if (userInput == randNum) {
			break;
		}

		if (userInput < randNum) {
			printf("%d < %d:��ֵ��С \n", userInput, randNum);
			continue;
		}
		printf("%d > %d:��ֵ���� \n", userInput, randNum);
	}
	printf("Num:%d \n", randNum);
	return 0;
}