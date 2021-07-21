#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	// printf("Hello World! \n");
	srand((int)time(NULL));
	int randNum = rand() % 100;
	printf("请输入一个1-100的数字:");
	int userInput;
	while (1) {
		scanf_s("%d", &userInput);
		if (userInput == randNum) {
			break;
		}

		if (userInput < randNum) {
			printf("%d < %d:数值过小 \n", userInput, randNum);
			continue;
		}
		printf("%d > %d:数值过大 \n", userInput, randNum);
	}
	printf("Num:%d \n", randNum);
	return 0;
}