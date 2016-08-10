#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
	int i = 0;
	if (argc == 1) {
		printf("It needs 1 argument to generate random integer.");
		return EXIT_FAILURE;
	}
	while (i < atoi(argv[1])) {
		printf("%d\n", rand() % atoi(argv[1]));
		i++;
	}
	
	return 0;
}