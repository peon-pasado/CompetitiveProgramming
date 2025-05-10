#include <bits/stdc++.h>
using namespace std;

const int maxn = 30;
bool vis[maxn][maxn][2];
bool memo[maxn][maxn][2];
string s;

bool dp(int l, int r, int f) {
    if (l > r) return 1;
    if (l == r) return f;
    if (vis[l][r][f]) return memo[l][r][f];
    vis[l][r][f] = 1;
    bool& ans = memo[l][r][f] = f ? dp(l+1, r, 0) : 0;
    for (int i = l+1; i <= r; ++i) {
        if (s[i] == s[l] && dp(l+1, i-1, 0) && dp(i, r, 1)) {
            ans = 1;
            break;
        }
    }
    return ans;
}

int main() {
    int t;
    cin>>t;
    while (t--) {
        cin>>s;
        memset(vis, 0, sizeof vis);
        //for (auto& c : s) c -= 'a'
        cout << dp(0, (int)s.size()-1, 0) << '\n';
    }
    return 0;
}