#include <bits/stdc++.h>
using namespace std;

const int N = 32;
vector<long long> bf[N][N];
int t, n, nc=1, k;
int a[N];

int main() {

    scanf("%d", &t);
    
    while(t--){
        scanf("%d %d", &n, &k);
        for(int i = 0; i < n; ++i)
            scanf("%d", a+i);
        
        if(n < 3){
            puts("0");
            continue;
        }
        
        int mu = (n+1)/2;
        long long ans = 0;
        
        for(int i = 0; i < k; ++i)
            for(int j = 0; j < mu; ++j)
                bf[i][j].clear();
        
        for(int mask = 1; mask < (1<<mu); ++mask){
            
            int l_mask = __builtin_popcount(mask);
            if(l_mask > k) continue;
            
            long long sum = 0;
            int pos = -1;
            int maxi_stick = 0;
            for(int i = 0; i < mu; ++i)
                if(mask&(1<<i)){
                    sum += a[i];
                    if(maxi_stick < a[i]){
                        maxi_stick = a[i];
                        pos = i;
                    }
                }
            
            if(l_mask == k) ans += (2*maxi_stick < sum);
            else bf[l_mask][pos].push_back(sum);
        }
        
        for(int i = 1; i < k; ++i)
            for(int j = 0; j < mu; ++j)
                sort(bf[i][j].begin(), bf[i][j].end());
        
        int md = n - mu;
        for(int mask = 1; mask < (1<<md); ++mask){
            int l_mask = __builtin_popcount(mask);
            if(l_mask > k) continue;
        
            long long sum = 0;
            int maxi_stick = 0;
            for(int i = mu; i < n; ++i)
                if(mask&(1<<(i-mu))){
                    sum += a[i];
                    maxi_stick = max(maxi_stick, a[i]);
                }
        
            if(l_mask == k) ans += (2*maxi_stick < sum);
            else{
                for(int i = 0; i < mu; ++i){
                    int sz = bf[k-l_mask][i].size();
                    if(sz == 0) continue;    
                    int lo = 0, hi = sz - 1;
                    int neo_maxi = max(maxi_stick, a[i]);
                    while(lo < hi){
                        int mid = lo + (hi-lo)/2;
                        if(sum + bf[k-l_mask][i][mid] <= 2*neo_maxi) lo = mid+1;
                        else hi = mid;
                    }
                    
                    
                    if(lo < sz and sum + bf[k-l_mask][i][lo] > 2*neo_maxi)
                        ans += sz - lo;			
                }
            }
        }
        
        
        printf("Case %d: %lld\n", nc++, ans);
    }

	return 0;
}
