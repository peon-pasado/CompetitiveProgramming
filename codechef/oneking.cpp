#include <bits/stdc++.h>
using namespace std;

vector<int> adj[2][2005];
bool vis[100005];
int t, n;

int main() {
	
	scanf("%d", &t);
	while(t--){
	    scanf("%d", &n);
	    
	    for(int i = 0; i <= 2000; ++i){
	        adj[0][i].clear();
	        adj[1][i].clear();  
	    }
	    
	    int x, y;
	    for(int i = 0; i < n; ++i){
	        scanf("%d %d", &x, &y);
	        adj[0][x].push_back(i);   
	        adj[1][y].push_back(i);
	    }
	       
	   queue<int> Q;    
	   memset(vis, 0, sizeof vis);
	 
	    int ans = 0;
	    for(int i = 0; i <= 2000; ++i){
	        for(int j = 0; j < adj[0][i].size(); ++j)
	            Q.push(adj[0][i][j]);
	        
	        for(int j = 0; j < adj[1][i].size(); ++j)
	            if(not vis[adj[1][i][j]]){
	                ans += 1;
	                while(not Q.empty()){
	                    int q = Q.front(); Q.pop(); 
	                    vis[q] = 1;
	                }
	            }
	    }
	    
	    printf("%d\n", ans);
	}
	
	return 0;
}
