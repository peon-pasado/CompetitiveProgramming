#include <bits/stdc++.h>
using namespace std;
const int N = 23;
int a[1<<N-1];
int f[1<<N];
int n;

int main() {
	scanf("%d", &n);
	memset(f, -1, sizeof f);
	for (int i = 0; i < n; ++i) {
		scanf("%d", a+i);
		f[a[i]] = a[i];
	}
	
	for(int i = 0; i < N; ++i) { 
		for(int mask = 0; mask < 1<<N; ++mask){
			if(mask & (1<<i)) {
				f[mask] = max(f[mask], f[mask^(1<<i)]);
			}
		}
	}
	
	for (int i = 0; i < n; ++i) printf("%d ", f[((1<<23)-1)^a[i]]);
	puts("");
	return 0;
}