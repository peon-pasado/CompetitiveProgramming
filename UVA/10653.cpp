#include <bits/stdc++.h>
using namespace std;

const int maxn = 1005;
int A[maxn][maxn];
int d[maxn][maxn];
bool vis[maxn][maxn];
int n, m;

bool valid(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m;
}

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, 1, -1};

void bfs(int x, int y) {
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			vis[i][j] = 0;
			
    vis[x][y] = 1;
    d[x][y] = 0;
    queue<pair<int, int>> Q;
    Q.push({x, y});
    while (!Q.empty()) {
        auto u = Q.front(); Q.pop();
        for (int i = 0; i < 4; ++i) {
        	int vx = dx[i] + u.first;
        	int vy = dy[i] + u.second;
        	if (!valid(vx, vy)) continue;
        	if (A[vx][vy]) continue;
            if (vis[vx][vy] == 0) {
                vis[vx][vy] = 1;
                d[vx][vy] = d[u.first][u.second] + 1;
                Q.push({vx, vy});
            }
        }
    }
}


int main() {
	while (cin >> n >> m, n + m) {
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				A[i][j] = 0;
		int k;
		cin >> k;
		for (int i = 0; i < k; ++i) {
			int r, c; 
			cin >> r >> c;
			for (int j = 0; j < c; ++j) {
				int b;
				cin >> b;
				A[r][b] = 1;
			}
		}
		int xs, ys;
		cin >> xs >> ys;
		int xf, yf;
		cin >> xf >> yf;
		bfs(xs, ys);
		cout << d[xf][yf] << '\n';
	}
	return 0;
}
