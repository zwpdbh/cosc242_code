#include <stdio.h>

int main(void) {
    double s1;
    double s2;
    double s3;
    
    double score;
    double highestScore = 0;
    int winnter;
    int lastWinner = 0;
    
    while (4==fscanf(stdin, "%d%lg%lg%lg", &winnter, &s1, &s2, &s3)) {
        if (s1 < s2 && s1 < s3) {
            score = (s2 + s3) / 2;
        } else if (s2 < s1 && s2 < s3) {
            score = (s1 + s3) / 2;
        } else {
            score = (s1 + s2) / 2;
        }
        
        if (score >= highestScore ) {
            highestScore = score;
            lastWinner = winnter;
        }
    }
    printf("%d\n", lastWinner);
}