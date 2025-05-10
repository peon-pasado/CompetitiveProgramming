#include <bits/stdc++.h>
using namespace std;

struct Rectangle {
	int x1, y1, x2, y2;
	
	Rectangle intercept(Rectangle p) {
		return {max(x1, p.x1), max(y1, p.y1), min(x2, p.x2), min(y2, p.y2)};
	}
	
	friend istream& operator>>(istream& is, Rectangle& r) {
		return is >> r.x1 >> r.y1 >> r.x2 >> r.y2;
	}
	
	friend ostream& operator<<(ostream& os, Rectangle r) {
    return os << r.x1 << " " << r.y1 << " " << r.x2 << " " << r.y2;
	}
};

const int maxn = 210;
int mat[maxn][maxn];
bool vis[maxn][maxn];

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		vector<Rectangle> p(n);
		for (int i = 0; i < n; ++i) {
			cin >> p[i];
		}
 		vector<int> X, Y;
 		for (int i = 0; i < n; ++i) {
 			X.push_back(p[i].x1); 
 			X.push_back(p[i].x2);
 			Y.push_back(p[i].y1);
 			Y.push_back(p[i].y2);
 		}
 		sort(X.begin(), X.end());
 		sort(Y.begin(), Y.end());
 		X.erase(unique(X.begin(), X.end()), X.end());
 		Y.erase(unique(Y.begin(), Y.end()), Y.end());
 		vector<int> lx(X.size()), ly(Y.size());
 		for (int i = 0; i + 1 < X.size(); ++i) {
 			lx[i] = X[i+1] - X[i];
 		}
 		for (int i = 0; i + 1 < Y.size(); ++i) {
 			ly[i] = Y[i+1] - Y[i];
 		}
 		for (int i = 0; i < n; ++i) {
 			p[i].x1 = lower_bound(X.begin(), X.end(), p[i].x1) - X.begin();
 			p[i].x2 = lower_bound(X.begin(), X.end(), p[i].x2) - X.begin();
 			p[i].y1 = lower_bound(Y.begin(), Y.end(), p[i].y1) - Y.begin();
 			p[i].y2 = lower_bound(Y.begin(), Y.end(), p[i].y2) - Y.begin();
 		}
 		memset(mat, 0, sizeof mat);
 		for (int i = 0; i < n; ++i) {
 			mat[p[i].x1][p[i].y1] += 1;
 			mat[p[i].x1][p[i].y2] -= 1;
 			mat[p[i].x2][p[i].y1] -= 1;
 			mat[p[i].x2][p[i].y2] += 1;
 		}
 		for (int i = 0; i < X.size(); ++i) {
 			for (int j = 0; j < Y.size(); ++j) {
 				if (j > 0) mat[i][j] += mat[i][j-1];
 			}	
 		}
 		for (int i = 0; i < X.size(); ++i) {
 			for (int j = 0; j < Y.size(); ++j) {
 				if (i > 0) mat[i][j] += mat[i-1][j];
 			}	
 		}
 		memset(vis, 0, sizeof vis);
 		int dx[] = {-1, 1, 0, 0};
 		int dy[] = {0, 0, -1, 1};
 		function<int(int, int)> dfs = [&](int x, int y)->int {
 			vis[x][y] = 1;
 			int ans = lx[x] * ly[y];
 			for (int i = 0; i < 4; ++i) {
 				int nx = x + dx[i];
 				int ny = y + dy[i];
 				if (min(nx, ny) >= 0 && nx < X.size() && ny < Y.size()) {
 					if (!vis[nx][ny] && mat[nx][ny]) {
 						ans += dfs(nx, ny);
 					}
 				}
 			}
 			return ans;
 		};
 		cout << dfs(p[0].x1, p[0].y1) << '\n';
 		if (t) cout << '\n';
	}
	return 0;
}