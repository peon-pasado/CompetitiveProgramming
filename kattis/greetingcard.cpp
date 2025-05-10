#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 50;
int x[MAXN], y[MAXN];

int main() {

	vector<pair<int, int>> v;
	map<pair<int, int>, int> m;

	for (int i = -2018; i <= 2018; ++i) {
		for (int j = 0; j*j + i*i <= 2018*2018; ++j) {	
			if (i*i + j*j == 2018*2018)
				v.push_back({i, j});
		}
		for (int j = -1; j*j + i*i <= 2018*2018; --j) {
			if (i*i + j*j == 2018*2018) 
				v.push_back({i, j});
		}
	}
	
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf ("%d %d", x+i, y+i);
		m[{x[i], y[i]}] += 1;
	}

	long long ans = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < v.size(); ++j) {
			ans += m[{x[i] + v[j].first, y[i] + v[j].second}];
		}
	}

	printf("%lld\n", ans/2);


	return 0;
}