#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
vector<int> big[500], small;
int n, m, q;
int t, nb, sq;
struct Edge{int u, v;} edge[N];
struct Query{int l, r;} Q[N];
int ans[N];
int Rank[2][N], Id[2][N];
int Components[2];

bool cmp(int x, int y){
	return Q[x].r < Q[y].r;
}

void init_BigSmall(){
	sq = (int) sqrt(m + 0.);
	nb = m / sq + 1;

	small.clear();
	for(int i = 0; i < nb; ++i)
		big[i].clear();

	for(int i = 0; i < q; ++i)
		if(Q[i].r - Q[i].l + 1 < sq)
			small.push_back(i);
		else
			big[Q[i].l/sq].push_back(i);

	for(int i = 0; i < nb; ++i)
		if(not big[i].empty())
			sort(big[i].begin(), big[i].end(), cmp);	
}

void init_dsu(){
	for(int i = 1; i <= n; ++i)
		Id[0][i] = i, Rank[0][i] = 0;
	Components[0] = n;
}

int Get(int nx, int x){
	if(Id[nx][x] != x) return Id[nx][x] = Get(nx, Id[nx][x]);
	return Id[nx][x];
}

void Union(int nx, int x, int y){
	x = Get(nx, x);
	y = Get(nx, y);

	if(x == y) return;
	Components[nx] -= 1;

	if(Rank[nx][x] < Rank[nx][y]) swap(x, y);

	Id[nx][y] = x;
	Rank[nx][x] += Rank[nx][x] == Rank[nx][y];
}



void Big(){

	for(int i = 0; i < nb; ++i){
		
		if(big[i].empty()) continue;

		init_dsu();		

		int state = (i+1)*sq;
		int pos = state;

		for(int j = 0; j < big[i].size(); ++j){

			while(pos <= Q[big[i][j]].r){ 
				Union(0, edge[pos].u, edge[pos].v);
				pos += 1;
			}

			Components[1] = Components[0];

			for(int k = Q[big[i][j]].l; k < state; ++k){
				int u = edge[k].u;
				int v = edge[k].v;
			
				int pu = Get(0, u);
				int pv = Get(0, v);
	
				Id[1][u] = pu; Rank[1][u] = Rank[0][u];	
				Id[1][v] = pv; Rank[1][v] = Rank[0][v];

				Id[1][pu] = pu; Rank[1][pu] = Rank[0][pu];
				Id[1][pv] = pv; Rank[1][pv] = Rank[0][pv];
			}				

			for(int k = Q[big[i][j]].l; k < state; ++k)
				Union(1, edge[k].u, edge[k].v);
		
			ans[big[i][j]] = Components[1];
		}
	}
}

void Small(){

		init_dsu();		

		for(int i = 0; i < small.size(); ++i){
	
			Components[1] = Components[0];

			for(int k = Q[small[i]].l; k <= Q[small[i]].r; ++k){
				int u = edge[k].u;
				int v = edge[k].v;
			
				int pu = Get(0, u);
				int pv = Get(0, v);
	
				Id[1][u] = pu; Rank[1][u] = Rank[0][u];	
				Id[1][v] = pv; Rank[1][v] = Rank[0][v];

				Id[1][pu] = pu; Rank[1][pu] = Rank[0][pu];
				Id[1][pv] = pv; Rank[1][pv] = Rank[0][pv];
			}				

			for(int k = Q[small[i]].l; k <= Q[small[i]].r; ++k)
				Union(1, edge[k].u, edge[k].v);

			ans[small[i]] = Components[1];
		}

}

void input(){
	scanf("%d %d %d", &n, &m, &q);

	for(int i = 1; i <= m; ++i){
		int u, v;
		scanf("%d %d", &u, &v);
		edge[i] = {u, v};
	}

	for(int i = 0; i < q; ++i){
		int l, r;
		scanf("%d %d", &l, &r);
		Q[i] = {l, r};
	}
}


void solve(){
	init_BigSmall();
	Big();
	Small();

	for(int i = 0; i < q; ++i)
		printf("%d\n", ans[i]);
}


int main(){

	scanf("%d", &t);

	while(t--){
		input();
		solve();
	}

	return 0;
}