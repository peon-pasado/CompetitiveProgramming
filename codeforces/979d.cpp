#include <bits/stdc++.h>
using namespace std;

const int M = 3e7 + 1999;
int q;
int T;
int trie[M][2];
int Min[M];
int Root[100003];
bool vis[100003];


void add (int root, int x, int pos) {
	
	//Max[root] = max(Max[root], x);
	Min[root] = min(Min[root], x);

    if (pos == -1) return;

	int d = (x>>pos)&1;

	if (trie[root][d] == 0)
		trie[root][d] = ++T;
	
	add (trie[root][d], x, pos-1);
}

int query (int root, int x, int pos, int s) {

	if (Min[root]+x > s) return -1;
	if (pos == -1) return Min[root];

	int d = (x >> pos) & 1;
	int v = -1;
	if (trie[root][d^1])
		v = query(trie[root][d^1], x, pos-1, s);

	if (v != -1)
		return v;
	else if (trie[root][d])
		return query(trie[root][d], x, pos-1, s);
	else
		return -1;
}

vector<int> d[100010];

int main () {

	scanf ("%d", &q);

	for (int i = 1; i <= 100000; ++i)
		Root[i] = ++T;

	memset(Min, 3, sizeof Min);
	
	for (int i = 1; i <= 100000; ++i) {
		for (int j = i; j <= 100000; j += i) {
			d[j].emplace_back(i);
		}
	}

	while (q--) {

		int type;

		scanf ("%d", &type);

		if (type == 1) {
			int u;
			scanf ("%d", &u);
			if (not vis[u]) {
				for (int e : d[u]) {
					add (Root[e], u, 20);
				}

				vis[u] = 1;
			}
		}
		else {
			int k, x, s;
			scanf ("%d %d %d", &x, &k, &s);
			if (x%k == 0)
				printf ("%d\n", query(Root[k], x, 20, s));
			else
				puts ("-1");
		}
	}


	return 0;
}