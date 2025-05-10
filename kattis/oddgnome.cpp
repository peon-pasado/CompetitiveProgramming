#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, t;
	scanf ("%d", &t);
	while(t--) {
		scanf ("%d", &n);
		vector<pair<int, int>> v;
		for (int i = 0; i < n; ++i) {
			int g;
			scanf ("%d", &g);
			v.push_back({g, i+1});
		}

		//sort(v.begin(), v.end());

		int ans = v[0].second;
		for (int i = 1; i < n; ++i) {
			if (v[i].first != v[i-1].first + 1) {	
				ans = v[i].second;
				break;
			}
		}

		printf("%d\n", ans);
	}
	return 0;
}