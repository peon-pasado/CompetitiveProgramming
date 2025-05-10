#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6;
bool comp[maxn];
vector<int> prime;
void sieve(int n) {
    for (int i=2; i<n; ++i) {
        if (!comp[i]) {
            prime.push_back(i);
        }
        for (int p : prime) {
            if (p * i >= n) break;
            comp[p*i]=1;
            if (i%p==0) break;
        }
    }
}

vector<pair<long long, int>> f;
long long a, b;
int bt(int pos, long long n = 1) {
    if (n >= a / n) return 0;
    if (pos == f.size()) return n >= b;
    long long pp = 1;
    int ans = 0;
    for (int i=0; i<=f[pos].second; ++i) {
        ans += bt(pos+1, n * pp);
        pp *= f[pos].first;
    }
    return ans;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    sieve(maxn);
    int t;
    cin>>t;
    for (int tc=1; tc<=t; ++tc) {
        cin>>a>>b;
        long long n = a;
        f.clear();
        for (int p : prime) {
            if (1LL*p*p > n) break;
            if (n % p == 0) {
                int e = 0;
                while (n % p == 0) {
                    e += 1;
                    n /= p;
                }
                f.emplace_back(p, e);
            }
        }
        cout << "Case " << tc << ": ";
        if (n > 1) f.emplace_back(n, 1);
        cout << bt(0) << '\n';
    }
    return 0;
}