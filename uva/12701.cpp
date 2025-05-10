#include <bits/stdc++.h>
using namespace std;
const int M = 200;
const int N = 16;
int T[M];
double P[M];
int adj[N][N];
int Id[N][N];
double dp[M][1<<N];
bool vis[M][1<<N];
int nx, n;

void dfs(int root, int x, int p, int mask, double sum, int len){
	
	if(x != root){
		T[nx] = mask;
		P[nx] = sum / len;
		nx += 1;
	}

	for(int v = 0; v < n; ++v)
		if(v != p and adj[x][v])
			dfs(root, v, x, mask|(1<<Id[x][v]), sum + adj[x][v], len + 1);
}

double backtrack(int pos, int mask){
	if(pos == nx) return (mask+1 == (1<<n-1)) ? 0.0 : 1000000000.0;
	if(vis[pos][mask]) return dp[pos][mask];

	double ans = 1000000000.0;
	if((T[pos]&mask) == 0) ans = min(ans, backtrack(pos+1, mask|T[pos]) + P[pos]);	
	ans = min(ans, backtrack(pos+1, mask));
	vis[pos][mask] = 1;
	return dp[pos][mask] = ans;
}

int main(){

	while(scanf("%d", &n), n){
		
		memset(adj, 0, sizeof adj);

		for(int i = 0; i+1 < n; ++i){
			int a, b, c;
			scanf("%d %d %d", &a, &b, &c);
			adj[b][a] = adj[a][b] = c;
			Id[b][a] = Id[a][b] = i;
		}

		nx = 0;
		for(int i = 0; i < n; ++i)
			dfs(i, i, -1, 0, 0.0, 0);

		memset(vis, 0, sizeof vis);
		printf("%.4lf\n", backtrack(0, 0));
	}

	return 0;
}