#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;

struct Participant {
	int a, b, c;
} p[maxn];
int n;
pair<int, int> ranking_a[maxn];

int ft[maxn];

void update(int pos, int v) {
	while (pos < maxn) {
		ft[pos] = min(ft[pos], v);
		pos += pos&-pos;
	}
}

int query(int pos) {
	int ans = INT_MAX;
	while (pos > 0) {
		ans = min(ans, ft[pos]);
		pos -= pos&-pos;
	}
	return ans;
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {		
			scanf("%d %d %d", &p[i].a, &p[i].b, &p[i].c);
			ranking_a[p[i].a] = {p[i].b, p[i].c};
		}
		memset(ft, 1, sizeof ft);
		int cnt = 0;
		for (int i = 1; i <= n; ++i) {
			int temp = query(ranking_a[i].first);
			if (temp > ranking_a[i].second) {
				cnt += 1;
			}
			update(ranking_a[i].first, ranking_a[i].second);
		}
		printf("%d\n", cnt);
	}
	return 0;
}