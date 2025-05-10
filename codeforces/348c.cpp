#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+2;
int n, nn, m, q, sq;
long long a[N];
vector<int> S[N];
long long sum[N];
bool vis[N];
int C[N][315];
int inv[N];
long long ch[N];
int rev[315];

int main(){

	scanf("%d %d %d", &n, &m, &q);
	
	for(int i = 1; i <= n; ++i)
		scanf("%lld", a+i);

	for(int i = 1; i <= m; ++i){
		int sz;
		scanf("%d", &sz);
		for(int j = 1; j <= sz; ++j){
			int x;
			scanf("%d", &x);
			S[i].push_back(x);
			sum[i] += a[x];
		}
	}

	sq = 320;
	for(int i = 1; i <= m; ++i)
		if(S[i].size() >= sq){
			
			memset(vis, 0, sizeof vis);
			for(int v : S[i])
				vis[v] = 1;				

			for(int j = 1; j <= m; ++j)
				for(int v : S[j])
					if(vis[v])
						C[j][nn] += 1;

			inv[i] = nn;
			rev[nn] = i;
			nn += 1;
		}

	
	while(q--){

		getchar();		
		if(getchar() == '?'){
			int id;	
			scanf("%d", &id);			

			long long ans = 0;
			if(S[id].size() >= sq)
				ans = sum[id];
			else
				for(int v : S[id])
					ans += a[v];

			for(int i = 0; i < nn; ++i)	
				ans += C[id][i] * ch[i];
			printf("%lld\n", ans);
		}
		else{
			int id, x;
			scanf("%d %d", &id, &x);
			
			if(S[id].size() >= sq)
				ch[inv[id]] += x;
			else{	
				for(int v : S[id])
					a[v] += x;

				for(int i = 0; i < nn; ++i)
					sum[rev[i]] += C[id][i] * 1ll * x;
			}
		}
	}

	return 0;
}