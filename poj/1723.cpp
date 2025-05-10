#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int mediana(vector<int> v) {
	sort(v.begin(), v.end());
	return v[v.size() / 2];
}

int calc(vector<int> v) {
	// sum (v[i] - mediana(v))
	int me = mediana(v);
	int sum = 0;
	for (int i = 0; i < v.size(); ++i) {
		sum += abs(v[i] - me);
	}
	return sum;
}

int main() {
	int n;
	cin >> n;
	vector<int> x(n), y(n);
	for (int i = 0; i < n; ++i) {
		cin >> x[i] >> y[i];
	}
	sort(x.begin(), x.end());
	for (int i = 0; i < n; ++i) {
		x[i] = i - x[i];
	}
	cout << calc(x) + calc(y) << '\n';
	return 0;
}