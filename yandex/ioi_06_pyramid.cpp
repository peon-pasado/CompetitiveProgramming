=/**
 * @author Miguel Mini
 * @tag dp, min_queue
 * @idea
 *      - we can precompute with two min_queues, the minimum
 *      sum rectangle dxc for every matrix (a-c-1) x (b-d-1). 
 *
 *      - the answer is sum(i, j, i+a-1, j+b-1) - minimum(i+1, j+1, i+a-c-1, j+b-d-1)
**/
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1010;
int t[maxn][maxn];
int u[maxn][maxn];
int v[maxn][maxn];
int w[maxn][maxn];

int get(int x1, int y1, int x2, int y2) {
	return t[x2][y2] - t[x2][y1-1] - t[x1-1][y2] + t[x1-1][y1-1];
}

int main() {
	int n, m, a, b, c, d;
	scanf("%d%d%d%d%d%d", &m, &n, &b, &a, &d, &c);
	for (int i=1; i<=n; ++i) {
		for (int j=1; j<=m; ++j) {
			scanf("%d", t[i]+j);
			t[i][j] += t[i-1][j] + t[i][j-1] - t[i-1][j-1];
		}
	}
	for (int i=1; i<=n-c+1; ++i) {
		for (int j=1; j<=m-d+1; ++j) {
			u[i][j] = get(i, j, i+c-1, j+d-1);
		}
	}
	for (int i=1; i<=n; ++i) {
		deque<int> s;
		for (int j=m; j>=1; --j) {
			while (!s.empty() && s.back() - j + 1 > b - d - 1) s.pop_back();
			while (!s.empty() && u[i][s.front()] >= u[i][j]) s.pop_front();
			s.push_front(j);
			v[i][j] = u[i][s.back()];
		}
	}
	for (int j=1; j<=m; ++j) {
		deque<int> s;
		for (int i=n; i>=1; --i) {
			while (!s.empty() && s.back() - i + 1 > a - c - 1) s.pop_back();
			while (!s.empty() && v[s.front()][j] >= v[i][j]) s.pop_front();
			s.push_front(i);
			w[i][j] = v[s.back()][j];
		}
	}
	int ans = -1e9;
	int x, y;
	for (int i=1; i<=n-a+1; ++i) {
		for (int j=1; j<=m-b+1; ++j) {
			int sum = get(i, j, i+a-1, j+b-1) - w[i+1][j+1];
			if (sum > ans) {
				ans = sum;
				x = i; y = j;
			}
		}
	}
	int need = get(x, y, x+a-1, y+b-1) - ans;
	printf("%d %d\n", y, x);
	bool found = 0;
	for (int i = 1; i <= a-c-1; ++i) {
		for (int j = 1; j <= b-d-1; ++j) {
			if (found) break;
			if (u[x+i][y+j] == need) {
				found = 1;
				printf("%d %d\n", y+j, x+i);
			}
		}
	}
	return 0;
}
