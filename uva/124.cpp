#include <bits/stdc++.h>
using namespace std;

const int maxn = 300;
bool vis[maxn];
bool adj[maxn][maxn];
char pr[maxn];

void bt(set<char>& s, int pos) {
	if (pos == s.size()) {
		pr[pos] = 0;
		puts(pr);
		return;
	}
	for (auto ch : s) {
		if (vis[ch]) continue;
		bool ok = 1;
		for (int i = 0; i < pos; ++i) {
			if (adj[ch][pr[i]]) {
				ok = 0;
				break;
			}
		}
		if (!ok) continue;
		vis[ch] = 1;
		pr[pos] = ch;
		bt(s, pos+1);
		vis[ch] = 0;
	}
}

int main() {
	string s;
	bool fst = 1;
	while (getline(cin, s)) {
		istringstream ss(s);
		char a;
		set<char> S;
		while (ss >> a) S.insert(a);
		getline(cin, s);
		istringstream ss2(s);
		char b;
		memset(adj, 0, sizeof adj);
		while (ss2 >> a >> b) {
			adj[a][b] = 1;
		}
		if (!fst) puts("");
		fst = 0;
		bt(S, 0);
	}
	return 0;
}
