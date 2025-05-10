#include <iostream>
using namespace std;

const int N = 10000002; 
int s[N];
int fa[N], sf[N];
long long p[N];
int n, m;

int main() {
	
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; ++i)
	    scanf("%lld", p+i);
	   
	fa[0] = 1;
	for(int i = 1; i <= m; ++i)
	    fa[i] = (1LL*i*fa[i-1])%m;
	
	for(int i = 1; i <= m; ++i)
	    sf[i] = (sf[i-1] + 1LL*i*fa[i])%m;
	
	for(int i = 1; i <= m; ++i)
	    s[i] = (s[i-1] + i)%m;
	    
	int ans = 0;
	for(int i = 0; i < n; ++i)
	    if(p[i] > m){
	        int temp = (p[i]/m%m*s[m])%m;
	        temp = (temp + s[p[i]%m])%m;
	        ans = (ans + sf[m] + p[i]%m*temp)%m;
	    
	    }else ans = (ans + sf[p[i]] + 1LL*p[i]*s[p[i]])%m;
	
	printf("%d\n", ans);
	
	return 0;
}
