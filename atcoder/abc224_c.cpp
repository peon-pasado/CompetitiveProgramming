#include <bits/stdc++.h>
#define fio ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
#define ln '\n'
#define ll long long
#define F first
#define S second
#define all(x) x.begin(),x.end()
#define sz(x) (int)x.size()
#define double long double

void go(){
    int n;cin>>n;
    pair<ll,ll> A[n];
    for(int i=0;i<n;i++)cin >> A[i].F >> A[i].S;
    int ans=0;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            for(int k=j+1;k<n;k++){
                if((A[j].F-A[i].F)*(A[k].S-A[i].S)-(A[k].F-A[i].F)*(A[j].S-A[i].S)!=0LL){
                    ans++;
                }
            }
        }
    }
    cout << ans << ln;
}
int main(){
    fio
    //freopen("test.in","r",stdin);
    //freopen("test.out","w",stdout);
    int tt=1;
    //cin>>tt;
    while(tt--)go();
    return 0;
}