#include <bits/stdc++.h>
using namespace std;

const int maxn = 3010;
using ll = long long;
const ll inf = 1e9;
ll a[maxn];
int dp[maxn];
ll f[maxn];

int main() {
    int n;
    cin>>n;
    for (int i=1; i<=n; ++i) {
        cin>>a[i];
        a[i] += a[i-1];
    }
    for (int i=1; i<=n; ++i) {
        for (int j=i; j>=1; --j) {
            if (a[i] >= f[j-1]) {
                dp[i] = dp[j-1] + 1;
                f[i] = 2 * a[i] - a[j-1];
                break;
            }
        }
    }
    cout << dp[n] << '\n';
    return 0;
}