#include <bits/stdc++.h>
using namespace std;

const int M = 6e2 + 1;
const int N = 3e5 + 1;
const int mod = 1e9 + 9;


int mul(long long a, long long b){
	return a*b%mod;
}

int add(int a, int b){
	return (a+b)%mod;
}

int sq, n, m;
int block[M];
int sum[2][M];
int a[N], f[N];
bool lazy[M];

void rebuild(int id){
	if(lazy[id]){	

		int A = sum[0][id];
		int B = sum[1][id];
		
		for(int i = 0; i < sq; ++i){
			a[id*sq + i] = add(a[id*sq + i], B);
			A = add(A, B);
			swap(A, B);
		}

		lazy[id] = 0;
		sum[0][id] = sum[1][id] = 0;
	}
}

void init(){
	sq = sqrt(n);
	f[0] = 0;
	f[1] = 1;
	for(int i = 2; i < N; ++i)
		f[i] = add(f[i-1], f[i-2]);

	for(int i = 0; i < n; ++i)
		block[i/sq] = add(block[i/sq], a[i]);
}

void update(int l, int r){
	l--; r--;

	int nbl = l / sq;
	int nbr = r / sq;


	if(nbl == nbr)
		for(int i = l; i <= r; ++i){
			a[i] = add(a[i], f[i - l + 1]);
			block[i/sq] = add(block[i/sq], f[i - l + 1]);
		}
	else{
		int t = 1;
		for(int i = l; i < (nbl+1)*sq; ++i){
			a[i] = add(a[i], f[t]);
			block[i/sq] = add(block[i/sq], f[t]);
			t += 1;
		}
		
		for(int i = nbl+1; i < nbr; ++i){
			sum[0][i] = add(sum[0][i], f[t-1]);
			sum[1][i] = add(sum[1][i], f[t]);
			lazy[i] = 1;
			block[i] = add(block[i], add(f[t + sq + 1], mod - f[t+1]));
			t += sq;
		}

		for(int i = nbr*sq; i <= r; ++i){
			a[i] = add(a[i], f[t]);
			block[i/sq] = add(block[i/sq], f[t]);	
			t += 1;
		}
	}
}



int query(int l, int r){
	r--; l--;

	int nbl = l / sq;
	int nbr = r / sq;

	int ans = 0;
	if(nbl == nbr){
		rebuild(nbl);
		for(int i = l; i <= r; ++i)
			ans = add(ans, a[i]);
	}
	else{
		rebuild(nbl); rebuild(nbr);
		for(int i = l; i < (nbl+1)*sq; ++i)
			ans = add(ans, a[i]);

		for(int i = nbl+1; i < nbr; ++i)
			ans = add(ans, block[i]);

		for(int i = nbr*sq; i <= r; ++i)
			ans = add(ans, a[i]);
	}

	return ans;
}


int main(){	

	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%d", a+i);	

	init();

	while(m--){
		int type, l, r;
		scanf("%d %d %d", &type, &l, &r);
		if(type == 1) update(l, r);
		else printf("%d\n", query(l, r));
	}


	return 0;
}
