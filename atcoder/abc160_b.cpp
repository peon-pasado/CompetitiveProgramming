#include <bits/stdc++.h>
using namespace std;

int main(){
	long long x;
	cin >> x;
    long long a=(x-(x%500));
    int b=((x%500)-(x%5));
    if(x==0){
        cout<< 0 << '\n';
    }
    else if(x==1000000000){
        cout<< 2000000000 << '\n';
    }
    else if(x-a-b!=0){
        cout<< 2*a+b <<'\n';
    } else {
        cout << 2 * a + b << '\n';
    }
	return 0;
}