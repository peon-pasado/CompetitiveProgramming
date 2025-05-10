#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 2;
bool lazy[320];
long long sum_b[320];
long long sum[N];
long long Xb[N];
long long X[N];
int Time[N];
int Timeb[N];
int now_time;
long long unit_sum[320];
int n, m, q, sq;

void update_pos(int pos, int x){

	int b_pos = pos / sq;	
	int last_x = Time[pos] >= Timeb[b_pos] ? X[pos] : Xb[b_pos];

	lazy[b_pos] = 1;
	sum_b[b_pos] += abs(last_x - x);
	sum[pos] += abs(last_x - x);
	Time[pos] = now_time;	
	X[pos] = x;
}

void update_block(int b_pos, int x){

	if(lazy[b_pos]){
		for(int i = b_pos*sq; i < (b_pos+1)*sq; ++i)
			update_pos(i, x);
		lazy[b_pos] = 0;
	}
	else{
		sum_b[b_pos] += abs(x - Xb[b_pos]) * sq;
		unit_sum[b_pos] += abs(x - Xb[b_pos]);
	}

	Timeb[b_pos] = now_time;	
	Xb[b_pos] = x;
}


void update(int l, int r, int x){
	--l; --r;
	int nbl = l / sq;
	int nbr = r / sq;

	if(nbl == nbr)
		for(int i = l; i <= r; ++i)		
			update_pos(i, x);
	else{
		for(int i = l; i < sq*(nbl+1); ++i)
			update_pos(i, x);
		
		for(int i = nbl+1; i < nbr; ++i)
			update_block(i, x);

		for(int i = nbr*sq; i <= r; ++i)
			update_pos(i, x);
	}
}

long long query(int l, int r){
	--l; --r;
	int nbl = l / sq;
	int nbr = r / sq;

	long long ans = 0;
	if(nbl == nbr)
		for(int i = l; i <= r; ++i)		
			ans += sum[i] + unit_sum[nbl];
	else{
		for(int i = l; i < sq*(nbl+1); ++i)
			ans += sum[i] + unit_sum[nbl];
		
		for(int i = nbl+1; i < nbr; ++i)
			ans += sum_b[i];

		for(int i = nbr*sq; i <= r; ++i)
			ans += sum[i] + unit_sum[nbr];
	}
	return ans;
}


int main(){

	scanf("%d %d", &n, &m);

	for(int i = 0; i < n; ++i)
		X[i] = i+1;

	memset(lazy, 1, sizeof lazy);

	sq = sqrt(n);	
	for(int i = 0; i < m; ++i){

		now_time += 1;
	
		int type, l, r, x;
		
		scanf("%d %d %d", &type, &l, &r);
	
		if(type == 1){
			scanf("%d", &x);
			update(l, r, x);
		}
		else printf("%lld\n", query(l, r));
	}

	return 0;
}