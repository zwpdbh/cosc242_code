#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
    int i = 0;
    double j = 1.0;

    for(i = 0; i < 10; i++) {
        printf("%d %12f %12.3f \n", i, j, sqrt(j));
        j *= 2;
    }

    return 0;
}
