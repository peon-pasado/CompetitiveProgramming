#include <bits/stdc++.h>
using namespace std;

const int maxn = 2010;
int a[maxn][maxn];
int x[maxn], y[maxn];
int N, M;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool valid(int x, int y) {
	return min(x, y) >= 0 && x < N && y < M;
}

bool vis[maxn][maxn];
void dfs(int x, int y) {
	vis[x][y] = 1;
	for (int i = 0; i < 4; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (!valid(nx, ny)) continue;
		if (vis[nx][ny]) continue;
		if (a[nx][ny] > 0) continue;
		dfs(nx, ny);
	}
}

int main() {
	int h, w;
	while (cin >> h >> w, h+w) {
		map<int, int> X, Y;
		X[0]; X[h];
		Y[0]; Y[w];
		int n;
		cin >> n;
		for (int i = 0; i < n; ++i) {
			int x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			x[2*i] = x1; x[2*i+1] = x2;
			y[2*i] = y1; y[2*i+1] = y2;
			X[x1]; X[x2];
			Y[y1]; Y[y2];
		}
		int tx = 0;
		for (auto& e : X) 
			e.second = tx++;
		int ty = 0;
		for (auto& e : Y) 
			e.second = ty++;
		N = X[h];
		M = Y[w];
		for (int i = 0; i < 2*n; ++i) {
			x[i] = X[x[i]];
			y[i] = Y[y[i]];
		}
		memset(a, 0, sizeof a);
		for (int i = 0; i < n; ++i) {
			a[x[2*i]][y[2*i]]++;
			a[x[2*i]][y[2*i+1]]--;
			a[x[2*i+1]][y[2*i]]--;
			a[x[2*i+1]][y[2*i+1]]++;
		}
		for (int i = 0; i < maxn; ++i)
			for (int j = 0; j < maxn; ++j)
				if (i > 0) a[i][j] += a[i-1][j];
		for (int i = 0; i < maxn; ++i)
			for (int j = 0; j < maxn; ++j)
				if (j > 0) a[i][j] += a[i][j-1];
		int c = 0;
		memset(vis, 0, sizeof vis);
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < M; ++j)
				if (!vis[i][j] && a[i][j] == 0)
					dfs(i, j), c++;
		cout << c << '\n';
	}
	return 0;
}