#include <bits/stdc++.h>
using namespace std;

vector<int> solution;
int disp;
const int maxn = 22;
int a[maxn];
int N, n;

//a0, a1, a2, ...., a(n-1)
//        apos, apos+1 

vector<int> v;
void backtracking(int pos, int N) {
	if (pos == n) {
		if (disp > N) {
			disp = N;
			solution = v;
		}
		return;
	}
	
	backtracking(pos+1, N);
	if (a[pos] <= N) {
		v.push_back(a[pos]);
		backtracking(pos+1, N-a[pos]);
		v.pop_back();
	}
}

int main() {
	while (cin >> N >> n) {
		for (int i = 0; i < n; ++i) cin >> a[i];
		solution.clear();
		disp = N;
		backtracking(0, N);
		for (int e : solution) cout << e << " ";
		cout << "sum:" << N - disp << endl;
	}
	return 0;
}