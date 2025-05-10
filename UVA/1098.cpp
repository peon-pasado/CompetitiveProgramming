#include <bits/stdc++.h>
using namespace std;

const int maxn = 8;
bool vis[maxn][maxn];
int r[5], c[5], t[5]; 
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
int n, m;

int dfs(int i, int j, int l) {
	for (int k=1; k<=4; ++k) {
		if (l <= t[k] && l + abs(r[k]-i) + abs(c[k]-j) > t[k]) return 0;
		if (l != t[k] && i == r[k] && j == c[k]) return 0;
	}
	if (i==0&&j==1) return 1;
	int sum[2] = {0};
	for (int k=0; k<4; ++k) {
		int ni = i + dx[k];
		int nj = j + dy[k];
		if (ni<0||nj<0) {
			sum[k/2] += 1;
			continue;
		}
		if (ni>=n||nj>=m) {
			sum[k/2] += 1;
			continue;
		}
		sum[k/2] += vis[ni][nj];
	}
	if (sum[0] == 2 && sum[1] == 0) return 0;
	if (sum[1] == 2 && sum[0] == 0) return 0;
	vis[i][j] = 1;
	int ans=0;
	for (int k=0; k<4; ++k) {
		int ni = i + dx[k];
		int nj = j + dy[k];
		if (ni<0||nj<0) continue;
		if (ni>=n||nj>=m) continue;
		if (vis[ni][nj]) continue;
 		ans += dfs(ni, nj, l+1);
	}
	vis[i][j] = 0;
	return ans;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int tc=1;
	while (cin>>n>>m, n+m) {
		for (int i=1; i<=3; ++i) {
			int x, y;
			cin>>x>>y;
			r[i]=x; c[i]=y;
			t[i]=i*n*m/4;
		}
		r[4]=0; c[4]=1;
		t[4]= n * m;
		cout << "Case " << tc++ << ": " << dfs(0, 0, 1) << '\n';
	}
	return 0;
}