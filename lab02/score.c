#include <stdlib.h>
#include <stdio.h>
#include <math.h>


double final_score(double score1, double score2, double score3) {
    if (score1 <= score2 && score1 <= score3) {
        return (score2 + score3)/2;
    } else if (score2 <= score1 && score2 <= score3) {
        return (score1 + score3)/2;
    } else {
        return (score1 + score2)/2;
    }
}

double calculate_mean(int i, double *arr) {
    double total = 0.0;
    int count = i;
    while (i >= 0) {
        total += arr[i];
        i--;
    }
    return total / count;
}

double calculate_var(int mean, double *arr, int count) {
    int i = count;
    double total = 0.0;
    while (count >= 0) {
        total += ((mean - arr[count])*(mean - arr[count]));
        count--;
    }
    return total / i;
}

int main(void) {
    /* code */
    int sn;
    double score1, score2, score3;

    double judge1[10];
    double judge2[10];
    double judge3[10];


    int record;
    double max=0.0;
    int i=0;
    while ( 4 == scanf("%d %lg %lg %lg", &sn, &score1, &score2, &score3)) {
        judge1[i] = score1;
        judge2[i] = score2;
        judge3[i] = score3;

        if (final_score(score1, score2, score3)>=max) {
            record = sn;
            max = final_score(score1, score2, score3);
        }
        i++;
    }
    printf("Max score is record: %d, with score: %.2f \n", record, max);

    double mean1, mean2, mean3;
    mean1 = calculate_mean(i, judge1);
    mean2 = calculate_mean(i, judge2);
    mean3 = calculate_mean(i, judge3);
    
    double var1, var2, var3;
    var1 = calculate_var(mean1, judge1, i);
    var2 = calculate_var(mean2, judge2, i);
    var3 = calculate_var(mean3, judge3, i);
    
    printf("\tAverage SD: \n");
    printf("judge1  : %5.2f %5.2f\n", mean1, sqrt(var1));
    printf("judge2  : %5.2f %5.2f\n", mean2, sqrt(var2));
    printf("judge3  : %5.2f %5.2f\n", mean3, sqrt(var3));

}
