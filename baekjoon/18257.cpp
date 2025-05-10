#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int maxn = 15;
const ll lim = 1e15;
ll v[maxn];
int k;
vector<pair<ll, int>> r;
void dfs(int pos, ll M, int t) {
    if (pos == k) {
        r.emplace_back(M, t);
        return;
    }   
    dfs(pos+1, M, t);
    ll g = __gcd(M, v[pos]);
    M /= g;
    if (M <= (lim + v[pos] - 1) / v[pos]) {
        dfs(pos+1, M * v[pos], t + 1);
    }
}   

ll count_p(ll x) {
    ll ans = 0;
    for (auto [w, c] : r) {
        ll temp = 0;
        if (c > 0) temp = x / w;
        if (c & 1) ans += c * temp;
        else ans -= c * temp; 
    }
    return ans;
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin>>t;
    while (t--) {
        ll n;
        cin>>k>>n;
        for (int i=0; i<k; ++i) {
            cin>>v[i];
        }
        r.clear();
        dfs(0, 1, 0);
        ll lo = 1, hi = lim;
        while (lo < hi) {
            ll mi = (lo + hi) / 2;
            if (count_p(mi) < n) lo = mi+1;
            else hi = mi;
        }
        cout << lo << '\n';
    }
    return 0;
}