#include <iostream>
#include <cstring>
using namespace std;

const int maxn = 1e6 + 10;
char t[maxn], p[maxn];
int b[maxn];

void prefix(char t[]) {
	b[0] = -1;
	for (int i = 1; t[i - 1]; ++i) {
		int j = b[i-1];
		while (j != -1 && t[i-1] != t[j]) j = b[j];
		b[i] = j + 1;
	}
}

void kmp(char p[]) {
	int m = strlen(p);
	prefix(p);
	int match = 0;
	getchar();
	char t = getchar();
	for (int i = 0; t != EOF; ++i) {
		while (match != -1 && t != p[match]) match = b[match];
		match += 1;
		if (match == m) {
			cout << "match in position: " << i - m + 2 << '\n';
			match = b[match];
		}
		t = getchar();
	}
}

int main() {
	
	while (cin >> p, p[0] != '.') {
		prefix(p);
		int n = strlen(p);
		int br = b[n];
		while (br != -1) {
			if (n % (n - br) == 0) {
				cout << n / (n - br) << '\n';
				break;
			}
			br = b[br];
		}
	}
	return 0;
}