#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;
int a[MAXN];
int st[MAXN<<2];
int n, k;

void build(int nx = 1, int l = 1, int r = n) {
	if (l == r) {
		st[nx] = a[r] == 0 ? 0 : (a[r] < 0 ? -1 : 1); 
		return;
	}
	int mid = (l+r)/2;
	build(nx<<1, l, mid);
	build(nx<<1|1, mid+1, r);
	st[nx] = st[nx<<1] * st[nx<<1|1];
}

void update(int pos, int v, int nx = 1, int l = 1, int r = n) {
	if (pos < l or r < pos) return;
	if (l == r) {	
		st[nx] = v == 0 ? 0 : (v < 0 ? -1 : 1); 
		return;
	}
	int mid = (l+r)/2;
	update(pos, v, nx<<1, l, mid);
	update(pos, v, nx<<1|1, mid+1, r);
	st[nx] = st[nx<<1] * st[nx<<1|1];
}

int query(int a, int b, int nx = 1, int l = 1, int r = n) {
	if (b < l or a > r) return 1;
	if (a <= l and r <= b) return st[nx];
	int mid = (l+r)/2;
	return query(a, b, nx<<1, l, mid) * query(a, b, nx<<1|1, mid+1, r);
}

int main() {
	
	while (scanf("%d %d", &n, &k) == 2) {

		for (int i = 1; i <= n; ++i) {
			scanf("%d", a+i);
		}	

		build();
		getchar();
		while (k--) {
			char type = getchar();
			int a, b;
			scanf("%d %d\n", &a, &b);

			if (type == 'C') {
				update(a, b);
			} else {		
				int x = query(a, b);	
				char ans = '0';
				if (x == 1) ans = '+';
				if (x == -1) ans = '-';

				putchar(ans);
			}
		}
		puts("");
	}

	return 0;
}