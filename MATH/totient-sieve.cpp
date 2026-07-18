#include "template.h"

/**
 * Compute phi(k) for all k = 1, 2, ..., n.
 * 
 * phi(k) is Euler's totient function, which computes
 * the number of integers less than k that are coprime
 * to k (i.e. have gcd 1). This is virtually identical
 * to the sieve of eratosthenes.
 * 
 * @param n The highest number in the sieve.
 */
vll phieve(ll n) {
    vll phi(n+1);
    iota(all(phi),0);
    for(int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
    return phi;
}