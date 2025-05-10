#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e3 + 10;
pair<int, int> a[maxN];
int t, n;
int P, Q;

bool f(int mid, int i, int j) {
	return (a[mid].first * a[mid].first *1ll* Q <= 
	Q *1ll* (a[i].first * a[i].first + a[j].first * a[j].first) 
	- 2ll*a[i].first*a[j].first*P);
}

int range(int a, int b, int i, int j) {
	if (a > b) return 0;
	while (a < b) {
		int mid = a + (b-a+1) / 2;
		if (f(mid, i, j)) a = mid;
		else b = mid-1;
	}
	if (f(a, i, j)) return a;
	return 0;
}

int main() {
	cin >> t;
	while (t--) {
		cin >> n >> P >> Q;
		for (int i = 1; i <= n; ++i) {
			cin >> a[i].first;
			a[i].second = i;
		}
		sort(a+1, a+n+1);
		int num = 0, den = 0;
		int x, y, z;
		for (int i = 1; i <= n; ++i) {
			for (int j = i+1; j <= n; ++j) {
				int zz[4] = {
						range(1, i-1, i, j),
						range(i+1, j-1, i, j),
						range(j+1, n, i, j)
					};		
				int n1 = a[i].first * a[i].first + a[j].first * a[j].first;	
				int d1 = 2 * a[i].first * a[j].first;
				sort(zz, zz+3); 		
				if (zz[2] == 0) continue;
				if (zz[2] < j and a[zz[2]].first + a[i].first <= a[j].first) continue;	
				n1 -= a[zz[2]].first * a[zz[2]].first;
				if (n1 *1ll* den <= num *1ll* d1) {
					x = a[i].second, y = a[j].second, z = a[zz[2]].second;
					num = n1;
					den = d1;
				}
			}
		}
		if (den) cout << z << " " << y << " " << x << endl;
		else cout << -1 << endl;
	}
	return 0;
}
