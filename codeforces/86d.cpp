#include <bits/stdc++.h>
using namespace std;

const int M = 2e5 + 5;
struct Query{
	int l, r, id;
} Q[M];
int a[M];
int n, sq, q;
long long now_ans;
long long ans[M];
int C[5*M];

bool cmp(const Query& P, const Query& Q){
	return P.l / sq < Q.l / sq or P.l / sq == Q.l / sq and P.r < Q.r;
}

void add(int pos){
	now_ans += 1ll * (2*C[a[pos]] + 1) * a[pos];
	C[a[pos]] += 1;
}

void remove(int pos){
	now_ans -= 1ll * (2*C[a[pos]] - 1) * a[pos];
	C[a[pos]] -= 1;
}

void solve_mo(){

	sq = sqrt(n) + 1;
	
	sort(Q, Q+q, cmp);
	int l = 0, r = 0;
	for(int i = 0; i < q; ++i){
		while(r <= Q[i].r) add(r++);
		while(l < Q[i].l) remove(l++);
		while(l > Q[i].l) add(--l);
		while(r > Q[i].r + 1) remove(--r);

		ans[Q[i].id] = now_ans;
	}
}




int main(){

	scanf("%d %d", &n, &q);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a+i);

	for(int i = 0; i < q; ++i){
		int l, r;
		scanf("%d %d",  &l, &r);
		
		Q[i] = {l, r, i};
	}	
	
	solve_mo();
	for(int i = 0; i < q; ++i)
		printf("%lld\n", ans[i]);

	return 0;
}