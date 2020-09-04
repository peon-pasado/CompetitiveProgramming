/**
 * @author Miguel Mini
 * @tag dp, brute_force
 * @idea
 *      - we can use brute force with 
 *      next_permutation to obtain a 
 *      base complexity O(binom(n, n/2) * n)
 *      ~ O(2^n / 2sqrt(pi x n) x n)
 * 
 *      - finally we can preprocessing max values
 *      in ranges to obtain a simple dp knapsack
 *      O(m^2 n).
 * 
 * @complexity O(2^n x sqrt(n) x m^2) with low constant ~ 1/5.
**/ 

#include <bits/stdc++.h>
using namespace std;

const int maxn = 19;
int n, m, p, q;
int mat[maxn][maxn];
int arr[maxn][maxn];
int best[maxn][maxn];
bool vis[maxn][maxn];
int memo[maxn][maxn];

int main() {
    cin >> n >> m >> p >> q;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> mat[i][j];
        }
    }
    vector<int> ind(n);
    for (int i=0; i<=p; ++i) ind[i] = 1;
    sort(ind.begin(), ind.end());
    int ans = 1e9;
    while (1) {
        memset(arr, 0, sizeof arr);
        for (int i=0; i<m; ++i) {
            for (int j=0, k=0; j<n; ++j) {
                arr[i][k] += mat[j][i];
                k += ind[j];
            }
        }
        for (int i=0; i<m; ++i) {
            vector<int> sum(p+1);    
            for (int j=i; j<m; ++j) {
                for (int k=0; k<=p; ++k) {
                    sum[k] += arr[j][k];
                }
                best[i][j] = *max_element(sum.begin(), sum.end());
            }
        }
        const int inf = 1e9;
        memset(vis, 0, sizeof vis);
        function<int(int, int)> dp = [&](int pos, int k)->int {
            if (pos == m) return k == q+1 ? -inf : inf;
            if (vis[pos][k]) return memo[pos][k];
            int ans = 1e9;
            for (int i=pos; i<m; ++i) {
                ans = min(ans, max(best[pos][i], dp(i+1, k+1)));
            }
            vis[pos][k] = 1;
            return memo[pos][k] = ans;
        };
        ans = min(ans, dp(0, 0));
        if (!next_permutation(ind.begin(), ind.begin()+n-1)) break;
    }
    cout << ans << endl;
    return 0;
}
