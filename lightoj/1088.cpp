#include<bits/stdc++.h>
using namespace std;
int ans(int a,const vector<int>& p, int n){
	int l=0, r=n-1;
	if(a<p[l]) return 0;
	while(l<r){
		int med=(l+r+1)/2;
		if(p[med]<=a) l=med;
		else r=med-1;
	}
	return l+1;
}
vector<int> p(1e5 + 10);
int main(){
    //ios_base::sync_with_stdio(false); 
    cin.tie(NULL);  
    int t; cin>>t;
    int cont=0,a,b,n,q;
    while(t--){
        cout<<"Case "<<++cont<<":\n";
        cin>>n>>q;
        for(int i=0;i<n;i++) cin>>p[i];
        while(q--){
        	cin>>a>>b;
        	cout<<ans(b,p, n)-ans(a-1,p, n)<<"\n";
    	} 
	} 
	return 0;
}