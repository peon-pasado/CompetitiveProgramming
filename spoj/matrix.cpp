#include <bits/stdc++.h>
using namespace std;
const int maxN = 210;
int mat[maxN][maxN], cnt[maxN][maxN], sum[maxN][maxN];
int best[maxN][maxN];

int main() {
	int t, n, m;
	cin >> t;
	while (t--) {
		cin >> n >> m;
		memset(mat, 0, sizeof mat);
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				cin >> mat[i][j];
				if (mat[i][j] == 0) mat[i][j] = -1;
			}
		}
		memset(sum, 0, sizeof sum);
		for (int i = n; i >= 1; --i) {
			for (int j = 1; j <= m; ++j) {
				sum[i][j] = sum[i+1][j] + mat[i][j];
			}
		}
		for (int i = 1; i <= m; ++i)
			for (int j = 1; j <= m; ++j) {
				best[i][j] = -1e9;
				cnt[i][j] = 0;
			}
		int w = -1e9, s = 0;
		for (int i = 1; i <= n; ++i) {
			for (int l = 1; l <= m; ++l) {
				int acc = 0;
				for (int r = l; r <= m; ++r) {
					acc += mat[i][r];
					if (l == r) continue;
					int temp = best[l][r] - sum[i][l] - sum[i][r] + acc;
					if (temp > w) {
						w = temp;
						s = cnt[l][r];
					} else if (temp == w) {
						s += cnt[l][r];
					}
				}
			}
			for (int l = 1; l <= m; ++l) {
				int acc = 0;
				for (int r = l; r <= m; ++r) {
					acc += mat[i][r];
					int temp = acc + sum[i+1][l] + sum[i+1][r];
					if (temp > best[l][r]) {
						best[l][r] = temp;
						cnt[l][r] = 1;
					} else if (temp == best[l][r]) {
						cnt[l][r] += 1;
					}
				}
			}
		}
		for (int i = 1; i <= n; ++i)
			for (int l = 1; l <= m; ++l) {
				int acc = 0;
				for (int r = l; r <= m; ++r) {
					acc += mat[i][r];
					if (l == r) continue;
					if (acc > w) {
						w = acc;
						s = 1;
					} else if (acc == w) {
						s += 1;
					}
				}
			}
		for (int i = 1; i <= m; ++i) 
			for (int l = 1; l <= n; ++l) {
				int acc = 0;			
				for (int r = l; r <= n; ++r) {
					acc += mat[r][i];
					if (l == r) continue;
					if (acc > w) {
						w = acc;
						s = 1;
					} else if (acc == w) {
						s += 1;
					}
				}
			}

		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j) 
				if (mat[i][j] > w) {
					w = mat[i][j];	
					s = 1;
				} else if (mat[i][j] == w) {
					s += 1;
				}
		cout << w << " " << s << endl;
	}
	return 0;
}