#include <bits/stdc++.h>
using namespace std;
const int maxN = 12;
int mat[maxN][maxN];
bool vis[maxN][maxN];

int dx[] = {1, 1, -1, -1, 2, 2, -2, -2};
int dy[] = {2, -2, 2, -2, -1, 1, -1, 1};

bool valid(int x, int y) {
	return x >= 0 and y >= 0 and x < 10 and y < 10 and mat[x][y] == 1;
}

int backtrack(int x, int y) {
	int ans = 0;
	vis[x][y] = 1;
	for (int i = 0; i < 8; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (not valid(nx, ny)) continue;
		if (not vis[nx][ny]) {
			ans = max(ans, backtrack(nx, ny));
		}
	}
	vis[x][y] = 0;
	return ans + 1;
}

int main() {
	int n;
	int cnt = 1;
	while (cin >> n, n) {
		memset(mat, 0, sizeof mat);
		int casillas = 0;
		int x, y;
		for (int i = 0; i < n; ++i) {
			int l, r;
			cin >> l >> r;
			if (i == 0) {
				x = 0, y = l;
			}	
			casillas += r;
			for (int j = 0; j < r; ++j) mat[i][j+l] = 1;
		}
		cout << "Case "<< cnt++ << ", "; 
		int noVisitadas = casillas - backtrack(x, y);
		if (noVisitadas == 1) cout << "1 square can not be reached." << endl;
		else cout << noVisitadas << " squares can not be reached." << endl;
	}
	return 0;
}