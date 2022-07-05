#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
double chisquare(const unsigned long long int *v, unsigned long long int value_expected){
    int i, s_value;
    double x_square;
    for (i=0; i<10; i++) {
        s_value = (int)v[i] - (int)value_expected;
        x_square = x_square + (double)(s_value*s_value)/(int)value_expected;
    }
    printf("chi-square: %f\n", x_square);
    return 0;
}
 
int main () {
 
    clock_t start = clock();
    int num;
    int n = 100000000;
    unsigned long long int v[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    unsigned long long int expected_frequency = n/10;
    time_t t;
   
    srand((unsigned) time(&t));
 
    for(unsigned long long int i = 0 ; i < n ; i++ ) {
        num = rand() % 10;
        v[num] = v[num]+1;
        //printf("%d\n", num);
    }
 
    chisquare(v, expected_frequency);
 
 
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
 
    printf("\nFunction rand() took %f seconds to execute \n", seconds);
   
    return(0);
}
