#include <iostream> //#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

int main() {
	int t;
	cin >> t;
	for (int i = 1; i <= t; ++i) {
		int n;
		cin >> n;
		int arr[50];
		for (int j = 0; j < n; ++j) {
			cin >> arr[j];
		}
		sort(arr, arr+n);
		//1 1 2 3 3 3 3 3 3 3 3 3 4 5 6 7 7 7
		int sum = 0;
		int cnt = 0;
		for (int j = 0; j < n; ++j) {
			cnt += 1;
			if (j + 1 < n && arr[j+1] == arr[j]) {
				
			} else {
				sum += (arr[j] + 1) * ((cnt + arr[j]) / (arr[j] + 1));
				cnt = 0;
			}
		}
		cout << "Case " << i << ": " << sum << endl;
	}
	return 0;
}