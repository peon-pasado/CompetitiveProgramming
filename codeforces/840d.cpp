#include <bits/stdc++.h>
using namespace std;

const int N = 3E5 + 5;
int a[N];
int n, q;
vector<int> adj[N];
int inv[N];
unsigned short acx[550][N];
unsigned char acy[550][N];
vector<int> best;
int C[N];


int main(){

	scanf("%d %d", &n, &q);

	for(int i = 1; i <= n; ++i){
		scanf("%d", a+i);
		adj[a[i]].push_back(i);
	}
	
	int sq = 555;
	int t = 0; 
	for(int i = 1; i <= n; ++i)
		if(adj[i].size() >= sq){
			inv[i] = t++;			

			for(int j = 0; j < adj[i].size(); ++j)
				acy[t-1][adj[i][j]] = 1;				

			for(int i = 1; i <= n; ++i){
				acx[t-1][i] += acx[t-1][i-1]; 
				int temp = acy[t-1][i] + 0 + acy[t-1][i-1];		
				acx[t-1][i] += temp / 255;
				acy[t-1][i] = temp%255;
			}

			best.push_back(i);
		}

	while(q--){

		int l, r, k;
		scanf("%d %d %d", &l, &r, &k);
		
		int need = (r - l + 1)/k;
		int ans = INT_MAX;
		if(r - l + 1 <= 5*sq){
			for(int i = l; i <= r; ++i){
				C[a[i]] += 1;
				if(C[a[i]] > need) ans = min(ans, a[i]); 
			}		

			for(int i = l; i <= r; ++i)
				C[a[i]] -= 1;
		}
		else{
			for(int v : best){
				int dx = acx[inv[v]][r] * 255 + acy[inv[v]][r] - acx[inv[v]][l-1] * 255 - acy[inv[v]][l-1];			
				if(dx > need)
				    ans = min(ans, v);
			}
		}

		printf("%d\n", ans == INT_MAX ? -1 : ans);
	}
	

	return 0;
}