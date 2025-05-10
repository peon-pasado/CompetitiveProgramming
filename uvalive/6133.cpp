#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100;
char s[100002][MAXN];
const int MAXT = 1e6 + 10;
int trie[MAXT][26];
int sons[MAXT];
bool terminal[MAXT];
int elems = 0;
int n;

void add(char s[]) {
	int root = 0;
	for (int i = 0; s[i]; ++i) {
		int v = s[i] - 'a';
		if (trie[root][v] == 0) trie[root][v] = ++elems, sons[root] += 1;
		root = trie[root][v];
	}
	terminal[root] = 1;
}

int keywords(char s[]) {
	bool fst = 1;
	int ans = 0;
	int root = 0;
	for (int i = 0; s[i]; ++i) {
		int v = s[i] - 'a';
		if (fst) {
			ans = 1;
			fst = 0;
		} else {
			ans += sons[root] != 1 or terminal[root];
		}
		
		root = trie[root][v];
	}

	return ans;
}


int main() {

	while (scanf("%d\n", &n) == 1) {
		
		memset(trie, 0, sizeof trie);
		memset(terminal, 0, sizeof terminal);
		memset(sons, 0, sizeof sons);
		elems = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%s", s[i]);
			add(s[i]);
		}	

		int sum = 0;
		for (int i = 1; i <= n; ++i) {

			sum += keywords(s[i]);
		}

		printf("%.2f\n", 1. * sum / n);

	}
	return 0;
}