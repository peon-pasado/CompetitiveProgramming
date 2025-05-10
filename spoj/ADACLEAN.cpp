#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll mod = 1e18 + 3;
const int maxn = 1e5 + 10;
ll B = 123456 + rand() % 1000;
char s[maxn];

ll add(ll a, ll b) {
    return (a+b)%mod;
}

ll mul(ll a, ll b) {
    ll r=0;
    while (b>0) {
        if (b&1) r=add(r, a);
        a=add(a, a);
        b>>=1;
    }
    return r;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, k;
        scanf("%d%d", &n, &k);
        scanf("%s", s);
        set<ll> hashes;
        ll h = s[0];
        ll bk = 1;
        for (int i=1; i<k; ++i) {
            h=add(mul(h, B), s[i]);
            bk = mul(bk, B);
        }
        hashes.insert(h);
        for (int i=1; i+k<=n; ++i) {
            h=add(mul(add(h, mod- mul(bk, s[i-1])), B), s[i+(k-1)]);
            hashes.insert(h);
        }
        printf("%d\n", (int)hashes.size());
    }
    return 0;
}