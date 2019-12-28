#include <stdio.h>

int main(int argc, char* argv[]) {
	char* lines[] = {
		"line 1",
		"line 2",
		"line 3",
	};

	int size = sizeof(lines) / sizeof(lines[0]);

	printf("%i\n %s\n %s\n %s\n", size, lines[0], lines[1], lines[2]);

	return 0;
}