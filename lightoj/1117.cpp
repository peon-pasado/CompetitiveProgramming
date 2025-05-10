#include <bits/stdc++.h>
using namespace std;

unsigned int n;
int m;
int c[20];

unsigned int calc(int a, int b) {
    a /= __gcd(a, b);
    if (a * 1ll * b > n) return n + 1;
    return a * b;
}

int bt(int pos, int N) {
    if (pos == m) return n / N;
    return bt(pos+1, N) - bt(pos+1, calc(N, c[pos]));
}


int main() {
    int t;
    cin>>t;
    for (int tc=1; tc<=t; ++tc) {
        cout<<"Case " << tc << ": ";
        cin>>n>>m;
        for (int i=0; i<m; ++i) cin>>c[i];
        cout << bt(0, 1) << '\n';
    }
    return 0;
}