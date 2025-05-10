#include <bits/stdc++.h>
using namespace std;

const int maxn = 40;
using ll = long long;
ll w[maxn];
ll msk[maxn];
ll dp[1<<(maxn/2)];
int n, m;

ll bt(ll mask) {
    if (mask == 0) return 0;
    if (mask < (1<<(n/2)) && dp[mask]) return dp[mask];  

    ll sum = 0;
    ll tmp = 0;
    for (int i=0; i<n; ++i) {
        if (~mask & (1ll<<i)) continue;
        if ((msk[i] & mask) == 0) {
            sum += w[i];
            tmp |= (1ll<<i);
        } 
    }

    ll ans = -1e18;
    if (sum > 0) {
        ans = max(ans, sum + bt(mask ^ tmp));
    } else {
        int x = 63 - __builtin_clzll(mask);
        ans = max(ans, bt(mask ^ (1ll<<x)));
        ans = max(ans, bt((mask ^ (1ll<<x)) & ~msk[x]) + w[x]);
    }
    
    if (mask < (1<<(n/2))) {
        dp[mask] = ans;
    }   
    return ans;
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin>>t;
    while (t--) {
        cin>>n>>m;
        for (int i=0; i<n; ++i) {
            cin>>w[i];
            msk[i] = 0;
        }
        for (int i=0; i<m; ++i) {
            int u, v;
            cin>>u>>v;
            msk[u] |= 1ll<<v;
            msk[v] |= 1ll<<u;
        }
        for (int i=0; i<(1<<(n/2)); ++i) dp[i] = 0;
        int q;
        cin>>q;
        while (q--) {
            int k;
            cin>>k;
            ll v_set = 0;
            for (int i=0; i<k; ++i) {
                int v;
                cin>>v;
                v_set |= (1ll<<v);
            }
            cout << bt(v_set) << '\n';
        }
        if (t > 0) cout << '\n';
    }
    return 0;
}