/**
 *  @name Miguel Mini
 *  @tag dp, sorting, negative_knapsack
 *  @idea
 *
 *        - use simple dp knapsack, but  
 *        query contribution has negative 
 *        weight and procesor negative profit.
 *
 *        - add elements in decreasing numbers 
 *        of f (in tie processors are big).
 *
 *        - discard elements with #procesors < 0.
**/


#include <bits/stdc++.h>
using namespace std;

const int maxn = 2010;
const int O = maxn * 51;
int n, m;
long long dp[maxn << 7];

struct Event {
    int c, f, v;    
    bool type;
} p[maxn * 2];

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> p[i].c >> p[i].f >> p[i].v;
        p[i].type = 0;
    }
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> p[n+i].c >> p[n+i].f >> p[n+i].v;
        p[n+i].type = 1;        
    }
    sort(p, p+n+m, [](auto a, auto b) {
        return a.f > b.f || (a.f == b.f && a.type < b.type);    
    });
    int t = max(n, m) * 50;
    for (int i = 0; i <= t; ++i) dp[O + i] = -1e18;
    dp[O + 0] = 0;
    for (int i = 0; i < n+m; ++i) {
        if (p[i].type) {
            for (int j = 0; j + p[i].c <= t; ++j) {
                dp[O + j] = max(dp[O + j], dp[O + j + p[i].c] + p[i].v);
            }
        } else {
            for (int j = t; j - p[i].c >= 0; --j) {
                dp[O + j] = max(dp[O + j], dp[O + j - p[i].c] - p[i].v);
            }
        }
    }
    long long ans = -1e18;
    for (int i = 0; i <= t; ++i) ans = max(ans, dp[i + O]);
    cout << ans << endl;
    return 0;
}
