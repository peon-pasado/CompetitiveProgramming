#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;
const int N = 1e5 + 5;
vector<int> adj[N];
vector<int> best[N];
int ans[N];
int H[N], inv[N], E[N<<1];
int T;
bool color[N];
int ST[N<<1][20];
vector<int> block;
int n, m, sq;

void add(int x, int w){
	best[x].push_back(w);			
	sort(best[x].begin(), best[x].end());
	if(best[x].size() > 2) best[x].pop_back();
}

void update_ans(int x, int d){
	ans[x] = min(ans[x], d);
}

int first = 1;
void dfs(int x, int p, int h){
	
	if(color[x])
		ans[x] = 0;
	
	if(first){
		H[x] = h;
		inv[x] = T;
		E[T++] = x;
	}
	
	for(int v : adj[x])
		if(v != p){
			dfs(v, x, h+1);

			if(ans[x] > ans[v] + 1)
				ans[x] = ans[v] + 1;

			add(x, ans[v] + 1);

			if(first)
				E[T++] = x;
		}
}

void dfs2(int x, int p){

	if(p){
		if(color[p]){
			update_ans(x, 1);
			add(x, 1);
		}
		else{
			if(best[p].size() == 2){
				if(best[p][0] == ans[x]){
					update_ans(x, best[p][1] + 1);
					add(x, best[p][1] + 1);
				}
				else{
					update_ans(x, best[p][0] + 1);
					add(x, best[p][0] + 1);
				}
			}
			else add(x, inf);
		}
	}

	for(int v : adj[x])
		if(v != p)
			dfs2(v, x);

}

void init(){

	for(int i = 1; i <= n; ++i)
		best[i].clear();
	for(int i = 1; i <= n; ++i)
		ans[i] = inf;
	
	dfs(1, 0, 0);
	dfs2(1, 0);

	if(first){
		for(int i = 0; i < 2*n; ++i)
			ST[i][0] = E[i];
	
		for(int k = 1; k <= 18; ++k)
			for(int i = 0; i + (1<<k) <= 2*n; ++i){
				int u = ST[i][k-1];
				int v = ST[i+(1<<k-1)][k-1];
				ST[i][k] = H[u] < H[v] ? u : v;
			}				

		first = 0;
	}

}

int LCA(int x, int y){
	x = inv[x];
	y = inv[y];

	if(x > y) swap(x, y);

	int r = 31 - __builtin_clz(y - x + 1);
	int u = ST[x][r];
	int v = ST[y - (1<<r) + 1][r];
	return H[u] < H[v] ? u : v;
}

int dist(int x, int y){
	return H[x] + H[y] - 2*H[LCA(x, y)];
}


int main(){
	
	scanf("%d %d", &n, &m);	
	
	for(int i = 1; i < n; ++i){
		int u, v;
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	color[1] = 1;

	sq = sqrt(10*n);
	for(int i = 0; i < m; ++i){
		if(i%sq == 0){
			init();
			block.clear();
		}
	
		int type, x;
		scanf("%d %d", &type, &x);
		if(type == 1){
			block.push_back(x);
			color[x] = 1;
		}
		else{
			int w = ans[x];

			for(int s : block)
				w = min(w, dist(s, x));

			printf("%d\n", w);
		}
	}

	return 0;
}