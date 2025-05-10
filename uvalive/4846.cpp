#include<bits/stdc++.h>
using namespace::std;

const int N = 2000 + 5;

int n;
int len;
int X[N];
int Y[N];
int R[N];
int in[N];
int comp[N];
bool vis[N];
stack<int> S;
vector<int> G[2][N];

void DFS(int u, int id){
	vis[u] = true;
	for(int v : G[id][u]){
		if(vis[v]) continue;
		DFS(v, id);
	}
	if(id == 0) S.emplace(u);
	else comp[u] = len;
}

void get_scc(){
	for(int i = 0; i < n; i++) vis[i] = false;
	for(int i = 0; i < n; i++){
		if(vis[i]) continue;
		DFS(i, 0);
	}
	for(int i = 0; i < n; i++) vis[i] = false;
	len = 0;
	while(!S.empty()){
		int u = S.top(); S.pop();
		if(vis[u]) continue;
		DFS(u, 1);
		len += 1;
	}
	for(int i = 0; i < len; i++) in[i] = 0;
	for(int i = 0; i < n; i++){
		for(int v : G[0][i]){
			if(comp[v] == comp[i]) continue;
			in[comp[v]] = 1;
		}
	}
}

bool inside(int a, int b, int c, int d, int x, int y){
	return a <= x and x <= b and c <= y and y <= d;
}

int solve(){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(i == j) continue;
			if(inside(X[i] - R[i], X[i] + R[i], Y[i] - R[i], Y[i] + R[i], X[j], Y[j])){
				G[0][i].emplace_back(j);
				G[1][j].emplace_back(i);
			}
		}
	}
	get_scc();
	return len - accumulate(in, in + len, 0);
}

void clear(){
	for(int i = 0; i < n; i++) G[0][i].clear(), G[1][i].clear();
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i = 0; i < n; i++){
			scanf("%d %d %d", X + i, Y + i, R + i);
			X[i] <<= 1;
			Y[i] <<= 1;
		}
		printf("%d\n", solve());
		if(t) clear();
	}
	return 0;
}