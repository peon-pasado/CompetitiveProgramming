#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
int a[N], L[N], R[N];
int t, n, m;

int gcd(int a, int b){
    if(b == 0) return a;
    return gcd(b, a%b);
}

int main() {
	
	scanf("%d", &t);
	while(t--){
	    scanf("%d %d", &n, &m);
	    
	    for(int i = 1; i <= n; ++i)
	        scanf("%d", a+i);
	    
	    R[n+1] = 0;
	    
	    for(int i = 1; i <= n; ++i)
	        L[i] = gcd(L[i-1], a[i]);
	    
	    for(int i = n; i >= 1; --i)
	        R[i] = gcd(R[i+1], a[i]);
	   
	    
	    int  l, r;
	 
	    while(m--){
	        scanf("%d %d", &l, &r);    
	        printf("%d\n", gcd(L[l-1], R[r+1]));
	    }
	    
	}
	
	
	return 0;
}
