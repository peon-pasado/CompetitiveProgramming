#include <bits/stdc++.h>
using namespace std;

int k, n;
const int mod = 1e9+9;
const int p = 257;
const int MAXN = 1e5 + 5;
int P[MAXN];

int add(int a, int b) {
	return (a+b)%mod;
}
int mul(long long a, long long b) {
	return a*b%mod;
}
multiset<pair<pair<int, int>, int>> ss;

int main() {
	
	scanf("%d %d\n", &k, &n);
	
	for (int i = P[0] = 1; i < n; ++i) {
		P[i] = mul(P[i-1], p);
	}
	
	for (int i = 0; i < k; ++i) {
		int h = 0, r = 0;
		for (int j = 0; j < n; ++j) {
			int ch = getchar();
			h = add(h, mul(P[j], ch));
			r = add(mul(r, p), ch);
		}
		int c;		
		scanf("%d\n", &c);
		ss.insert({{h, r}, -c});
	}
	
	int ans = 0;
	int add = 0;
	vector<pair<int, int>> rr;
	
	while (not ss.empty()) {
		auto pq = ss.begin(); 
		auto q = *pq;
		ss.erase(pq);
		
		auto r = ss.empty() ? ss.end() : ss.lower_bound({{q.first.second, q.first.first}, -1000000000});
		if (r != ss.end() and q.first.second == r->first.first) {
		    int sum = max(0, -q.second - r->second);
		    bool p1 = q.first.first == q.first.second;
		    bool p2 = r->first.first == r->first.second;
		    
		    if ((r->second^q.second) < 0) {
		        if (-q.second > 0)
		                rr.push_back({sum, p1 ? -q.second : 0});
		        if (-r->second > 0) 
		                rr.push_back({sum, p2 ? -r->second : 0});
		    }
		    
			ans += sum;
			ss.erase(r);
		} else {
			if (q.first.first == q.first.second) add = max(add, -q.second);
		}
	}
	
	ans += add;
	int lans = ans;
	for (auto v : rr)
	    lans = max(lans, ans - add - v.first + v.second);
	
	printf("%d\n", lans);
	
	return 0;
}