#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
char s[maxn];
int cnt[maxn];

int main() {
	int t;
	scanf("%d", &t);
	for (int tc=1; tc<=t; ++tc) {
		printf("Case %d:\n", tc);
		scanf("%s", s + 1);
		int n = strlen(s + 1);
		for (int i = 1; s[i]; ++i) s[i] -= '0';
		int q;
		scanf("%d\n", &q);
		int sqrtn = sqrt(n);
		vector<pair<int, int>> ranges;
		for (int i = 0; i < q; ++i) {
			if (i%sqrtn == 0) {
				for (auto r : ranges) {
					cnt[r.first] ^= 1;
					cnt[r.second+1] ^= 1;
				}
				for (int i = 1; i <= n; ++i) {
					cnt[i] ^= cnt[i-1];
				}
				for (int i = 1; i <= n; ++i) {
					s[i] ^= cnt[i];
					cnt[i] = 0;
				}
				ranges.clear();
			}
			char type;
			scanf("%c", &type);
			if (type == 'I') {
				int l, r;
				scanf("%d%d\n", &l, &r);
				ranges.emplace_back(l, r);
			} else {
				int x;
				scanf("%d\n", &x);
				int ans = s[x];
				for (auto r : ranges) {
					if (r.first <= x && x <= r.second) {
						ans ^= 1;
					}
				}
				printf("%c\n", ans + '0');
			}
		}
	}
	return 0;
}