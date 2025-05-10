#include <bits/stdc++.h>
using namespace std;

typedef complex<double> cd;
const double tao = 2 * acos(-1);

void fft(vector<cd>& A, bool invert) {
	int n = A.size();
	if (n == 1) {
		return;
	}
	vector<cd> A0(n>>1), A1(n>>1);
	for (int i = 0; i+i < n; ++i) {
		A0[i] = A[i<<1];
		A1[i] = A[i<<1|1];
	}
	fft(A0, invert);
	fft(A1, invert);
	double angle = tao / n * (invert ? -1 : 1);
	cd w(1), wn(cos(angle), sin(angle));
	for (int i = 0; i+i < n; ++i) {
		A[i] = A0[i] + w * A1[i];
		A[i+(n>>1)] = A0[i] - w * A1[i];
		if (invert) {
			A[i] /= 2;
			A[i+(n>>1)] /= 2;
		}
		w *= wn;
	}
}

vector<int> multiply(vector<int>& A, vector<int>& B) {
	vector<cd> fA(begin(A), end(A));
	vector<cd> fB(begin(B), end(B));
	int n = 1;
	while (n < A.size() + B.size()) n <<= 1;
	fA.resize(n); fB.resize(n);
	fft(fA, 0);
	fft(fB, 0);
	for (int i = 0; i < n; ++i) {
		fA[i] *= fB[i];
	}
	fft(fA, 1);
	vector<int> res(n);
	for (int i = 0; i < n; ++i) {
		res[i] = round(fA[i].real());
	}
	int carry = 0;
	for (int i = 0; i < n; ++i) {
		res[i] += carry;
		carry = res[i] / 10;
		res[i] %= 10;
	}
	return res;
}

int main() {
	int n;
	scanf("%d", &n);
	while (n--) {
		string A, B;
		cin >> A >> B;
		reverse(begin(A), end(A));
		reverse(begin(B), end(B));
		vector<int> nA(A.size());
		vector<int> nB(B.size());
		for (int i = 0; i < A.size(); ++i) {
			nA[i] = A[i] - '0';
		}
		for (int i = 0; i < B.size(); ++i) {
			nB[i] = B[i] - '0';
		}
		vector<int> C = multiply(nA, nB);
		while (C.size() > 1 and C.back() == 0) C.pop_back(); 
		reverse(begin(C), end(C));
		for (int i = 0; i < C.size(); ++i) {
			putchar(C[i] + '0');
		} puts("");
	}
	return 0;
}