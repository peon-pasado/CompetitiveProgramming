#include<bits/stdc++.h>
using namespace::std;

int n;

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        double res = 0.0;
        double one = 0.0;
        double none = 1.0;
        vector<double> C;
        for(int i = 1; i <= n; i++){
            double c;
            scanf("%lf", &c);
            if(c >= 0.5) res = max(res, c);
            else{
            	C.push_back(c);
            }
        }
        sort(C.rbegin(), C.rend());
        for (int i = 0; i < C.size(); ++i) {
        	one = one * (1 - C[i]) + none * C[i];
        	none *= (1 - C[i]);
        	res = max(res, one);
        }
        printf("%.8lf\n", res);
    }
    return 0;
}