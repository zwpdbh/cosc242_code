#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define string_len 80
#define array_len 10000


void *emalloc(size_t s) {
	void *result = malloc(s);
	if(NULL == result) {
		fprintf(stderr, "malloc failded\n");
		exit(EXIT_FAILURE);
	}
	return result;
}

int main(void) {
	char word[string_len];
	char *wordlist[array_len];
	int num_words;
	double average;
	int i;

	num_words = 0;
	while(num_words < array_len && 1 == scanf("%79s", word)) {
		wordlist[num_words] = emalloc((strlen(word) + 1) * sizeof wordlist[0][0]);
		strcpy(wordlist[num_words], word);
		num_words++;
	}

	average = 0.0;
	for(i=0; i<num_words; i++) {
		average += strlen(wordlist[i]);
	}

	average = average / num_words;
	printf("%f\n", average);

	for (i=0; i<num_words; i++) {
		free(wordlist[i]);
	}

	return 0;
}
