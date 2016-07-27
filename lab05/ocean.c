#include <stdio.h>
#include <stdlib.h>

#define OCEAN_MAX 41981

struct ocean_datum {
	int x;
	int y;
	double conc;
};

void print_ocean_datum(struct ocean_datum *o) {
	printf("%d %d %.4f\n", o->x, o->y, o->conc);
}

int read_ocean_datum(struct ocean_datum *o) {
	return 3 == scanf("%d %d %lg", &o->x, &o->y, &o->conc);
}

int compare(struct ocean_datum d1, struct ocean_datum d2) {
	if(d1.conc > d2.conc) {
		return 1;
	} else if (d1.conc == d2.conc) {
		return 0;
	} else {
		return -1;
	}
}

void sort(struct ocean_datum data[], int size) {
	int j;
	int i;
	struct ocean_datum key;
	for(j=1; j<size; j++) {
		key = data[j];
		i = j-1;
		while(i>=0 && compare(key, data[i])<0) {
			data[i+1] = data[i];
			i--;
		}
		data[i+1] = key;
	}
	
}

int main(void) {
	struct ocean_datum ocean_data[OCEAN_MAX];
	int num_items;
	int i;

	num_items = 0;
	while (num_items < OCEAN_MAX && read_ocean_datum(&ocean_data[num_items])) {
		num_items++;
	}
	
	for(i = 0; i<num_items; i++) {
		print_ocean_datum(&ocean_data[i]);
	}
	/*sorting*/
	sort(ocean_data, OCEAN_MAX);
	/*print*/
	for(i = 0; i<num_items; i++) {
		print_ocean_datum(&ocean_data[i]);
	}

	return 0;
}
