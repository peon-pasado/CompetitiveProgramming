/**
 * @author Miguel Mini
 * @tag dp, bridges, bitmask, subsets
 * @idea
 *      - we need build a path with 
 *      only bridge edges.
 * 
 *      - we can make a path in a set
 *      from 1 to x with avoiding multiple
 *      edges from this set to x.
 *      
 *      - or, divide in two sets and 
 *      make a unique path from x to that set.
 * 
 * @complexity O(3^n x n^2), we can reduce
 * to O(3^n x n) with O(3^n) of memory.
 */ 
#include <bits/stdc++.h>
using namespace std;

const int maxn = 15;
int g[20][20];
int cst[1<<15][20];
int dp[1<<15][20];

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        g[a][b] = g[b][a] = c;
    }
    for (int s = 0; s < 1<<n; ++s)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (s & (1<<j))
                    cst[s][i] += g[j][i];
    memset(dp, 63, sizeof dp);   
    dp[1][0] = 0;
    for (int s = 0; s < 1<<n; ++s)
        for (int x = 0; x < n; ++x)
            if ((s&(1<<x)) && x < 1e9) {
                for (int y = 0; y < n; ++y)
                    if (g[x][y] && (~s&(1<<y))) {
                        dp[s|(1<<y)][y] = min(dp[s|(1<<y)][y], dp[s][x] + cst[s][y] - g[x][y]);
                    }
                int super = s ^ ((1<<n)-1);
                for (int s2 = super; s2 > 0; s2 = (s2-1)&super) {
                    int add = 0;
                    for (int y = 0; y < n; ++y) if (s2&(1<<y)) add += cst[s^(1<<x)][y];
                    dp[s|s2][x] = min(dp[s|s2][x], dp[s][x] + add);
                }
            }
    cout << dp[(1<<n)-1][n-1] << '\n';
    return 0;
}