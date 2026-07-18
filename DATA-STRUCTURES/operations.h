#include "template.h"

#define sci static constexpr int

struct SUM { sci ID = 0; ll operator()(ll a, ll b) const { return a + b; }};
struct MIN { sci ID = LLONG_MAX; ll operator()(ll a, ll b) const { return min(a, b); }};
struct MAX { sci ID = LLONG_MIN; ll operator()(ll a, ll b) const { return max(a, b); }};
struct GCD { sci ID = 1; ll operator()(ll a, ll b) const { return __gcd(a,b); }};
struct XOR { sci ID = 0; ll operator()(ll a, ll b) const { return a^b; }};
