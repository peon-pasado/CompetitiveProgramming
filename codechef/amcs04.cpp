#include <bits/stdc++.h>
using namespace std;

const int N = 10010;
int A, C, M, K;
int t;
int f[2][N];
map<int, int> mapa;

int add(int a, int b){
	return (a+b)%M;
}

int mul(long long a, long long b){
	return (a*b)%M;
}

int expfast(int a, int n){
	int r = 1;
	while(n){
		if(n&1) r = mul(r, a);
		a = mul(a, a);
		n >>= 1;
	}
	return r;
}

int gcdex(int a, int b, int& x, int& y){
	if(b == 0){
		x = 1;
		y = 0;
		return a;
	}

	int x1, y1;
	int g = gcdex(b, a%b, x1, y1);
	x = y1;
	y = add(x1, M - mul(a/b, y1));
	return g;
}

int inv(int a, int b = M){
	int x, y;
	gcdex(a, b, x, y);	
	return x;
}

int answer(int x, int y){
	int mod = 1000000007;
	
	int a = 1LL*x*K%mod;
	int b = 1LL*(K-1)*K/2%mod;

	return (a + 1LL*b*y%mod)%mod;
}


int main(){

	scanf("%d", &t);
	while(t--){
		scanf("%d %d %d %d", &A, &C, &M, &K);

		int lx = (int) sqrt(M + 0.) + 1;		
		int A_q = expfast(A, lx);
		int A_inv = inv(A);
		

		f[0][0] = 1;
		for(int i = 1; i <= lx; ++i)
			f[0][i] = mul(f[0][i-1], A_q);

		mapa.clear();		
		for(int i = 0; i <= lx; ++i)
			if(mapa.count(f[0][i]))
				mapa[f[0][i]] = min(mapa[f[0][i]], i);
			else
				mapa[f[0][i]] = i; 

		f[1][0] = 1;
		for(int i = 1; i <= lx; ++i)
			f[1][i] = mul(f[1][i-1], A_inv);

		int x = INT_MAX, y = INT_MAX;
		for(int i = 0; i <= lx; ++i){
			int temp = mul(f[1][i], C);	
			if(mapa.count(temp)) x = min(x, mapa[temp]*lx + i);
			if(mapa.count(f[1][i])){ 
				int ty = mapa[f[1][i]]*lx + i;
				if(ty != 0) y = min(y, ty);
			}
		}

		if(x == INT_MAX) puts("0");
		else{
			if(y == INT_MAX){
				if(K == 1) printf("%d\n", x);
				else puts("0");
			}
			else printf("%d\n", answer(x, y));
		}
	}

	return 0;
}