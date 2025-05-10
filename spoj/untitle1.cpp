#include <bits/stdc++.h>
using namespace std;

const int N = 50005;
const int M = 1300;
int n, q, sq, nb;
int A[N];
long long s[N];
long long X[M], delta[M];
vector<int> block[M];

struct Line{
	long long a, b;
} lines[N];

long long cross(const Line O, const Line A, const Line B){
	return (A.a - O.a) * (B.b - O.b) - (A.b - O.b) * (B.a - O.a);
}

struct convex_hull_trick{

	vector<Line> at;
	int n;

	void init(){
		at.clear();
		n = 0; 
	}

	void add(Line l){
		while(n >= 2 and cross(at[n-2], at[n-1], l) >= 0) n--;			

		n += 1;
		at.resize(n);
		at[n-1] = l;
	}

	long long f(int id, long long x){
		return at[id].a * x + at[id].b;
	}

	long long max(long long x){

		int lo = 0, hi = n-1;
		while(lo < hi){
			int mid = lo + (hi-lo)/2;
			if(f(mid, x) <= f(mid+1, x)) lo = mid+1;			
			else hi = mid;
		}

		return f(lo, x);
	}
} cht[M];

void build(){

	for(int i = 1; i <= n; ++i)
		s[i] = s[i-1] + A[i];

	sq = sqrt(n*log2(n)) + 1;
	nb = n / sq + 1;

	for(int i = 0; i < nb; ++i){
		block[i].clear();
		cht[i].init();
		delta[i] = 0;
		X[i] = 0;
	}

	for(int i = 1; i <= n; ++i){
		block[i / sq].emplace_back(i);
		int sz = block[i / sq].size();
		lines[i] = {sz, s[i]}; 
	}

	for(int i = 0; i < nb; ++i)
		for(int j = 0; j < block[i].size(); ++j)
			cht[i].add(lines[block[i][j]]);
}

long long query(int l, int r){

	int nbl = l / sq;
	int nbr = r / sq;
	
	long long maxi = LLONG_MIN;
	if(nbl == nbr)
		for(int i = l; i <= r; ++i)
			maxi = max(maxi, lines[i].a * X[nbl] + lines[i].b + delta[nbl]);
	else{
		for(int i = l; i < (nbl+1)*sq; ++i)
			maxi = max(maxi, lines[i].a * X[nbl] + lines[i].b + delta[nbl]);

		for(int i = nbl+1; i < nbr; ++i)
			maxi = max(maxi, cht[i].max(X[i]) + delta[i]);

		for(int i = nbr * sq; i <= r; ++i)
			maxi = max(maxi, lines[i].a * X[nbr] + lines[i].b + delta[nbr]);
	}

	return maxi;
}

void update(int l, int r, int x){

	int nbl = l / sq;
	int nbr = r / sq;
	
	if(nbl == nbr){
		int t = 1;
		for(int i = l; i <= r; ++i)
			lines[i].b += 1ll *x * t++;	
		for(int i = r+1; i < min((nbl+1)*sq, n+1); ++i)
			lines[i].b += 1ll*(t-1)*x;

		cht[nbl].init();
		for(int i = 0; i < block[nbl].size(); ++i)
			cht[nbl].add(lines[block[nbl][i]]);

		for(int i = nbl + 1; i < nb; ++i)
			delta[i] += 1ll*(t-1)*x;
	}
	else{
		int t = 1;
		for(int i = l; i < (nbl+1)*sq; ++i)
			lines[i].b += 1ll * x * t++;

		cht[nbl].init();
		for(int i = 0; i < block[nbl].size(); ++i)
			cht[nbl].add(lines[block[nbl][i]]);

		for(int i = nbl+1; i < nbr; ++i){
			delta[i] += 1ll*(t-1)*x;
			X[i] += x;
			t += block[i].size();
		}

		for(int i = nbr * sq; i <= r; ++i)
			lines[i].b += 1ll * x * t++;
		for(int i = r+1; i < min((nbr+1)*sq, n+1); ++i)
			lines[i].b += 1ll*(t-1)*x;

		cht[nbr].init();
		for(int i = 0; i < block[nbr].size(); ++i)
			cht[nbr].add(lines[block[nbr][i]]);

		for(int i = nbr + 1; i < nb; ++i)
			delta[i] += 1ll*(t-1)*x;
	}
}

void solve(){
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", A+i);

	build();
	scanf("%d", &q);
	while(q--){
		int type, l, r;	

		scanf("%d %d %d", &type, &l, &r);
		if(type) printf("%lld\n", query(l, r));
		else{		
			int x;
			scanf("%d", &x);
			update(l, r, x);
		}
	}
}

int main(){
	
	solve();

	return 0;
}