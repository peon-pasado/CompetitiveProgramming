#include <bits/stdc++.h>
using namespace std;

const int maxn = 5010;
pair<int, int> p[maxn];
int n;

int main() {
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> p[i].first >> p[i].second;
	}
	sort(p, p+n);
	int last = -1e9;
	for (int i = 0; i < n;) {
		int j = i;
		for (; j < n; ++j) {
			if (p[i].first != p[j].first) break; 
		}
		bool fail = 0;
		int max_el = -1e9;
		for (int k = i; k < j; ++k) {
			if (p[k].second < last) fail = 1;
			max_el = max(max_el, p[k].second);
		}
		if (fail) max_el = p[i].first;
		last = max_el;
		i = j;
	}
	cout << last << endl;
	return 0;
}