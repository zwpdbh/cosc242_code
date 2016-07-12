#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
    int f = 0;
    int g = 1;

    int i = 1;
    int tmp = 0;

    for(i = 1; i<=40; i++) {
        printf("%d ", g);
        tmp = g;
        g = f + g;
        f = tmp;

        if(i%5 == 0) {
            printf("\n");
        }
    }

    return 0;
}
