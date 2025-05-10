#include <bits/stdc++.h>
using namespace std;

const int N = 5002;
int a[N];
vector<int> adj[N];
int ans;
int n, k;

void dfs(int root, int x, int p, int l, int r){
    
    if(x != root and r - l >= k) ans += 1;
    
    for(int v : adj[x])
        if(v != p)
            dfs(root, v, x, min(a[v], l), max(a[v], r));
}


int main() {
	
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; ++i)
	    scanf("%d", a+i);
	
	for(int i = 1; i < n; ++i){
	    int x, y;
	    scanf("%d %d", &x, &y);
	    adj[x].push_back(y);
	    adj[y].push_back(x);
	}
	
	for(int i = 1; i <= n; ++i)
	    dfs(i, i, 0, a[i], a[i]);
	
	printf("%d\n", ans/2);
	
	return 0;
}
