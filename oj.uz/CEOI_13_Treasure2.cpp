/**
 *  @author Miguel Mini
 *  @tag inclusion-exclusion principle, dp
 *  @idea
 *      - we can find acc[x][y] = \sum_{i=1}^{x} \sum_{j=1}^{y} mat[i][j]
 *      in 1 + n^2 - (n/2 + di) * (n/2 + dj) where di + dj is the manhathan 
 *      distance to the center, this sum ensures n^2 + 7/16 n^4 energy.
 *
**/

#include <bits/stdc++.h>
#include "treasure.h"
using namespace std;

const int maxn = 110;
int acc[maxn][maxn];
bool mat[maxn][maxn];

void findTreasure(int n) {
    for (int i = n; i >= 1; --i) {
        for (int j = n; j >= 1; --j) {
            if (i <= n/2 && j <= n/2) 
                acc[i][j] = countTreasure(i+1, j+1, n, n) - acc[n][n] + acc[i][n] + acc[n][j];
            else if (i <= n/2) 
                acc[i][j] = acc[n][j] - countTreasure(i+1, 1, n, j);
            else if (j <= n/2) 
                acc[i][j] = acc[i][n] - countTreasure(1, j+1, i, n);
            else 
                acc[i][j] = countTreasure(1, 1, i, j);
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            mat[i][j] = acc[i][j] - acc[i-1][j] - acc[i][j-1] + acc[i-1][j-1];
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (mat[i][j]) Report(i, j);
        }
    }
}
