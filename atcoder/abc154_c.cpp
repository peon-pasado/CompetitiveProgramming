#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin>>n;
	int arr[n + 2];
	for(int i=0;i<n;++i){
	    cin>>arr[i];
	}
	sort(&arr[0], &arr[n]);
	bool distinto = true;
	for (int i = 1; i < n; ++i) {
		if (arr[i] == arr[i-1]) {
			distinto = false;
		}
	}
	if (!distinto) cout << "NO\n";
	else cout<<"YES"<<'\n';
	return 0;
}