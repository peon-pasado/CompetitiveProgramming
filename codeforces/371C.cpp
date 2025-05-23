#include <bits/stdc++.h>

using namespace std;

long long b, s, c, r,
    kb, ks, kc,
    nb, ns, nc,
    pb, ps, pc;
string A;

bool proof(long long mid){
    return max(kb*mid - nb, 0ll)*pb + max(ks*mid - ns, 0ll)*ps + max(kc*mid - nc, 0ll)*pc <= r;
}


int main(){
    
    //ios_base::sync_with_stdio(0);
    cin >> A;   
    cin >> nb >> ns >> nc;
    cin >> pb >> ps >> pc;
    cin >> r;
    for(auto a : A)
        if(a == 'B') kb++;
        else if(a == 'S') ks++;
        else kc++;

    long long lo = 0ll, hi = 10000000000000ll;
    while(lo < hi){
        long long mid = lo+(hi-lo+1)>>1;
        if(proof(mid)) lo = mid;    
        else hi = mid - 1;
    }
    cout << lo << endl;

    return 0;
}
