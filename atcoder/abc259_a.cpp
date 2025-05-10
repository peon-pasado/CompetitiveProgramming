#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, x, t, d;
    cin>>n>>m>>x>>t>>d;
    n = min(n, x);
    int r = max(1, t - n * d);
    cout << r + min(x, m) * d << '\n';
    return 0;
}