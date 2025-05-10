#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int B = 1500;
int n;
int a[N];
int l[N], r[N];
long long C[N][B];
unsigned long long Ans[B];
int sq, nb;
long long ft[N];

void updateft(int pos, int v){
	while(pos < N){
		
		ft[pos] += v;

		pos += pos&-pos;
	}
}

long long queryft(int pos){

	long long ans = 0;
	while(pos > 0){
		ans += ft[pos];
		pos -= pos&-pos;
	}	
	
	return ans;
}


void build(){

	for(int i = 1; i <= n; ++i)
		updateft(i, a[i]);
	
	sq = n / (sqrt(n * log2(n)) + 1) + 1;
	nb = n / sq + 1; 
	for(int i = 1; i <= n; ++i){
		C[l[i]][i/sq] += 1; 
		C[r[i] + 1][i/sq] -= 1;
	}

	for(int j = 0; j < nb; ++j){
		Ans[j] = 0;
		for(int i = 1; i <= n; ++i){
			C[i][j] += C[i-1][j];
			Ans[j] += 1ULL * C[i][j] * a[i];
		}
	}
}

unsigned long long query(int L, int R){


	int nbL = L / sq;
	int nbR = R / sq;
	unsigned long long ans = 0ull;

	if(nbL == nbR)
		for(int i = L; i <= R; ++i)
			ans += 1ull*(queryft(r[i]) - queryft(l[i] - 1));	
	else{
		for(int i = L; i < (nbL+1)*sq; ++i)
			ans += 1ull*(queryft(r[i]) - queryft(l[i] - 1));
		
		for(int i = nbL + 1; i < nbR; ++i)
			ans += Ans[i];

		for(int i = nbR*sq; i <= R; ++i)
			ans += 1uLL*(queryft(r[i]) - queryft(l[i] - 1));
	}

	return ans;
}

void update(int pos, int nv){

	for(int i = 0; i < nb; ++i)
		Ans[i] += C[pos][i] * (nv - a[pos]);

	updateft(pos, nv - a[pos]);
	a[pos] = nv;
}



int main(){

	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a+i);

	for(int i = 1; i <= n; ++i)
		scanf("%d %d", l+i, r+i);

	build();

	int q;
	scanf("%d", &q);
	while(q--){	
		int type;	
		scanf("%d", &type);

		if(type == 1){
			int x, y;
			scanf("%d %d", &x, &y);
			update(x, y);
		}		
		else{
			int L, R;
			scanf("%d %d", &L, &R);
			printf("%llu\n", query(L, R));
		}
	}

	return 0;
}