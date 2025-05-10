#include <bits/stdc++.h>
using namespace std;
const int maxN = 2005;
bool vis[maxN];
int dis[maxN];
int n, k;
int a[maxN], b[maxN];

int bfs() {
	queue<int> Q;
	Q.push(0);
	vis[1000] = 1;
	dis[1000] = 0;
	while (not Q.empty()) {
		int q = Q.front(); Q.pop();
		for (int i = 0; i < k; ++i) {
			if (abs(q + a[i] - n) > 1000) continue;
			if (not vis[q + a[i] - n + 1000]) {
				vis[q + a[i] - n + 1000] = 1;
				dis[q + a[i] - n + 1000] = dis[q + 1000] + 1;
				Q.push(q + a[i] - n);
			} else if (q + a[i] == n) return dis[q + 1000] + 1;
		}
	}
	return -1;
}

int main() {
	scanf("%d %d", &n, &k);
	for (int i = 0; i < k; ++i) {
		int x;
		scanf("%d", &x);
		b[x] = 1;
	}
	k = 0;
	for (int i = 0; i < maxN; ++i) {
		if (b[i]) a[k++] = i;
	}
	printf("%d\n", bfs());
	return 0;
}