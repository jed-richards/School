#include <stdio.h>

//int main(int argc, char** argv) {
int main() {
	printf("Hello, World!\n");

	//char str[] = "Jed Richards";  // same as below
	char* str = "Jed Richards";

	printf("Hello, %s!\n", str);

	return 0;
}
