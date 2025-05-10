#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
int ft[MAXN];
int bp[MAXN], ibp[MAXN];
int L, N, B, P;

int add(int a, int b) {
	return (a+b)%P;
}

int mul(long long a, long long b) {
	return a*b%P;
}

void update(int x, int v) {
	while (x <= L) { 
		ft[x] = add(ft[x], v);
		x += x&-x;
	}
}

int query(int x) {
	int ans = 0;
	while (x > 0) {
		ans = add(ans, ft[x]);
		x -= x&-x;
	}
	return ans;
}

int ex(int a, int b) {
	int r = 1;
	while (b > 0) {
		if (b&1) r = mul(r, a);
		a = mul(a, a);
		b >>= 1;
	}
	return r;
}


int main() {

	while(scanf("%d %d %d %d\n", &B, &P, &L, &N), B+P+L+N) {
		int ib = ex(B, P-2);
		bp[0] = 1;
		ibp[0] = 1;
		for (int i = 1; i <= L; ++i) {	
			ft[i] = 0;
			bp[i] = mul(B, bp[i-1]);
			ibp[i] = mul(ib, ibp[i-1]);
		}
	
		for (int i = 0; i < N; ++i) {
			int op = getchar();
			if (op == 'E') {
				int I, V;
				scanf("%d %d\n", &I, &V);
				int val = add(query(I), P - query(I-1));
				update(I, add(mul(V, bp[L-I]), P - val));
			} else {
				int I, J;
				scanf("%d %d\n", &I, &J);
				printf("%d\n", mul(add(query(J), P - query(I-1)), ibp[L-J]));
			}
		}
		puts("-");
	}	

	return 0;
}