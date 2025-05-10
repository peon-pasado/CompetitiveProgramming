#include <bits/stdc++.h>
using namespace std;
const int maxN = 105;
string mat[maxN];
int n, m;

const int dx[] = {-1, -1, -1, 1, 1, 1, 0, 0};
const int dy[] = {-1, 1, 0, -1, 1, 0, -1, 1};

bool valid(int x, int y) {
	return min(x, y) >= 0 and x < n and y < m;
}

bool vis[maxN][maxN];
void dfs(int x, int y) {
	vis[x][y] = 1;
	for (int k = 0; k < 8; ++k) {
		int nx = x + dx[k];
		int ny = y + dy[k];
		if (not valid(nx, ny)) continue;
		if (not vis[nx][ny] and mat[nx][ny] == '#') {
			dfs(nx, ny);
		}
	}
}

int main() {
	while (cin >> n >> m) {
		for (int i = 0; i < n; ++i) {
			cin >> mat[i];
		}
		memset(vis, 0, sizeof vis);
		int c = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (not vis[i][j] and mat[i][j] == '#') {
					dfs(i, j);
					c += 1;
				}
			}
		}	
		cout << c << endl;
	}
	return 0;
}