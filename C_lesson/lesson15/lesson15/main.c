#include <stdio.h>

int main() {
	// printf("Hello World! \n");
	FILE * f = fopen("data.txt", "w");
	fprintf(f, "Hello c\n");
	fclose(f);
	return 0;
}