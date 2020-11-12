/**
 * @author Miguel Mini
 * @tag dp
 * @idea 
 *    - use dp approach dp[i][k]:
 *    rightmost index from 0-position
 *    such that cur position is s[i] == p[k]   
 *    - dp[i][0] = (s[i] == p[0]) ? i : -1;
 *      dp[i][k] = (s[i] == p[k]) ? max(dp[i-1][k-1], dp[i-1][k]) : -1;
 *    - note that dp[i][k] have atmost 1000 states.
**/

#include <bits/stdc++.h>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
using namespace std;
using ll = long long;

ll conta(int S, int s[], int P, int p[]) {
    vector<ll> dp(P, -1);
    vector<vector<ll>> pos(101); 
    for (int i = P-1; i >= 0; --i) {
        pos[p[i]].emplace_back(i);
    }
    ll ans = 0;
    for (int i = 0; i < S; ++i) {
        for (int k : pos[s[i]]) {
            if (k == 0) dp[k] = i;
            else {
                dp[k] = max(dp[k-1], dp[k]); 
            }
        }
        ans += dp[P-1] + 1;
    }
    return ans;
}
