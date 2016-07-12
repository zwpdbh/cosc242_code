#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int isPrime(int num) {
    int i = 2;
    for(i = 2; i < num; i++) {
        if(num % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int target = 2;
    int count = 0;

    while(count < 100) {
        if(isPrime(target)) {
            if (count % 7 == 0) {
                printf("\n");
            }
            printf("%3sd ", target);
            count++;
        }
        target++;
    }

    return 0;
}
