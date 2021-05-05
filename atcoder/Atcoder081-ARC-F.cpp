/**
 * @author Miguel Mini
 * @tag dp, linear_algebra
 * @idea
 *      - we can transform every
 *      2x2 square with even
 *      number of characters '#'.
 *  
 *      - we can put a point in
 *      center of each square with
 *      odd number of '#'. 
 * 
 *      - rectangles cant include
 *      those points.
 * 
 *      - we can solve with simple dp
 *      in compressing form.
 * 
 * @complexity O(nm)
 */ 

#include <bits/stdc++.h>
using namespace std;

const int maxn = 2010;
char s[maxn][maxn];
int L[maxn][maxn];
int R[maxn][maxn];
int U[maxn][maxn];

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> (s[i] + 1);
        for (int j = 1; j <= m; ++j) {
            s[i][j] = s[i][j] == '#';
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            s[i][j] ^= s[i][j+1] ^ s[i+1][j] ^ s[i+1][j+1]; 
        }
    }
    int ans = max(n, m);
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) L[i][j] = s[i][j] ? 0 : L[i][j-1]+1;
        for (int j = m-1; j >= 1; --j) R[i][j] = s[i][j] ? 0 : R[i][j+1]+1;
    }
    for (int i = 0; i <= m; ++i) {
        L[0][i] = R[0][i] = 1e9;
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            if (s[i][j]) {
                U[i][j] = 0;
                L[i][j] = R[i][j] = 1e9;
            } else {
                U[i][j] = U[i-1][j]+1;
                L[i][j] = min(L[i][j], L[i-1][j]);
                R[i][j] = min(R[i][j], R[i-1][j]);
                ans = max(ans, (U[i][j]+1)*(L[i][j] + R[i][j]));
            }
        }
    }
    cout << ans << '\n';
    return 0;
}