#include <bits/stdc++.h>
using namespace std; 

typedef long long ll; 

#define f(i,a,b) for(int i = a; i < b; i++)
const int N = 5e5 + 5; 



int n, dp[N][2], ty[N]; 
vector <int> adj[N]; 
bool on[N]; 

void dfs(int u){
    int maxi = -2e9, id = -1; 
    dp[u][1] = 1; 

    for(int v: adj[u]){
        dfs(v); 
        dp[u][0] += dp[v][0]; 
        dp[u][1] += dp[v][0]; 

        if(-dp[v][0] + dp[v][1] > maxi){
            maxi = dp[v][1] - dp[v][0]; 
            id = v; 
        }
    }
    if(maxi > 0){
        dp[u][0] += maxi; 
        ty[u] = id; 
    }
}

void dfs1(int u, int ti){
    on[u] = ti; 

    for(int v: adj[u]){
        int r = 0; 
        if(ti == 0 and ty[u] == v) r = 1; 
        dfs1(v, r); 
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(); 
    freopen("grant.in", "r", stdin);
    freopen("grant.out", "w", stdout);
    cin >> n; 

    f(i,2,n+1){
        int x; cin >> x; 
        adj[x].push_back(i); 
    }

    dfs(1); 

    int ans, ti = 0;   
    // if(dp[1][0] < dp[1][1]) ti = 1; 
    // else ti = 0; 

    ans = dp[1][ti]; 

    dfs1(1, ti); 

    cout << ans * 1000 << "\n"; 
    f(i,1,n+1) if(on[i]) cout << i << " "; 
//
    return 0; 
}