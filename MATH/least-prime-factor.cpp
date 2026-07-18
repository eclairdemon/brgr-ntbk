#include "template.h"

/**
 * @brief Find the least prime factor of all numbers from 1 to n.
 * 
 * This is virtually identical to the Sieve of Eratosthenes,
 * except that instead of a boolean array we store the least prime factor array lpf,
 * and now p being prime is equivalent to lpf[p] == p.
 * To sieve up to the kth prime, use the bound p_k < k(ln k + ln ln k).
 * 
 * @param n The highest number in the sieve.
 */
vll lpf(ll n) {
    vll lpf(n+1);
    iota(all(lpf),0);

    lpf[2] = 2;
    for(int i = 2; i*i <= n; i++) {
        if(lpf[i] == i) {
            for(int j = i*i; j <= n; j += i) {
                lpf[j] = 0;
            }
        }
    }

    return lpf;
}