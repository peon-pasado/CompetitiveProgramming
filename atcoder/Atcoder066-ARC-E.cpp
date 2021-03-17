/**
 * @author Miguel Mini
 * @tag dp, parenthesis
 * @idea
 *      - note that we need start parenthesis
 *      only before of sign -.
 *
 *      - we can make dp(position, number_of_open_parenthesis)
 *
 *      - note that we only need at most 2 open parenthesis
 *      because if it is not negative element to right, 2
 *      parenthesis is optimum.
 *
 * @complexity O(n)
 */

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int maxn = 1e5 + 10;
const ll inf = 1e18;
ll dp[maxn][3];
int n;

int main() {
    cin >> n;
    vector<ll> a(n);
    cin >> a[0];
    for (int i = 1; i < n; ++i) {
        char sign;
        cin >> sign;
        cin >> a[i];
        if (sign == '-') a[i] *= -1;
    }
    dp[0][0] = a[0];
    dp[0][1] = -inf;
    dp[0][2] = -inf;
    for (int i = 1; i < n; ++i) {
        if (a[i] > 0) {
            dp[i][0] = max(dp[i-1][0] + a[i], dp[i-1][1] - a[i]);
            dp[i][1] = max(dp[i-1][1] - a[i], dp[i-1][2] + a[i]);
            dp[i][2] = dp[i-1][2] + a[i];
        } else {
            dp[i][0] = dp[i-1][0] + a[i];
            dp[i][1] = max(dp[i-1][0] + a[i], dp[i-1][1] - a[i]);
            dp[i][2] = max(dp[i-1][2] + a[i], dp[i-1][1] - a[i]);
        }
    }
    cout << *max_element(dp[n-1], dp[n-1]+3) << '\n';
    return 0;
}