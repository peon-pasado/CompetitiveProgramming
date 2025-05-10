#include <bits/stdc++.h>
using namespace std;
const long long N = 2000500;
long long n, t, sum[N], cnt[N];
long long mn = LLONG_MAX;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>n;

    for(int i = 0; i<n; i++){
        cin>>t;
        sum[t] += t;
        cnt[t]++;
    }
    if(cnt[0] == n){
        cout<<2<<endl;
        return 0;
    }


    cnt[0] = 0;
    sum[0] = 0;
    for(int i = 1; i<N; i++){
        sum[i] += sum[i-1];
        cnt[i] += cnt[i-1];
    }

    for(long long i = 2; i<N; i++){
        long long temp = 0;
        for(long long j = i; j<N; j+=i){
            long long m = j - (i + 1)/2;
            long long ltm = sum[m] - sum[j-i];
            ltm = ltm - (cnt[m] - cnt[j-i])*(j-i);
            long long gtm = sum[j] - sum[m];
            gtm = (cnt[j] - cnt[m])*j - gtm;
            temp += ltm + gtm;
        }
        mn = min(mn, temp);
    }

    cout<<mn<<endl;
    return 0;
}