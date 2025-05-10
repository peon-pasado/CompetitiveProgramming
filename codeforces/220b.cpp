#include <bits/stdc++.h>
using namespace std;

const int N = 100002;
int n, nq;
int a[N];
int sq, nSet;
int ans[N];
int c[N];
struct quer{int l, r, id;} Q[N];
bool cmp(quer& p, quer& q){
	return p.l / sq < q.l / sq or p.l / sq == q.l / sq and p.r < q.r;
}

void add(int x){
	if(x >= N) return;
	c[x] += 1;
	
	if(c[x] == x) nSet += 1;
	if(c[x] == x+1) nSet -= 1;
}

void remove(int x){
	if(x >= N) return;

	c[x] -= 1;
	if(c[x] == x) nSet += 1;
	if(c[x] == x-1) nSet -= 1;
}

void mo(){
	for(int i = 0; i < nq; ++i) 
		Q[i].id = i;
	sq = (int) sqrt(n + 0.) + 1;   
	sort(Q, Q+nq, cmp);
	int l = 0, r = 0;
	for(int i = 0; i < nq; ++i){
		while(l > Q[i].l) add(a[--l]);
		while(r <= Q[i].r) add(a[r++]);
		while(l < Q[i].l) remove(a[l++]);
		while(r > Q[i].r + 1) remove(a[--r]);
		ans[Q[i].id] = nSet;
	}
}

int main(){

	scanf("%d %d", &n, &nq);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a+i);

	for(int i = 0; i < nq; ++i)
		scanf("%d %d", &Q[i].l, &Q[i].r);
	
	mo();

	for(int i = 0; i < nq; ++i)
		printf("%d\n", ans[i]);

	return 0;
}