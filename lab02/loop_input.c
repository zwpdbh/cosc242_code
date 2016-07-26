#include <stdio.h>

int main(int argc, char *argv[]) {
	double entry = 0.0;
	double total = 0.0;
	
	double dummy = 0.0;
	
	int numberOfEntry = 0;
	
	while (2 == scanf("%lg %lg", &entry, &dummy)) {
		total += entry;
		numberOfEntry++;
	}
	
	printf("%f \n", total/numberOfEntry);
	printf("%d \n", numberOfEntry);
	
	return 0;
	
}