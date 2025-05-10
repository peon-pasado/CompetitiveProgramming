#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
int k, p;
bool vis[1000005];

int mul(long long a, long long b){
   return a*b%mod;
}

int expfast(int a, int n){
   int r = 1;
   while(n){
      if(n&1) r = mul(r, a);
      a = mul(a, a);
      n >>= 1;
   }
   return r;
}


int main(){

   cin >> p >> k;
   
   if(k == 0)
      cout << expfast(p, p-1) << endl;
   else if(k == 1)
      cout << expfast(p, p) << endl; 
   else{
      int ans = 1;
      for(int i = 1; i < p; ++i)
         if(not vis[i]){
            ans = mul(ans, p);
            int x = i;
            while(not vis[x]){
               vis[x] = 1;      
               x = (1LL*x*k)%p;
            }
         }

      cout << ans << endl;
   }

   return 0;
}