#include <stdio.h>
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
 
void multiply_with_carry(unsigned long long int seed, unsigned long long int n){
    unsigned long long int x = seed;
    unsigned long long int num = 0;
    unsigned long long int v[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    unsigned long long int expected_frequency = n/10;
 
    for (unsigned long long int i=0; i<n; i++){
        // x = a * (x && [2^32 - 1] + (x >> 32))
        x = 4294957665 * (x & 4294967295) + (x >> 32);
        num = x%10;
        v[num] = v[num]+1;
        //printf("Freq de %llu: %llu \n", i, num);
    }
    chisquare(v, expected_frequency);
}
 
int main(){
 
    clock_t start = clock();
    unsigned long long int seed = time(NULL);
 
    multiply_with_carry(seed, 100000000);
 
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
 
    printf("\nFunction multiply_with_carry() took %f seconds to execute \n", seconds);
 
    return 0;
}
