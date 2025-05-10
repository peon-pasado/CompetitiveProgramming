#include <bits/stdc++.h>
#define sz(v) (ll) v.size()
#define ff first
#define ss second

using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;

const ll N = 820;
const int S = 31625;

int n,a,b,c,d;

bool check(int x){
    if(x < 1) return 0;
    bool f1 = ((a+x-1)/x <= b/x), f2 = ((c+x-1)/x <= d/x);
    return (f1 && f2);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i){
        cin >> a >> b >> c >> d;
        int ans = -1;
        int r = max(b, d);
        for (int j = 1; j*j <= r; ++j) if (check(j)) ans = max(ans, j);
        for (int j = 1; j*j <= r; ++j) if (check(b/j)) ans = max(ans, b/j);
        for (int j = 1; j*j <= r; ++j) if (check(d/j)) ans = max(ans, d/j);
        cout << ans << "\n";
    }
    return 0;
}