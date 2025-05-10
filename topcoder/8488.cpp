#include <bits/stdc++.h>
using namespace std;

class MarbleCollectionGame {
public:
	vector<int> dx, dy;
	bool vis[21][21];
	int n, m;
	vector<string> T;
	int ans[410], color[21][21];
	int sz[410];
	bool valid(int x, int y) {
		return x >= 0 and x < n and y >= 0 and y < m and T[x][y] != '#';
	}
	vector<pair<int, int>> order;
	void dfs(int x, int y) {
		vis[x][y] = 1;
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (not valid(nx, ny)) continue;
			if (vis[nx][ny]) continue;
			if (i == 2 and T[x][y] != 'U') continue;
			if (i == 3 and T[x][y] != 'L') continue;
			dfs(nx, ny);
		}
		order.push_back({x, y});
	}
	void dfs2(int x, int y, int c) {
		vis[x][y] = 1;
		color[x][y] = c;
		sz[c] += isdigit(T[x][y]) ? T[x][y] - '0' : 0;
		ans[color[x][y]] = sz[color[x][y]];
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (not valid(nx, ny)) continue;
			if (vis[nx][ny]) continue;
			if (i == 0 and T[nx][ny] != 'U') continue;
			if (i == 1 and T[nx][ny] != 'L') continue;
			dfs2(nx, ny, c);	
		}
	}
	int dfs3(int x, int y) {
		vis[x][y] = 1;
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (not valid(nx, ny)) continue;
			if (i == 2 and T[x][y] != 'U') continue;
			if (i == 3 and T[x][y] != 'L') continue;
			if (not vis[nx][ny]) dfs3(nx, ny);
			if (color[x][y] != color[nx][ny]) ans[color[x][y]] = max(ans[color[x][y]], ans[color[nx][ny]] + sz[color[x][y]]);
		}
	}
	int collectMarble(vector<string> board) {
		T = board;
		n = board.size();
		m = board[0].size();
		dx = {1, 0, -1, 0};
		dy = {0, 1, 0, -1};	
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (not vis[i][j] and valid(i, j)) {
					dfs(i, j);
				}			
			}
		}
		memset(sz, 0, sizeof sz);
		memset(vis, 0, sizeof vis);
		reverse(begin(order), end(order));
		int C = 1;
		for (auto e : order) {
			if (not vis[e.first][e.second] and valid(e.first, e.second)) {
				dfs2(e.first, e.second, C++);
			}
		}
		memset(vis, 0, sizeof vis);
		dfs3(0, 0);
		return ans[color[0][0]];
	}
};