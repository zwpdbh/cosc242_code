#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define num_of_words 10

void *emalloc(size_t s) {
	void *result = malloc(s);
	if(NULL == result) {
		fprintf(stderr, "Allocation Failed!\n");
		exit(EXIT_FAILURE);
	}
	return result;
}

void sort(char **arr, int size) {
	int j = 1;
	char *key;
	int i;
	for(j=1; j<size; j++) {
		key = arr[j];
		printf("Key is %s \n", key);
		i = j - 1;
		while(i>=0 && strcmp(key, arr[i])<0) {
			arr[i+1] = arr[i];
			i--;
		}
		printf("arr[i+1]: %s, key is: %s\n", arr[i+1], key);
		arr[i+1] = key;
	}
}

int main(void) {
	char word[80];
	char *wordlist[num_of_words];

	int num;
	
	num = 0;
	while(num < num_of_words && 1 == scanf("%79s", word)) {
		wordlist[num] = emalloc((strlen(word)+1) * sizeof wordlist[0][0]);
		strcpy(wordlist[num], word);
		num++;
	}

	for(num=0; num<num_of_words; num++) {
		printf("%s\n", wordlist[num]);
	}

	sort(wordlist, num_of_words);

	for(num=0; num<num_of_words; num++) {
		printf("%s\n", wordlist[num]);
		free(wordlist[num]);
	}


	return 0;
}
