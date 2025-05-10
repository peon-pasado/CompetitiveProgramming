#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int a[maxn];

int main() {
    int t;
    cin>>t;
    while (t--) {
        int n, m;
        cin>>n>>m;
        for (int i=1; i<=n; ++i) a[i] = -1;
        for (int i=1; i<=m; ++i) {
            int x, y;
            cin>>x>>y;
            a[x] = y;
        }
        a[n+1] = 0;
        int sum = 0;
        for (int i=n; i>=3; --i) {
            a[i] = max(a[i], a[i+1]);
            sum += a[i];
        }
        int num = 0;
        if (a[1] != -1 && a[2] != -1) num = a[1] + a[2];
        else if (a[1] != -1) num = 2 * a[1];
        else if (a[2] != -1) num = 100 + a[2];
        else num = 200;
        int den = num + sum;
        int g = __gcd(num, den);
        cout << num/g << '/' << den/g << '\n';
    }
    return 0;
}