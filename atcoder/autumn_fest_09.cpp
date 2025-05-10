#include <iostream>
using namespace std;

const int p = 1e9 + 7;
const int mod = 1e9 + 9;
const int o = 1010;
using ll = long long;
int mat[3*o][3*o];
int a, b, d;
int ma, mb, md;
int aa, ab, ad;

int add(int a, int b, int m) {
	return (a+b)%m;
}

int mul(ll a, ll b, int m) {
	return a*b%m;
}

void add(int x, int y) {
	mat[o+x][o+y]++;
}

void sub(int x, int y) {
	mat[o+x][o+y]--;
}

int get(int x, int y) {
	return mat[o+x][o+y];
}

int main() {
	int n, m, q;
	cin >> n >> m >> q;
	cin >> a >> ma >> aa;
	cin >> b >> mb >> ab;
	cin >> d >> md >> ad;
	for (int i = 0; i < q; ++i) {
		add(a-d+1, b);
		sub(a-d+1, b+1);
		add(a-d+2, b);
		sub(a-d+2, b+1);
		
		add(a+1, b+d);
		add(a+1, b+d+1);
		sub(a+2, b+d);
		sub(a+2, b+d+1);
		
		sub(a+d+1, b);
		sub(a+d+2, b);
		add(a+d+1, b+1);
		add(a+d+2, b+1);
		
		sub(a+1, b-d);
		sub(a+1, b-d+1);
		add(a+2, b-d);
		add(a+2, b-d+1);
		
		a = add(mul(a, ma, n), aa, n) + 1;
		b = add(mul(b, mb, m), ab, m) + 1;
		d = add(mul(d, md, max(m, n)), ad, max(m, n)) + 1;
	}
	
	for (int i = 0; i < 3*o; ++i)
		for (int j = 0; j < 3*o; ++j)
			if (i>0 && j>0) (mat[i][j] += mat[i-1][j-1]) %= mod;
	
	for (int i = 0; i < 3*o; ++i)
		for (int j = 3*o-1; j >= 0; --j)
			if (i>0 && j<3*o-1) (mat[i][j] += mat[i-1][j+1]) %= mod;
	
	for (int i = 0; i < 3*o; ++i)
		for (int j = 0; j < 3*o; ++j)
			if (i > 0) (mat[i][j] += mat[i-1][j]) %= mod;
	
	for (int i = 0; i < 3*o; ++i)
		for (int j = 0; j < 3*o; ++j)
			if (j > 0) (mat[i][j] += mat[i][j-1]) %= mod;
	
	int hash = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			hash = add(mul(hash, p, mod), get(i, j), mod);
	
	cout << hash << '\n';
	return 0;
}