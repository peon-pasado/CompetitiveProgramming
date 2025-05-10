#include <bits/stdc++.h>
using namespace std;
const int maxN = 510;
int n, m;
bool is[maxN][maxN];
bool has[maxN][maxN];

int T;

int main() {
	while (cin >> n >> m) {
	T = 0;
	map<string, int> id;
	for (int i = 0; i < n; ++i) {
		string a, r, b;
		cin >> a >> r >> b;
		if (not id.count(a)) id[a] = T++;
		if (not id.count(b)) id[b] = T++;
		if (r == "is-a") {
			is[id[a]][id[b]] = 1;
		} else {
			has[id[a]][id[b]] = 1;
		}
	}
	for (int i = 0; i < T; ++i) is[i][i] = 1;
	for (int k = 0; k < T; ++k) {
		for (int i = 0; i < T; ++i) {
			for (int j = 0; j < T; ++j) {
				is[i][j] |= is[i][k] and is[k][j];
				has[i][j] |= (has[i][k] and has[k][j]) or (has[i][k] and is[k][j]) or (is[i][k] and has[k][j]); 
			}
		}
	}
	for (int i = 0; i < m; ++i) {
		string a, r, b;
		cout << "Query " << i+1 << ": ";
		cin >> a >> r >> b;
		if (r == "is-a") {
			cout << (is[id[a]][id[b]] ? "true" : "false") << endl;
		} else {
			cout << (has[id[a]][id[b]] ? "true" : "false") << endl;
		}
	}
	for (int i = 0; i < T; ++i) {
		for (int j = 0; j < T; ++j) {
			is[i][j] = has[i][j] = 0;
		}
	}
	}
	return 0;
}