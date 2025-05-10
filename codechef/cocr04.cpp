#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
int a[N];
int t, n, k;

bool p(int x){
    long long ans = 0;
    for(int i = 0; i < n; ++i){
        int lo = i+1, hi = n-1;
        while(lo < hi){
            int mid = lo + (hi - lo + 1)/2;
            if(a[mid] + a[i] <= x) lo = mid;
            else hi = mid-1;
        }
        
        if(lo < n and a[lo] + a[i] <= x) ans += lo - i;
        
    }
    
    return ans < k;
}


int main() {
	
	scanf("%d", &t);
	while(t--){
	    scanf("%d %d", &n, &k);
	    for(int i = 0; i < n; ++i)
	        scanf("%d", a+i);
	 
	    sort(a, a+n);
	    
	    int lo = 1, hi = 2000000;
	    while(lo < hi){
	        int mid = lo + (hi-lo)/2;
	        if(p(mid)) lo = mid+1;
	        else hi = mid;
	    }
	   
	    printf("%d\n", lo);
	}
	
	return 0;
}
