#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	char *string1 = "Hello";
	char string2[10];
	char *string3 = NULL;

	printf("%s ", string1);

	string2[0] = 'w';
	string2[1] = 'o';
	string2[2] = '\0';
	printf("%s", string2);

	strcpy(string2, "rld");
	printf("%s!\n", string2);

	string3 = string2;
	strcpy(string2, string1);
	printf("%s ", string3);

	string3 = malloc(10 * sizeof(string3[0]));
	strcpy(string3, "world!");
	printf("%s \n", string3);

	free(string3);
	printf("\n");
	char words[2][15];
	char tmp[15];

	strcpy(words[0], "123");
	strcpy(words[1], "456");
	printf("%s %s\n", words[0], words[1]);

	int i = 113;
	char result[80];
	sprintf(result, "There are %d items", i);
	printf("%s\n", result);
	
	return 0;
}
