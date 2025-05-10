#include <bits/stdc++.h>
using namespace std;
const int maxn = 20;
const int mod = 1e9 + 7;
int F[66000];

int add(int a, int b) {
	return (a+b)%mod;
}

int mul(long long a, long long b) {
	return a*b%mod;
}

vector<pair<int, int>> blocks;
void init() {
	blocks.clear();
}

int ord(char c) {
	if (isdigit(c)) return c-'0';
	return c-'A'+10;
}

void update(char c) {
	int o = ord(c);
	for (auto& x : blocks) x.first |= 1<<o;
	blocks.push_back({1<<o, 1});
	int m = 1;
	for (int i = 1; i < blocks.size(); ++i) {
		if (blocks[i].first == blocks[m-1].first) {
			blocks[m-1].second += blocks[i].second;
		} else {
			blocks[m++] = blocks[i];
		}
	}
	blocks.resize(m);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	while (t--) {
		string s;
		cin >> s;
		init();
		memset(F, 0, sizeof F);
		for (int i = 0; i < s.size(); ++i) {
			update(s[i]);
			for (auto x : blocks) {
				F[x.first] = add(F[x.first], x.second);
			}
		}
		for (int i = 0; i < 16; ++i)
			for (int s = 0; s < 1<<16; ++s)
				if (~s & (1<<i))
					F[s] = add(F[s], F[s^(1<<i)]);
					
		for (int i = 0; i < 1<<16; ++i) 
			F[i] = mul(F[i], F[i]);	
		
		for (int i = 0; i < 16; ++i)
			for (int s = 0; s < 1<<16; ++s)
				if (~s & (1<<i))
					F[s] = add(F[s], mod - F[s^(1<<i)]);
					
		int ans = 0;
		for (int i = 1; i < 1<<16; ++i) 
			ans = add(ans, F[i]);
	
		cout << ans << '\n';
	}
	return 0;
}