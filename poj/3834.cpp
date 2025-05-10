#include <cstdio>
#include <iostream>
#define ll long long
#define pb push_back
#define fi first
#define se second
#define db double
#define ull unsigned long long
#define inf 0x3f3f3f3f
using namespace std;
int n,m,fa[10],fa2[10],U[30],V[30],s[30];
int find(int x){
    return fa[x]==x?x:find(fa[x]);
}
int check(){
    for(int i=0;i<n;i++) fa2[i]=fa[i],fa[i]=i;
    int tot=0;
    for(int i=0;i<m;i++){
        if(s[i]==0){
            int x=find(U[i]),y=find(V[i]);
            if(x!=y)fa[x]=y,tot++;
        }
    }if(tot==n-1){
        return 1;
    }
    for(int i=0;i<n;i++) fa[i]=fa2[i];
    return 0;
}
int dfs(int x,int y){
    if(y==n-1)return check();
    for(int i=x;i<m;i++){
        int a=find(U[i]),b=find(V[i]);
        if(a==b)continue;
        fa[a]=b,s[i]=1;
        if(dfs(i+1,y+1))return 1;
        fa[a]=a,s[i]=0;
    }
    return 0;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    while(cin>>n>>m){
        if(n==-1&&m==-1)break;
        for(int i=0;i<n;i++) fa[i]=i;
        for(int i=0;i<m;i++) cin>>U[i]>>V[i],s[i]=0;
        cout<<(dfs(0,0)?"YES":"NO")<<'\n';
    }
}
