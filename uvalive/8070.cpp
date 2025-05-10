#include <bits/stdc++.h>
using namespace std;
const int maxN = 205;
int pos[maxN];
int n, k;

int add(int a, int b) {
	a = (a + b) % n;
	if (a < 0) a += n;
	return a;
}

int main() {
	while (cin >> n >> k) {
		pos[0] = 0;
		int id = 0;
		for (int i = 1; i <= k; ++i) {
			int o = pos[id];
			string s;
			cin >> s;
			if (s == "undo") {
				cin >> s;
				int x = atoi(s.c_str());
				id -= x;
			} else {
				int x = atoi(s.c_str());
				pos[++id] = add(o, x);	
			}
		}
		cout << pos[id] << endl;
	}
	return 0;
}