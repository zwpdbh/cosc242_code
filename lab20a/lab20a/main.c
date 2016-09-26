
#include<stdlib.h>
#include<stdio.h>

int is_prime(int candidate) {
    int i;

    for(i = 2; i < candidate; i++) {
        if(candidate % i == 0) {
            return 0;
        }
    }
    return 1;
}


int main(void) {
    int candidate = 2;
    int count = 0;
    
    while (count < 200) {
        if (is_prime(candidate)) {
            count += 1;
            printf("%5d", candidate);
            if (count % 10 == 0) {
                printf("\n");
            }
        }
        candidate += 1;
    }
    
    return 0;
}