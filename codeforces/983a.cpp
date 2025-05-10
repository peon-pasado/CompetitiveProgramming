#include <bits/stdc++.h>
using namespace std;

long long gcd(long long a, long long b){
	if(b == 0) return a;
	return gcd(b, a%b);
}

int main(){
	int t;
         ios_base::sync_with_stdio(0); cin.tie(NULL);
	cin>>t;
	long long p,q,b;
	while(t--){
		cin>>p>>q>>b;
		if(p%q == 0){
			cout<<"Finite"<<endl;
			continue;
		}
		long long g = gcd(p, q);
		q /= g;
		while(q >  1){
			g = gcd(q, b);
			if(g == 1) break;
			while(q%g == 0) q/= g;
		}
		if(q <= 1) cout<<"Finite"<<endl;
		else cout<<"Infinite"<<endl;
		 
	}
}