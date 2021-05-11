/**
 * @author Miguel Mini
 * @tag dp, greedy
 * @idea
 *      - we can make dp(node, k) 
 *      where k is number of nodes
 *      with equal color to node color
 *      and dp is minimum weight sum of 
 *      the other color.
 * 
 *      - yes, we can minimize minimum
 *      sum of the other color and fill 
 *      the rest with an ancestor.
 * 
 * @complexity O(5000n)
 */ 
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1010;
int p[maxn], x[maxn];
int dp[maxn][2][maxn * 5];
int b[maxn];
bool deg[maxn];

int main() {
    int n;
    cin >> n;
    for (int i = 2; i <= n; ++i) {
        cin >> p[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> x[i];
    }
    memset(dp, 63, sizeof dp);
    for (int i = 1; i <= n; ++i) {
        dp[i][0][0] = 0;
    }
    for (int i = n; i >= 1; --i) {
        b[i] = *min_element(dp[i][deg[i]], dp[i][deg[i]] + x[i] + 1);
        if (b[i] >= 1e8) {
            cout << "IMPOSSIBLE"<< endl;
            exit(0);
        }
        if (i == 1) break;
        auto& m0 = dp[p[i]][deg[p[i]]], &m1 = dp[p[i]][deg[p[i]]^1];
        for (int k = 5000; k >= 0; --k) {
            m1[k] = 1e9;
            if (k - b[i] >= 0)
                m1[k] = min(m1[k], m0[k-b[i]] + x[i]);
            if (k - x[i] >= 0)
                m1[k] = min(m1[k], m0[k-x[i]] + b[i]);
        }
        deg[p[i]] ^= 1;
    }
    cout << "POSSIBLE" << endl;
    return 0;
}