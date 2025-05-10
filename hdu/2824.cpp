#include <bits/stdc++.h>
using namespace std;

const int maxn = 21000 + 2;
bitset<maxn> comp;
vector<int> prime;
using ll = long long;
ll sphi[maxn];

void sieve() {
    sphi[1] = 1;
    for (int i=2; i<maxn; ++i) {
        if (!comp[i]) {
            prime.push_back(i);
            sphi[i] = i-1;
        }
        for (int p : prime) {
            if (p * i >= maxn) break;
            comp[p * i] = 1;
            if (i % p == 0) {
                sphi[p * i] = p * sphi[i];
                break;
            } else {
                sphi[p * i] = (p - 1) * sphi[i];
            }
        }
    } 
    for (int i=2; i<maxn; ++i) {
        sphi[i] += sphi[i-1];
    }
}

unordered_map<int, ll> memo; 
ll calc(int n) {
    if (n < maxn) return sphi[n];
    if (memo.count(n)) return memo[n];
    ll ans = n *1LL * (n+1) / 2;
    for (int i = 2; i <= n; ++i) {
        int j = n / (n / i);
        ans -= (j - i + 1) * calc(n / i);
        i = j;
    }
    memo[n] = ans;
    return ans;
}


int main() {
    sieve();
    int l, r;
    while (cin>>l>>r)
        cout << calc(r) - calc(l-1) << '\n';
    return 0;
}