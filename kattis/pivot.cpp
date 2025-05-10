#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;
multiset<int> l, r;
int a[MAXN];
int n;

int main() {

	scanf ("%d", &n);

	for (int i = 0; i < n; ++i) {
		scanf("%d", a+i);
		r.insert(a[i]);
	}

	int ans = 0;
	for (int i = 0; i < n; ++i) {

		if ((l.empty() or *(l.rbegin()) < a[i]) and (r.empty() or a[i] <= *(r.begin()))) ans += 1;
		l.insert(a[i]);
		r.erase(r.lower_bound(a[i]));
	}

	printf("%d\n", ans);
	
	return 0;
}