#include<bits/stdc++.h>
#define all(x) x.begin(),x.end()
#define sz(x) (int)x.size()
#define bs binary_search
using namespace std;
const double eps = 1e-10;
typedef long double ld;
typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
bool p(ld x, ld n){
    return x*x  + sqrt(x) < n;
}
ld solve(ld n){
    ld l = 0.0L, r = 1e10;
    while(fabs(r - l) > eps){
    	ld mid = l + (r-l)/2;
    	if(p(mid, n)) l = mid;		
    	else r = mid;
    }
    return l;
}
int main(){
    ios_base::sync_with_stdio(false);cin.tie(nullptr);
    double c;   cin >> c;   
    cout << setprecision(9) << fixed <<solve(c); 
    return 0;
}