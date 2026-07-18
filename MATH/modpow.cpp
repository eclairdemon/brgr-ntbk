#include "template.h"

/**
 * @brief Fast modular exponentiation.
 * 
 * Computes (a**x) % m in O(log x) time (m usually prime).
 * This is useful when dividing under modulo as it also allows us
 * to compute for the modular multiplicative inverse of a
 * using Fermat's little theorem (a**(p-1) = 1 mod p).
 * That function is also included here.
 * 
 * MODPOW:
 * @param a The base of the exponentiation.
 * @param x The exponent.
 * @param m The modulo.
 * 
 * @return (a**x) % m.
 * 
 * MODINV:
 * @param a The number to be inverted.
 * @param m The modulo. THIS MUST BE PRIME.
 * 
 * @return The modular multiplicative inverse of a.
 */
ll modpow(ll a, ll x, ll m = MOD) {
    ll out = 1;
    while(x) {
        if(x&1) out = (out*a)%m;
        a = (a*a)%m;
        x >>= 1;
    }
    return out;
}

ll modinv(ll a, ll m = MOD) {
    return modpow(a, m-2);
}