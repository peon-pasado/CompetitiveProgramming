#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int query(ll x){
    cout << "? " << x << endl;
    cin >> x;
    return x;
}
ll begin(ll x){
    if(x==2)return 1;
    return (x+3)/2-begin((x+1)/2);
}
int main(){
      ll n;
      cin>>n;
      ll now = begin(n);
      query(now);
      int dir = 1;
      ll lo = 0, hi = n;
      while (hi - lo != 1) {
            ll mid = lo + (hi - lo) / 2;
            now += dir * mid;
            dir *= -1;
            if (query(now)) hi = mid;
            else lo = mid;
      }
      cout << "= " << lo + 1 << endl;
    return 0;
}
