#include <bits/stdc++.h>
using namespace std;

const int N = 2E4 + 4;
int n, q;
int sq;
struct Query{
	int l, r, id;
	bool operator<(const Query& p){
		return l/sq < p.l/sq or l/sq == p.l/sq and r < p.r; 
	}
} Q[N];

int a[N];
int ft[N];
pair<int, int> A[N];
int ans[N];
int now_ans;

void update(int pos, int v){
	while(pos < N){
		ft[pos] += v;
		pos += pos&-pos;
	}
}

int query(int pos){
	int ans = 0;
	while(pos > 0){	
		ans += ft[pos];
		pos -= pos&-pos;
	}
	return ans;
}

void addR(int pos){
	int val = a[pos];
	now_ans += query(N-1) - query(val);
	update(val, 1);
}

void removeR(int pos){
	int val = a[pos];
	now_ans -= query(N-1) - query(val);	
	update(val, -1);
}

void addL(int pos){
	int val = a[pos];
	now_ans += query(val - 1);
	update(val, 1);
}

void removeL(int pos){
	int val = a[pos];
	now_ans -= query(val - 1);
	update(val, -1);
}



void solve_mo(){

	sq = sqrt(n);
	sort(Q, Q+q);

	int l = 1, r = 1;
	for(int i = 0; i < q; ++i){
		while(r <= Q[i].r) addR(r++);		
		while(l < Q[i].l) removeL(l++);
		while(l > Q[i].l) addL(--l);
		while(r > Q[i].r + 1) removeR(--r);

		ans[Q[i].id] = now_ans;
	}

	for(int i = 0; i < q; ++i)
		printf("%d\n", ans[i]);
}



int main(){

	scanf("%d", &n);
	for(int i = 1; i <= n; ++i){
		scanf("%d", &A[i-1].first);
		A[i-1].second = i;
	}

	sort(A, A+n);	

	int na = 1;
	a[A[0].second] = 1;
	for(int i = 1; i < n; ++i){
		if(A[i].first != A[i-1].first) na += 1; 
		a[A[i].second] = na;
	}

	scanf("%d", &q);
	for(int i = 0; i < q; ++i){
		scanf("%d %d", &Q[i].l, &Q[i].r);
		Q[i].id = i;
	}

	solve_mo();

	return 0;
}