/**
 * @idea Use manhatan relaxation to prune. 
**/


#include <iostream>
#include <cstring>
using namespace std;

bool vis[31][31][31];
char s[31][31][31];
int d[30][30][30];
int n, m, p;
int sx=-1, sy=-1, sz=-1;
int fx=-1, fy=-1, fz=-1;
int dx[] = {0, 0, 0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0, 0, 0};
int dz[] = {0, 0, -1, 1, 0, 0};


bool check(int x, int y, int z) {
    return x >= 0 && y >= 0 && z >= 0 && x < n && y < m && z < p && s[x][y][z] != '#';
}

void bt(int x, int y, int z, int t) {
    d[x][y][z] = t;
    if (x == fx && y == fy && z == fz) return;
    if (abs(x-fx)+abs(y-fy)+abs(z-fz)+t >= d[fx][fy][fz]) return;
    vis[x][y][z] = 1;
    int ans = 0;
    for (int i=0; i<6; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        int nz = z + dz[i];
        if (check(nx, ny, nz) && !vis[nx][ny][nz] && d[nx][ny][nz] > t + 1) {
            bt(nx, ny, nz, t+1);
        }
    }
    vis[x][y][z] = 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    while (cin>>n>>m>>p, n+m+p!=0) {
        for (int i=0; i<n; ++i) {
            for (int j=0; j<m; ++j) {
                cin>>s[i][j];
                for (int k=0; k<p; ++k) {
                    if (s[i][j][k] == 'S') {
                        sx=i; sy=j; sz=k;
                    }
                    if (s[i][j][k] == 'E') {
                        fx=i; fy=j; fz=k;
                    }
                }
            }
        }
        memset(d, 1, sizeof d);
        bt(sx, sy, sz, 0);
        if (d[fx][fy][fz] <= 27000) cout << "Escaped in " << d[fx][fy][fz] << " minute(s)." << '\n';
        else cout << "Trapped!" << '\n';
    } 
    return 0;
}