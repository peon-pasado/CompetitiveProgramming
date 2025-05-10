#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5 + 5;
int n, q;
int root;
int a[maxN];
vector<int> pos[maxN << 2];
vector<int> wt[maxN << 2][2];
int Left[maxN << 2], Right[maxN << 2]; 
int T = 0;
bool Terminal[maxN << 2];

int create(){
	return T++;
}

void build(int nx, int Min, int Max){
	
	if(Min == Max)
		return void(Terminal[nx] = 1);

	int lMax = Min, rMin = Max;
	Left[nx] = create();
	Right[nx] = create();

	int mid = Min + (Max - Min)/2;

	for(int v : pos[nx]){
		if(a[v] <= mid){
			lMax = max(lMax, a[v]);
			pos[Left[nx]].push_back(v);
		}
		else{
			rMin = min(rMin, a[v]);
			pos[Right[nx]].push_back(v);
		}

		wt[nx][0].push_back((int)pos[Left[nx]].size() - 1);
		wt[nx][1].push_back((int)pos[Right[nx]].size() - 1);
	}

	build(Left[nx], Min, lMax);
	build(Right[nx], rMin, Max);
}

void search (int nx, int k, int i, int l){
	if (Terminal[nx])
		return void(printf("%d\n", pos[nx].size() < l ? -1 : pos[nx][l-1]));

	int c = wt[nx][0][i] - max(0, wt[nx][0][0]) + 1;
	if (c >= k) search(Left[nx], k, wt[nx][0][i], l);
	else search(Right[nx], k - c, wt[nx][1][i], l);
}

void input(){
	scanf("%d %d", &n, &q);

	for(int i = 0; i < n; ++i)
		scanf("%d", a+i);
}

void solve_next_query(){
	int i, k, l;
	scanf("%d %d %d", &k, &i, &l);
	search(root, k, i, l);
}

void solve(){

	int Min = *min_element(a, a+n), Max = *max_element(a, a+n);
	root = create();

	pos[root].resize(n);
	for(int i = 0; i < n; ++i)
		pos[root][i] = i;	

	build(root, Min, Max);

	while(q--) solve_next_query();
}


int main(){

	input();
	solve();

	return 0;
}