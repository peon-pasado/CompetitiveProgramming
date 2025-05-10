#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
const int N = 5000002;
long long f[N];
int p[N];
int t, l, r;

void sieve(int n){

   for(int i = 4; i <= n; i += 2) p[i] = 2;

   for(int i = 3; i*i <= n; i += 2)
      if(not p[i])
         for(int j = i*i; j <= n; j += i+i)
            if(not p[j])
               p[j] = i;
}


int add(long long a, int b){
   return (a+b)%mod;
}

int mul(long long a, long long b){
   return a*b%mod;
}

long long fa(long long a, int b){
   return (a-1)*a/2*b; 
}


int preproc(int n){
   f[1] = 0;
   f[2] = 1;
   f[3] = 3;
   
   for(int i = 4; i <= n; ++i){
      if(p[i] == 0)
         f[i] = add(fa(i, 1), f[1]);
      else
         f[i] = add(fa(p[i], i/p[i]), f[i/p[i]]);
   }
}


int main(){

   cin >> t >> l >> r;
   sieve(r);
   preproc(r);   

   int ans = 0;
   int tp = 1;
   for(int i = l; i <= r; ++i){
      ans = add(ans, mul(tp, f[i]));
      tp = mul(tp, t);
   }
   printf("%d\n", ans);

   return 0;
}