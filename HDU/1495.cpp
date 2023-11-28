/**
 * @idea:
 * 
 *  - given the constraints, dont exist solution
 *  if s(mod 2) = 1 o s/2 (need value) dont divide
 *  gcd(n, m). 
 * 
 *  - suppose that we want reach xn + ym, we can
 *  make (x, y) = (1, 0) and (0, 1). 
 * 
 *  - if n > m: (1, -1) ... (1, -2) ... n - qm = (n%m)
 *  
 *  - m % (n % m) ... 
 * 
 *  - until gcd(n, m). 
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 101;
int d[N][N];
int s, n, m;
void dfs(int x[3], int L) {
    d[x[1]][x[2]] = L;
    for (int i=0; i<2; ++i)
        for (int j=i+1; j<3; ++j)
            if (x[i] == s/2 && x[j] == s/2) return; 
    int y[3] = {s - x[0], n - x[1], m - x[2]};
    for (int i=0; i<3; ++i)
        for (int j=0; j<3; ++j) if (i != j) {
            int m = min(x[i], y[j]);
            x[i] -= m;
            x[j] += m;
            if (d[x[1]][x[2]] > L + 1) {
                dfs(x, L+1);
            }
            x[j] -= m;
            x[i] += m;
        }
}

int main() {
    while (cin>>s>>n>>m, s) {
        if (s % 2 == 1 || (s/2) % __gcd(n, m) != 0) {
            cout << "NO" << '\n';
            continue;
        } 
        for (int i=0; i<=s; ++i)
            for (int j=0; j<=s; ++j)
                d[i][j] = 1e9;
        
        int x[3] = {s, 0, 0};
        dfs(x, 0);

        int ans = 1e9;
        ans = min(ans, d[s/2][s/2]);
        ans = min(ans, d[0][s/2]);
        ans = min(ans, d[s/2][0]);
        cout << ans << '\n';
    }
    return 0;
}