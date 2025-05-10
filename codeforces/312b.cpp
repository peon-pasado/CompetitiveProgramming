#include <bits/stdc++.h> 
using namespace std; 
typedef long long ll;


void solve(){
  long double a,b,c,d;
  cin>>a>>b>>c>>d;
  long double ans=a/b,temp=a/b,fallo1=1-a/b,fallo2=1-c/d;
  for(int i=1;i<=10000;i++){
    ans=ans+(pow(fallo1,i)*pow(fallo2,i)*temp);
  }
  cout<<fixed << setprecision(8)<<ans<<'\n';

}
int main(){
  cin.tie(0);
  ios::sync_with_stdio(0);
  int t=1;
  //cin>>t;
  while(t--) solve();
}