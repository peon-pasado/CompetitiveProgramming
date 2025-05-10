 #include <cstdio>
 #include <vector>
  using namespace std;
  
  typedef long long int LLI;
  struct Item {
      LLI g;
      int p;
  };
 
 LLI gcd(LLI a, LLI b) {
     return b == 0 ? a : gcd(b, a%b);
 }
 
 int main() {
     int T, n;
     LLI v, ans;
     scanf("%d", &T);
     while(T--) {
         ans = 0;
         vector<Item> vec;
         scanf("%d", &n);
         for(int t = 0; t < n; t++) {
             scanf("%lld", &v);
             for(int i = 0; i < vec.size(); i++) vec[i].g = gcd(vec[i].g, v);
             vec.push_back((Item){v,t});
             vector<Item> nvec;
             for(int i = 0; i < vec.size(); i++) {
                 if(i != 0 && vec[i].g == vec[i-1].g) continue;
                 ans = max(ans, vec[i].g * (t-vec[i].p+1));
                 nvec.push_back(vec[i]);
             }
             vec = nvec;
         }
         printf("%lld\n", ans);
     }
     return 0;
}
