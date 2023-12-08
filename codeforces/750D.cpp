/**
 * @idea backtracking, memoization 
 * 
 *  - simule with backtracking.
 * 
 *  - note that every cell have n x 8 possibilities
 *  to explote. 
 * 
**/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 304;
int mid = 150;
bool mat[maxn][maxn];
int t[maxn];
int n;
int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
bool vis[maxn][maxn][30][8];
bool cell[maxn][maxn];

int sum = 0;
void bt(int x, int y, int i, int d) {
    if (i == n) return;
    if (vis[x][y][i][d]) return;
    vis[x][y][i][d] = 1;
    sum += !cell[x][y];
    cell[x][y] = 1;

    for (int j=0; j<t[i]; ++j) {
        bool& r = cell[x+j*dx[d]][y+j*dy[d]];
        sum += !r;
        r = 1;
    }

    bt(x + (t[i]-1)*dx[d] + dx[(d+1)%8], y + (t[i]-1)*dy[d] + dy[(d+1)%8], i+1, (d+1)%8);
    bt(x + (t[i]-1)*dx[d] + dx[(d+7)%8], y + (t[i]-1)*dy[d] + dy[(d+7)%8], i+1, (d+7)%8);
}


int main() {
    cin>>n;
    for (int i=0; i<n; ++i) {
        cin>>t[i];
    }
    bt(mid, mid, 0, 0);
    cout << sum << '\n';
    return 0;
}