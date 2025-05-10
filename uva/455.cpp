#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
vi borde(const string& s) {
	int n = s.size();
	vi b(n+1);
	b[0] = -1;
	for (int i = 1; i <= n; ++i) {
		b[i] = b[i-1];
		while (b[i] != -1 and s[i-1] != s[b[i]]) {
			b[i] = b[b[i]];
		}
		b[i] += 1;
	}
	return b;
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		string s;
		cin >> s;
		vi b = borde(s);
		int n = s.size();
		int cur = b[n];
		while (n % (n - cur) != 0) {
			cur = b[cur];
		}
		cout << n - cur << endl; 
		if (t) cout << endl;	
	}
	return 0;
}