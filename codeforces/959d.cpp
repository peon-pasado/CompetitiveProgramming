#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e7 + 10;
bool composite[maxN];
vector<int> prime;
int Min[maxN];
bool vis[maxN];
int n;

void sieve(int n) {
	for(int i = 2; i <= n; ++i){
		if(not composite[i]){
			prime.push_back(i);
			Min[i] = i;
		}
		for(int p : prime){
			if(i * p > n) break;
			composite[p * i] = 1;
			Min[p * i] = p;
			if(i % p == 0) break;
		}
	}
}

bool fill(int n) {
	if(n == 1) return 0;
    vector<int> pr;
	while(n != 1) {
		int p = Min[n];

		while(n%p == 0) {
			n /= p;
		}
		if(vis[p]) {
			return 0;
		}
		pr.push_back(p);
	}

    for(int v : pr) { 
        for(int s = v; s < maxN; s += v) {
            vis[s] = 1;
		}
	}
	return 1;
}

int main() {
	sieve(1e7);
	scanf("%d", &n);
	for(int i = 0; i < n; ++i){
		int x;	
		scanf("%d", &x);

		bool ok = fill(x);
		if(ok){ 
			printf("%d ", x);
			continue;
		}
		
		for(int s = x; s < 1e7; ++s) {
		    if(not vis[s]) {
		        printf("%d ", s);
		        fill(s);
		        break;
		    }
		}
		
		int k = 0;
		for(int j = i+1; j < n;) {
			if(not vis[prime[k]]) {
				printf("%d ", prime[k]), j += 1;
			}
			k += 1;		
		}
		break;		
	}
	puts("");
	return 0;
}