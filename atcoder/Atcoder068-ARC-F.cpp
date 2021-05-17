/**
 * @author Miguel Mini
 * @tag dp, combinatorics
 * @idea
 *      - we can make 
 *  
 *          dp(pos, res, t):
 *              processing numbers greater
 *              than pos, and res number free
 *              with last added is free or not.
 * 
 *      - if t == 1:
 * 
 *          put pos+1 free: dp(pos+1, res-1, 0) + dp(pos+1, res-1, 1)
 * 
 *      - if t == 0:
 * 
 *          put pos+1 from first sequence (there are 2 decreasing sequence,
 *          first sequence have high priority).
 * 
 *              dp(pos+1, res, 0) + dp(pos+1, res, 1)
 *  
 *          put maximum free in second sequence:
 *      
 *              dp(pos, res+1, 0)
 * 
 *       - we make answer up to n-k-1 with
 * 
 *          dp(1, n-k, 0) + dp(1, n-k, 1)
 * 
 *        and finally last n-k elements can be
 *        taked in 2^{n-k-1} ways.
 * 
 * @complexity O(n^2)
 */ 

#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int maxn = 2010;
int n, k;
bool vis[maxn][maxn][2];
int memo[maxn][maxn][2];

int dp(int pos, int res, int t) {
    if (res > n) return 0;
    if (res < 0) return 0;
    if (pos == n) return res == 0 && t == 0;
    if (vis[pos][res][t]) return memo[pos][res][t];
    vis[pos][res][t] = 1;
    int& ans = memo[pos][res][t] = dp(pos+1, res-t, 0) + dp(pos+1, res-t, 1);
    if (ans >= mod) ans -= mod;
    if (t == 0) ans += dp(pos, res+1, 0);
    if (ans >= mod) ans -= mod;
    return ans;
}

int main() {
    cin >> n >> k;
    int ans = dp(1, n-k, 0) + dp(1, n-k, 1);
    if (ans >= mod) ans -= mod;
    for (int i = 0; i < n-k-1; ++i) {
        ans += ans;
        if (ans >= mod) ans -= mod;
    }
    cout << ans << endl;
    return 0;
}