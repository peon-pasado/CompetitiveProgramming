/**
 * @author Miguel Mini
 * @tag math, geometry
 * @idea
 *      - if a set s have convex
 *      hull size equal to m, then
 *      every superset of the convex
 *      hull of s is added one time.
 * 
 *      - on the other hand, each set
 *      is added one time if its convex
 *      hull is non-degenerated.
 * 
 *      - answer is number of sets with
 *      non-degenerated convex hull.
 * 
 * @complexity O(n^3)
 */ 

#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;

int main() {
    int n;
    cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }
    vector<int> pot(n+1);
    pot[0] = 1;
    for (int i = 1; i <= n; ++i) {
        pot[i] = (2 * pot[i-1]) % mod;
    }
    for (int i = 0; i <= n; ++i) {
        pot[i] -= i+1;
        if (pot[i] < 0) pot[i] += mod;
    }
    int ans = pot[n];
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            int cnt = 0;
            for (int k = 0; k < n; ++k) {
                bool p = (x[j]-x[i])*(y[k]-y[i])==(y[j]-y[i])*(x[k]-x[i]);
                if (p && (k < i || k > j)) {
                    cnt = 0;
                    break;
                } else cnt += p;
            }
            ans -= pot[cnt];
            if (ans < 0) ans += mod;
        }
    }
    cout << ans << '\n';
    return 0;
}