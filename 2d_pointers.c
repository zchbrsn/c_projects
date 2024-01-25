#include <stdio.h>
#include <stdlib.h>

// Make a 2d array and fill with 1-100
// Access arrays using only pointer arithmetic and print all prime numbers
// prime number can be calculated by modulus of anything equals itself
// for (i = 2; i < len(array); i++) {
    // if num is divisible i, 

// Takes n and calculates primes up to n
int *sieve_of_eratosthenes(int n) {
    int *primes = malloc((n+1)* sizeof(int));

    if (n <= 2) {
        return primes;
    }

    return 0;

}


int main(void) {

    int *primes = sieve_of_eratosthenes(100);

    printf("Size %d\n", sizeof(primes));

    for (int i = 0; i < 100; i++) {
        printf("Prime: %d\n", *(primes+i));
    }
    free(primes);
}










    
        /*
        int nums[10][10] = {0};
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                nums[i][j] = i * 10 + j + 1;
            }
        }

        for (int i = 0; i < 100; i++) {
            printf("%d, ", *(*nums + i));
        }
        printf("");
        */
