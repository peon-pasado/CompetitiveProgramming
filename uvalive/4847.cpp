#include <bits/stdc++.h>
using namespace std;

const int maxn = 25;
int n;
int p[maxn];
int L[maxn], R[maxn];
int root = -1;

int insert(int& r, int v) {
    if (r == -1) r = v;
    else {
        if (v > r) p[insert(R[r], v)] = r;
        else p[insert(L[r], v)] = r; 
    }
    return r;
}

const int mod = 9999991; 
bool vis[1<<20];
int memo[1<<20];
int dp(int mask) {
    if (mask == (1<<n) - 1) return 1; 
    if (vis[mask]) return memo[mask];
    vis[mask] = 1;
    int& ans = memo[mask] = 0;
    for (int j = 0; j < n; ++j) {
        if (mask & (1<<j)) continue;
        if (mask & (1<<p[j])) {
            ans += dp(mask | (1<<j));
            if (ans >= mod) ans -= mod;
        }
    }
    return ans;
}

int main() {
    int t;
    cin>>t;
    while (t--) {
        cin>>n;
        memset(p, -1, sizeof p);
        root = -1;
        memset(L, -1, sizeof L);
        memset(R, -1, sizeof R);
        for (int i = 0; i < n; ++i) {
            int x;
            cin>>x;
            x--;
            insert(root, x);
        }      
        memset(vis, 0, sizeof vis); 
        cout << dp(1<<root) << '\n';
    }
    return 0;
}