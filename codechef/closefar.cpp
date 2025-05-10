#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;
const int N = 1e5 + 5;
int E[N<<1];
int R[N];
struct node{
	int l, r, min, max;
	node() {}
	node(int _l, int _r, int _min, int _max) : l(_l), r(_r), min(_min), max(_max) {}
} st[N<<1];
vector<int> adj[N];
int A[N];
bool C[N];
int n, m, sq;
int ST[N<<1][18];
int S[N<<1];
int H[N];
int L[N];
int ans[N];
int inv[N];
int Inv[N];
int B[N];
int T, Y;

void dfs(int x, int p, int h){

	E[T] = Inv[x];
	L[x] = T++;
	inv[x] = Y;
	H[x] = h;	
	S[Y++] = x;

	for(int v : adj[x])
		if(v != p){
			dfs(v, x, h+1);
			S[Y++] = x;
		}

	E[T] = Inv[x];
	R[x] = T++;
}

void init(){

	dfs(1, 0, 0);
	
	for(int i = 0; i < 2*n; ++i)
		ST[i][0] = S[i];

	for(int k = 1; k < 17; ++k)
		for(int i = 0; i + (1<<k) <= 2*n; ++i){
			int u = ST[i][k-1];
			int v = ST[i+(1<<k-1)][k-1];
		
			ST[i][k] = H[u] < H[v] ? u : v;
		}			
}


int LCA(int x, int y){
	x = inv[x];
	y = inv[y];

	if(x > y) swap(x, y);
	int r = 31 - __builtin_clz(y - x + 1);
	int u = ST[x][r];	
	int v = ST[y-(1<<r)+1][r];
	return H[u] < H[v] ? u : v;
}

node nil = node(inf, inf, inf, -inf);
node merge(node r, node s){
	if(r.l == inf) return s;
	if(s.l == inf) return r;
	
	node p = r;
	node q = s;

	if(p.l > q.l) swap(p, q);

	return {p.l, q.r, min(p.min, min(q.min, B[q.l] - B[p.r])), max(p.max, max(q.max, B[q.r] - B[p.l]))};
}

void build(){
  for (int i = 0; i <= 2*n; ++i) st[i] = nil;
}

void update(int p) { 
	C[p] ^= 1;
	
	if(C[p]) st[p + n] = {p, p, inf, -inf};
  	else st[p + n] = nil;
	
	for (p += n; p >>= 1;) st[p] = merge(st[p<<1], st[p<<1|1]);
}

node query(int l, int r) {  // sum on interval [l, r)
  node resl = nil;
  node resr = nil;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) resl = merge(resl, st[l++]);
    if (r&1) resr = merge(st[--r], resr);
  }
  return merge(resl, resr);
}

struct Query{
	int l, r, k, id, type;
	bool operator<(const Query& p){
		return l / sq < p.l / sq or l/sq == p.l/sq and r < p.r;
	}
} Q[N];



void mo(){
	sq = sqrt(n);
	sort(Q, Q+m);
	int l=0,r=0;
	for(int i = 0; i < m; ++i){
		while(r <= Q[i].r) update(E[r++]);
		while(l < Q[i].l) update(E[l++]);
		while(l > Q[i].l) update(E[--l]);
		while(r > Q[i].r + 1) update(E[--r]);
	
		if(~Q[i].k) update(E[Q[i].k]);
		if(Q[i].type) ans[Q[i].id] = query(0, n).max;
		else ans[Q[i].id] = query(0, n).min;
		if(~Q[i].k) update(E[Q[i].k]);
	}
}


int main(){

	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", A+i);

	vector<pair<int, int>> order(n);
	for(int i = 1; i <= n; ++i)
		order[i-1] = {A[i], i};
	
	sort(order.begin(), order.end());
	for(int i = 0; i < n; ++i){
		Inv[order[i].second] = i;
		B[i] = order[i].first;
	}	

	for(int i = 1; i < n; ++i){
		int u, v;
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	init();
	build();

	scanf("%d", &m);
	for(int i = 0; i < m; ++i){
		getchar();
		int x, y;
		bool c = getchar() == 'F';
		scanf("%d %d", &x, &y);
			
		int _lca = LCA(x, y);
		if(L[x] > L[y])	swap(x, y);

		if(x == _lca) Q[i] = {L[x], L[y], -1, i, c};
		else Q[i] = {R[x], L[y], L[_lca], i, c};
	}

	mo();

	for(int i = 0; i < m; ++i)
		printf("%d\n", ans[i]);

	return 0;
}