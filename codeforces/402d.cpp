#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

const int maxN = 1000005, M = 5005;
bool composite[maxN];
vector<int> prime;
unordered_set<int> bad;
int a[M], g[M];
int n, m;

void sieve(int n) {
	for (int i = 2; i <= n; ++i) {
		if (not composite[i]) {
			prime.push_back(i);
		}
		for (int p : prime) {
			if (p * i > n) break;
			composite[p * i] = 1;
			if (i % p == 0) break;
		}
	}
}

int f(int n){
	int l = 0;
	for(int i = 0; prime[i]*1ll*prime[i] <= n; ++i) {
		if(n % prime[i] == 0) {
			int e = 0; 
			while(n % prime[i] == 0) {
				e++;
				n /= prime[i];
			}

			if(bad.count(prime[i])) l -= e; 			
			else l += e;
		}
	}
	if(n > 1) {
		if(bad.count(n)) l -= 1;
		else l += 1;
	}
	return l;
}

int gcd(int a, int b){
	if(b == 0) return a;
	return gcd(b, a%b);
}

int main(){
	sieve(maxN - 1);
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; ++i) {
		scanf("%d", a+i);	
	}
	for(int x, i = 0; i < m; ++i){
		scanf("%d", &x);
		bad.insert(x);
	}
	int res = 0;
	for(int i = 0; i < n; ++i) {
		res += f(a[i]);
	}
	g[0] = a[0];
	for(int i = 1; i < n; ++i) {
		g[i] = gcd(a[i], g[i-1]);
	}
	int div = 1;
	for(int i = n-1; i >= 0; --i){
		int tr = f(g[i] / div);
		if(tr < 0){
			res -= (i+1)*tr;
			div = g[i];
		}
	}
	printf("%d\n", res);

	return 0;
}