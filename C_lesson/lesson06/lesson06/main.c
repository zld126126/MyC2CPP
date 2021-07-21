#include <stdio.h>

void TestIf1(int score) {
	if (score < 60) {
		printf("%d,������\n", score);
		return;
	}
	printf("%d,����\n", score);
}

void TestIf2(int score) {
	int s = score / 10;
	switch (s) {
	case 5:
	case 4:
	case 3:
	case 2:
	case 1:
	case 0:
		printf("%d,������\n", score);
		return;
	default:
		printf("%d,����\n", score);
		return;
	}
}

int main() {
	// printf("Hello World! \n");
	TestIf1(55);
	TestIf1(85);
	TestIf2(60);
}