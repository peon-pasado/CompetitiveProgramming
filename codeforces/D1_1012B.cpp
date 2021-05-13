    #include <bits/stdc++.h>
    using namespace std;
    const int MAXN = 2e5 + 10;
    vector<int> g[MAXN<<1];
    int n, m, q;
    bool vis[MAXN<<1];
    int dfs(int x) {
    	vis[x] = 1;
    	for (int v : g[x]) {
    		if (not vis[v]) {
    			dfs(v);
    		}
    	}
    }
    int main() {
    	scanf("%d%d%d", &n, &m, &q);
    	for (int i = 0; i < q; ++i) {
    		int x, y;
    		scanf("%d %d", &x, &y);
    		g[x].push_back(n+y);
    		g[y+n].push_back(x);
    	}
    	int ans = -1;
    	for (int i = 1; i <= n+m; ++i) {
    		if (not vis[i]) {
    			dfs(i);
    			ans += 1;
    		} 
    	}	
    	printf("%d\n", ans);
    	return 0;
    }