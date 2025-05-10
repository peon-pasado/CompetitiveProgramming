#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e4 + 10;
const int mod = 1e9 + 7;
int dp[2][maxn];

int add(int a, int b) {
    return a+b<mod?a+b:a+b-mod;
}

int main() {
    int n, c;
    cin>>n>>c;
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        int sum = 0;
        for (int j = 0; j < maxn; ++j) {
            sum = add(sum, dp[i&1^1][j]);
            if (j >= i) sum = add(sum, mod - dp[i&1^1][j-i]);
            dp[i&1][j] = sum;
        }
    }
    cout << dp[n&1][c] << '\n';
    return 0;
}