#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
long double h[maxn];
const long double euler = 0.57721566490153286060L;

int main() {
    h[1] = 1;
    for (int i=2; i<maxn; ++i) {
        h[i] = 1.L / i + h[i-1];
    }
    int t;
    cin>>t;
    cout.precision(10);
    cout<<fixed;
    for (int tc=1; tc<=t; ++tc) {
        int n;
        cin>>n;
        cout << "Case " << tc << ": ";
        if (n < maxn) cout << h[n] << '\n';
        else {
            long double ans = log(n) + 1.L/(2*n) + euler;
            cout << ans << '\n';
        }
    }
    return 0;
}