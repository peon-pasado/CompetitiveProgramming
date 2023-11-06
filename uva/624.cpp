#include <bits/stdc++.h>
using namespace std;

vector<int> solution;
int disp;
const int maxn = 22;
int a[maxn];
int N, n;

void backtracking(int pos, int N, vector<int>& v, vector<int>& solution, int& disp) {
	if (pos == n) {
		if (disp > N) {
			disp = N;
			solution = v;
		}
		return;
	}
	
	backtracking(pos+1, N, v, solution, disp);
	if (a[pos] <= N) {
		v.push_back(a[pos]);
		backtracking(pos+1, N-a[pos], v, solution, disp);
		v.pop_back();
	}
}

int main() {
	while (cin >> N >> n) {
		for (int i = 0; i < n; ++i) cin >> a[i];
		solution.clear();
		disp = N;
		vector<int> v;
		backtracking(0, N, v, solution, disp);
		for (int e : solution) cout << e << " ";
		cout << "sum:" << N - disp << endl;
	}
	return 0;
}