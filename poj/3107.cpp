#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
const int maxN = 1e5 + 10;
int t, n;
int sz[maxN], ans[maxN];
int head[maxN], prv[maxN], to[maxN];

void dfs(int x, int parent=0) {
	sz[x] = 1;
	ans[x] = 0;
	for (int e = head[x]; ~e; e = prv[e]) {
		int v = to[e];
		if (v == parent) continue;
		dfs(v, x);
		sz[x] += sz[v];
		ans[x] = max(ans[x], sz[v]);
	}
	ans[x] = max(ans[x], n - sz[x]);
}

int in() {
	int x = 0;
	register char c = getchar();
	while (c < '0') c = getchar();
	while (c >= '0') {
		x = (x<<3) + (x<<1) + c - '0';
		c = getchar();
	}
	return x;
}

void write(int n) {
	if (n == 0) putchar('0');
	else {
		register char num[8];
		int t = 0;
		while (n > 0) {
			num[t++] = n % 10;
			n /= 10;
		}
		for (int i = t-1; i >= 0; --i) putchar((char)num[i] + '0');
	}
} 
void addEdge(int i, int u, int v) {
	to[i] = v;
	prv[i] = head[u];
	head[u] = i;
}

int main() {
	t = 1;
	for (int _ = 1; _ <= t; ++_) {
		n = in();
		for (int i = 1; (i>>1) <= n; ++i) head[i] = -1;
		for (int i = 1; i <= n-1; ++i) {
			int u, v; 
			u = in();  v = in();
			addEdge(i<<1, u, v);
			addEdge(i<<1|1, v, u);
		}
		dfs(1);
		int f = n, cnt = 0;
		for (int i = 1; i <= n; ++i) {
			if (f > ans[i]) {
				f = ans[i];
			}
		}
		for (int i = 1; i <= n; ++i) if (ans[i] == f) write(i), putchar(' ');
		putchar('\n');
	}
	return 0;
}