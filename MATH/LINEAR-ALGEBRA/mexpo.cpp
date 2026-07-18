#include "template.h"
#include "linalg.h"

/**
 * @brief Fast matrix exponentiation.
 * 
 * This is useful for solving linear recurrences very quickly.
 * For example, exponentiating [[1 1][1 0]] to find Fibonacci numbers.
 * 
 * @param a The matrix to be exponentiated
 * @param x The exponent
 * @param m The modulo 
 * 
 * @return a**x % m
 */
Matrix<ll> mexpo(Matrix<ll> a, ll x, ll m = MOD) {
    Matrix<ll> out = Matrix<ll>::identity(a.rows());
    while(x) {
        if(x&1) out = (out*a)%m;
        a = (a*a)%m;
        x >>= 1;
    }
    return out;
}