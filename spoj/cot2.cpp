#include <bits/stdc++.h>
using namespace std;

const int N = 4E4 + 4;
const int M = 1e5 + 5;
int B[N<<1];
int vis[N], ans[M];
int S[N];
int E[N];
int ST[N<<1][18];
int T;
vector<int> adj[N];
int now_ans;
int n, q, sq;
int W[N];
pair<int, int> W_aux[N];
int inv[N];
int H[N];
int ET[N<<1];
int C[N];
int CC;


struct Query{
	int x, y;
} Q[M];

struct Range{
	int l, r, k, id;

	bool operator<(const Range& p){
		return l/sq < p.l/sq or l/sq == p.l/sq and r < p.r;
	}	
} R[M];



void dfs(int x, int p, int h){
	S[x] = T++;
	ET[CC] = x;
	H[x] = h;
	inv[x] = CC++;

	for(int v : adj[x])
		if(v != p){
			dfs(v, x, h+1);
			ET[CC++] = x;
		}

	E[x] = T++;
}

void init_lca(){

	for(int i = 0; i < 2*n; ++i)
		ST[i][0] = ET[i];
		
	for(int k = 1; k <= 17; ++k)
		for(int i = 0; i + (1<<k) <= 2*n; ++i){
			int u = ST[i][k-1], v = ST[i+(1<<k-1)][k-1];
			ST[i][k] = H[u] < H[v] ? u : v;
		}	
}

int LCA(int x, int y){
	x = inv[x];
	y = inv[y];	
	
	if(x > y) swap(x, y);
	int r = 31 - __builtin_clz(y - x + 1);

	int u = ST[x][r], v = ST[y-(1<<r)+1][r];	
	return H[u] < H[v] ? u : v;
}


void input(){

	scanf("%d %d", &n, &q);

	for(int i = 1; i <= n; ++i){
		int w;
		scanf("%d", &w);
		W_aux[i-1] = {w, i};
	}

	sort(W_aux, W_aux+n);

	int inv = 0;
	W[W_aux[0].second] = 0;
	for(int i = 1; i < n; ++i){
		if(W_aux[i].first != W_aux[i-1].first) inv += 1;
		W[W_aux[i].second] = inv;	
	}

	for(int i = 1; i < n; ++i){
		int u, v;
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	for(int i = 0; i < q; ++i){
		int x, y;
		scanf("%d %d", &x, &y);

		Q[i] = {x, y};
	}
}

int rm(int x){
	C[x] -= 1;
	if(C[x] == 0) now_ans -= 1;
}

int ad(int x){
	C[x] += 1;
	if(C[x] == 1) now_ans += 1;
}


void remove(int x){
	int val = B[x];
	vis[val] -= 1;
	
	if(vis[val] == 1) ad(W[val]);
	else rm(W[val]);
}

void add(int x){
	int val = B[x];

	vis[val] += 1;	
	
	if(vis[val] == 1) ad(W[val]);
	else rm(W[val]);
}


void solve(){
	dfs(1, 0, 0);
	init_lca();

	sq = sqrt(n) + 1;
	for(int i = 1; i <= n; ++i)
		B[S[i]] = B[E[i]] = i;

	for(int i = 0; i < q; ++i){
		int p = LCA(Q[i].x, Q[i].y);	
		
		if(S[Q[i].x] > S[Q[i].y]) swap(Q[i].x, Q[i].y);
		
		if(p == Q[i].x) R[i] = {S[p], S[Q[i].y], -1, i};
		else R[i] = {E[Q[i].x], S[Q[i].y], S[p], i};
	}

	sort(R, R+q);
	int l = 0, r = 0;
	for(int i = 0; i < q; ++i){	

		while(r <= R[i].r) add(r++);
		while(l < R[i].l) remove(l++);
		while(l > R[i].l) add(--l);
		while(r > R[i].r + 1) remove(--r);

		if(~R[i].k) add(R[i].k);		

		ans[R[i].id] = now_ans;

		if(~R[i].k) remove(R[i].k);
	}
}

void print(){
	for(int i = 0; i < q; ++i)
		printf("%d\n", ans[i]);
}



int main(){

	input();
	solve();
	print();

	return 0;
}