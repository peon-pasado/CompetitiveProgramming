#include <bits/stdc++.h>
using namespace std;
const int maxN = 505;
int a[maxN][maxN];
int n;
int x, y;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};
char ch[] = {'U', 'L', 'D', 'R'};
int l = 1e9, r = 0;
int rowL[maxN], rowR[maxN];
int colL[maxN], colR[maxN];
bool vis[maxN][maxN];
bool valid(int x, int y) {
	return min(x, y) >= 1 and max(x, y) <= n;
}
string ans;
void add(int i, int j) {
	rowL[i] = min(j, rowL[i]);
 	rowR[i] = max(j, rowR[i]);
 	colL[j] = min(i, colL[j]);
 	colR[j] = max(i, colR[j]);
}

void dfs(int x, int y, int px, int py, bool ok) {
	vis[x][y] = 1;
	if (a[x][y] == 0) {
		a[x][y] = 1;
		ans += '1';
		add(x, y);
	}
	for (int i = 0; i < 4; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (not valid(nx, ny)) continue;
		bool possible = colL[y] <= nx and nx <= colR[y];
		possible = possible and rowL[x] <= ny and ny <= rowR[x]; 
		if (not vis[nx][ny] and possible) {
			ans += ch[i];
			dfs(nx, ny, x, y, ok);
			ans += ch[(i + 2) % 4];
		}
	}
	if (ok) ans += '2';
}

int main() {
	cin >> n >> x >> y;
	for (int i = 1; i <= n; ++i) rowL[i] = colL[i] = 1000;
 	for (int i = 1; i <= n; ++i) {
 		for (int j = 1; j <= n; ++j) {
 			cin >> a[i][j];
 			if (a[i][j]) {
 				add(i, j);
 			}
 		}
 	}
 	dfs(x, y, -1, -1, 0);
 	memset(vis, 0, sizeof vis);
 	dfs(x, y, -1, -1, 1);
 	for (int i = 1; i <= n; ++i) {
 		for (int j = 1; j <= n; ++j) {
 			if (a[i][j] and not vis[i][j]) {
 				return cout << "NO" << endl, 0;
 			}
 		}
 	}
 	puts("YES");
 	puts(ans.c_str());
	return 0;
}