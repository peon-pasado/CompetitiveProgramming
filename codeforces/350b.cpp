#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int n;
int c[maxn], out[maxn], p[maxn];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", c+i);
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%d", p+i);
		out[p[i]] += 1;
	}
	vector<int> ans[maxn];
	for (int i = 1; i <= n; ++i) {
		if (c[i] == 1) {
			ans[i].push_back(i);
			int x = i;
			while (p[x] != 0 and out[p[x]] == 1) {
				ans[i].push_back(x = p[x]);
			}
		}
	}
	int m = 0, id;
	for (int i = 1; i <= n; ++i) {
		if (m < ans[i].size()) {
			m = ans[i].size();
			id = i;
		}
	}
	printf("%d\n", m);
	reverse(begin(ans[id]), end(ans[id]));		
	for (int e : ans[id]) printf("%d ", e);
	puts("");
	return 0;
}