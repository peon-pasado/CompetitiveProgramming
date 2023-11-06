#include <bits/stdc++.h>
using namespace std;
const int maxn = 102;
string w[maxn], r[maxn];
int n, m;

void backtrack(string& w, string& r, int pos) {
	if (pos == r.size()) {
		for (char c : r) {
			if (c == '#') cout << w;
			else cout << c;
		}
		cout << endl;
		return;
	}
	if (r[pos] == '#') backtrack(w, r, pos+1);
	else {
		for (int i = 0; i < 10; ++i) {
			r[pos] = i + '0';
			backtrack(w, r, pos+1);
			r[pos] = '0';
		}
	}
}

int main() {
	while (cin >> n) {
		for (int i = 0; i < n; ++i) cin >> w[i];
		cin >> m;
		for (int j = 0; j < m; ++j) cin >> r[j];
		cout << "--" << endl;
		for (int j = 0; j < n; ++j) {
			for (int i = 0; i < m; ++i) {
				backtrack(w[j], r[i], 0);
			}
		}
	}
	return 0;
}