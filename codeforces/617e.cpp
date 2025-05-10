#include <bits/stdc++.h>
using namespace std;

const int N = 1E6 + 2;
int C[1<<20];
int a[N];
int D[1<<20];
int ac[N];
int sq, n, m, k;
long long ans[N];

struct Query{
	int l, r, id;
	
	bool operator<(const Query& p){
		return l/sq < p.l/sq or l/sq == p.l/sq and r < p.r;
	}
} Q[N];

long long now_ans = 0;

void addR(int pos){
	C[ac[pos-1]] += 1;
	now_ans += C[ac[pos]^k];
	D[ac[pos]] += 1;
}

void addL(int pos){
	D[ac[pos]] += 1;
	now_ans += D[ac[pos-1]^k];
	C[ac[pos-1]] += 1;
}

void removeR(int pos){
	now_ans -= C[ac[pos]^k];
	C[ac[pos-1]] -= 1;
	D[ac[pos]] -= 1;
}

void removeL(int pos){
	now_ans -= D[ac[pos-1]^k];
	D[ac[pos]] -= 1;
	C[ac[pos-1]] -= 1;
}



void mo(){

	sq = sqrt(n);
	sort(Q, Q+m);
	
	for(int i = 1; i <= n; ++i)
		ac[i] = ac[i-1] ^ a[i];	

	int l = 1, r = 1;
	for(int i = 0; i < m; ++i){
		while(r <= Q[i].r) addR(r++);
		while(l < Q[i].l) removeL(l++);
		while(l > Q[i].l) addL(--l);
		while(r > Q[i].r + 1) removeR(--r);

		ans[Q[i].id] = now_ans;
	}
}



int main(){

	scanf("%d %d %d", &n, &m, &k);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a+i);

	for(int i = 0; i < m; ++i){
		int l, r;
		scanf("%d %d", &l, &r);
		Q[i] = {l, r, i};
	}

	mo();

	for(int i = 0; i < m; ++i)
		printf("%lld\n", ans[i]);

	return 0;
}