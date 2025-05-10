#include <bits/stdc++.h>
using namespace std;

using u64 = uint64_t;
using u128 = __uint128_t;

u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

const int maxn = 1e6 + 10;
bool comp[maxn];
vector<int> prime;
void sieve() {
    for (int i = 2; i < maxn; ++i) {
        if (!comp[i]) {
            prime.push_back(i);
        }
        for (int p : prime) {
            if (p * i >= maxn) break;
            comp[p * i] = 1;
            if (i % p == 0) break;
        }
    }
}


int num_div(long long n) {
    int ans = 1;
    for (int d : prime) {
        if (n % d == 0) {
            int e = 0;
            while (n % d == 0) {n /= d; e += 1;}
            ans *= (e + 1);
        } 
    }
    if (n == 1) return ans;
    long long lo = 1, hi = 1e9;
    while (lo < hi) {
        long long mid = lo + (hi - lo + 1) / 2;
        if (mid * mid <= n) lo = mid;
        else hi = mid-1;
    }
    if (lo * lo == n) return ans * 3;
    for (auto b : {2, 3, 5, 7}) {
        if (binpower(b, n, n) != b) {
            return ans * 4;
        }
    }
    return ans * 2;
}

int main() {
    sieve();
    int t;
    scanf("%d", &t);
    while (t--) {
        long long n;
        scanf("%lld", &n);
        printf("%d\n", num_div(n));
    }
    return 0;
}