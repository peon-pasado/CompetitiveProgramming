/**
 * @idea backtracking, heuristic
 * 
 *  - simule with backtracking
 * 
 *  - use manhatan prune
 * 
 *  - assume that path is a simple path.
 * 
**/

#include <iostream>
#include <cstring>
using namespace std;

const int N = 12;
int n, m, T;
char s[2][N][N];
int d[2][N][N];
bool vis[2][N][N];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool valid(int l, int x, int y) {
    return x>=0&&y>=0&&x<n&&y<m&&s[l][x][y]!='*';
}

void dfs(int l, int x, int y, int fl, int fx, int fy, int depth) {
    d[l][x][y] = depth;
    if (fl == l && fx == x && fy == y) return;
    if (depth + abs(x-fx) + abs(y-fy) > d[fl][fx][fy]) return;
    vis[l][x][y] = 1;
    if (s[l][x][y] == '#') {
        if (valid(1-l, x, y) && !vis[1-l][x][y] && d[1-l][x][y] > depth) {
            dfs(1-l, x, y, fl, fx, fy, depth);
        }
    } else {
        for (int i=0; i<4; ++i) {
            int nx=x+dx[i];
            int ny=y+dy[i];
            if (!valid(l, nx, ny)) continue;
            if (!vis[l][nx][ny] && d[l][nx][ny] > depth+1) {
                dfs(l, nx, ny, fl, fx, fy, depth+1);
            }
        }   
    }
    vis[l][x][y] = 0;
}

int main() {
    int t;
    cin>>t;
    while (t--) {
        cin>>n>>m>>T;
        int sx, sy, sz, fx, fy, fz;
        for (int k=0; k<2; ++k) {
            for (int i=0; i<n; ++i) {
                cin>>s[k][i];
                for (int j=0; j<m; ++j) {
                    if (s[k][i][j] == 'S') {
                        sx = k; sy = i; sz = j;
                    }
                    if (s[k][i][j] == 'P') {
                        fx = k; fy = i; fz = j;
                    }
                }
            }
        }
        memset(d, 1, sizeof d);
        dfs(sx, sy, sz, fx, fy, fz, 0);
        if (d[fx][fy][fz] <= T) cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }
    return 0;
}