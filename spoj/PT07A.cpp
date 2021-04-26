/**
 * @author Miguel Mini
 * @tag hackenbush 
 * @idea
 *      - we can compress special 
 *      nodes.
 * 
 *      - according to Colon principle
 *      we can close special nodes by
 *      paths, and resulting loops can
 *      be replace for 1-edge-tree.
 *  
 *      - find grundy number of each 
 *      tree in the forest and solve
 *      with sprague-grundy theorem.
 * 
 * @complexity O(n)
 */ 


#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int dp[maxn];
int s[maxn];
vector<int> g[maxn];

void calc(int x, int p=0) {
	dp[x] = 0;
	for (int v : g[x]) {
		if (v==p) continue;
		calc(v, x);
		s[x] |= s[v];
		dp[x] ^= s[v] ^ (1 - s[v] + dp[v]);
	}
	dp[x] ^= s[x];
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", s+i);
		}
		for (int i = 1; i <= n; ++i) {
			g[i].clear();
		}
		for (int i = 0; i < n-1; ++i) {
			int a, b;
			scanf("%d%d", &a, &b);
			g[a].push_back(b);
			g[b].push_back(a);
		}
		int ans = 0;
		for (int i = 1; i <= n; ++i) {
			if (s[i] == 1) {
				calc(i);
				ans = dp[i] ^ 1;
				break;
			}
		}
		puts(ans ? "1" : "0");
	}
	return 0;
}