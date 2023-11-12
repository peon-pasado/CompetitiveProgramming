#include <bits/stdc++.h>
using namespace std;

const int N = 101;
bool vis[N][N][N];
int d[N][N];
int s[3];
void dfs(int x[3], int L) {
    d[x[1]][x[2]] = L;
    if (x[1] == s[0]/2 && x[2] == s[0]/2) return;

    for (int i=0; i<3; ++i)
        for (int j=0; j<3; ++j) if (i != j) {
            int m = min(x[i], x[j]);
            x[i] -= m;
            x[j] += m;
        }
}

int main() {
    while (cin>>s>>n>>m, s) {
        if (s % 2 == 1 || s/2 % __gcd(n, n) != 0) {
            cout << "NO" << '\n';
        } 
        for (int i=0; i<=n; ++i)
            for (int j=0; j<= m; ++j)
                d[i][j] = 1e9;
        
    }
    return 0;
}