#include "template.h"

/**
 * @brief Sieve of Eratosthenes.
 * 
 * Return an array isPrime such that isPrime[i] == 1 <==> i is prime.
 * This is done in O(n log log n) time using the Sieve of Eratosthenes.
 * To sieve up to the kth prime, use the bound p_k < k * (ln k + ln ln k).
 * 
 * @param n The highest number in the sieve.
 */
vec<bool> primeSieve(ll n) {
    vec<bool> isPrime(n+1,1);

    isPrime[0] = isPrime[1] = 0;
    for(int i = 2; i*i <= n; i++) {
        if(isPrime[i]) {
            for(int j = i*i; j <= n; j += i) {
                isPrime[j] = 0;
            }
        }
    }

    return isPrime;
}