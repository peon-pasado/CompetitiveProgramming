/**
 * @author Miguel Mini
 * @tag dp, multicase
 * @idea
 *      - can divide the problem in
 *      four patterns (from 1 to i):
 *
 *          1.- xxxxxxxxxxxxxxxx (dp[i][0])
 *
 *          2.- xxxxxxxxxxxxxx x (dp[i][1])
 *
 *          3.- xxxxx x  x  x  x (dp[i][2])
 *
 *          4.- xxxxxxx  x  x  x (dp[i][2])
 *
 *      - we can compute 3. and 4. by adding:
 *
 *          xxxxx__x (dp[i-3][0])
 *          xxx x__x (dp[i-3][1])
 *           x  x__x (dp[i-3][2])
 *
 *       - for two:
 *
 *          xxxxxx_1 (dp[i-2][0])
 *          xxxx1x_2 (dp[i-2][1])
 *          xx2x31_4 (dp[i-4][1])
 *          x32x41_5 (dp[i-4][2])
 *          xxx12x_3 (dp[i-2][2])
 *
 *        - for one:
 *
 *          xxxxx1x2 (dp[i-1][1])
 *          xxxx2x13 (dp[i-2][1])
 *          xxx2x314 (dp[i-3][1])
 *          xxxxxxx1 (dp[i-1][0])
 *          xxx24135 (dp[i-5][0])
 *          xx32x415 (dp[i-3][2])
 *          xxx23x14 (dp[i-2][2])
 *          x23x14x5 (dp[i-1][2])
 *          x32x41x5 (dp[i-1][2])
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
const int mod = 1e9 + 7;
using ll = long long;
ll dp[maxn][3];

int main() {
    int n, m;
    cin >> n >> m;
    if (m == 1) return cout << 1 << '\n', 0;
    dp[1][0] = 1;
    dp[2][0] = 1;
    for (int i = 3; i <= n; ++i) {
        dp[i][0] += dp[i-1][1]; //213
        if (m > 2) dp[i][0] += dp[i-2][1]; //3124
        if (m > 2) dp[i][0] += dp[i-3][1]; //31425
        dp[i][0] += dp[i-1][0]; //1
        if (m > 2) dp[i][0] += dp[max(0, i-5)][0]; //24135
        dp[i][0] += dp[i-3][2]; //__x415
        dp[i][0] += dp[i-2][2]; //__x14
        dp[i][0] += dp[i-1][2] + dp[i-1][2]; //__xn
        dp[i][0] %= mod;

        dp[i][1] += dp[i-2][0]; //_1
        if (m > 2) dp[i][1] += dp[i-2][1]; //21_3
        if (m > 2) dp[i][1] += dp[max(0, i-4)][1]; //3142_5
        dp[i][1] += dp[max(0, i-4)][2]; //43152_6
        dp[i][1] += dp[i-2][2]; //12x_3
        dp[i][1] %= mod;

        if (m > 2) {
            dp[i][2] += dp[i-3][0]; //__x
            dp[i][2] += dp[i-3][1]; //_1__2
            dp[i][2] += dp[i-3][2]; //__x__x
            dp[i][2] %= mod;
        }
    }
    cout << dp[n][0] << endl;
    return 0;
}