#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
using namespace std;

long long ccw(int x1, int y1, int x2, int y2) {
	return x1 * 1ll * y2 - x2 *1ll* y1; 
}

const int maxn = 1e5 + 10;
int a[maxn], s[maxn], res[maxn];
int stck[maxn];
int m;

inline char nc() {
    static char buf[100000], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

inline bool _read(int &sum) {
    char ch = nc();
    if (ch == EOF)
        return 0;
    sum = 0;
    while (!(ch >= '0' && ch <= '9'))ch = nc();
    while (ch >= '0' && ch <= '9') sum = sum * 10 + ch - 48, ch = nc();
    return sum;
}

int main() {
	int n, k;
	while (_read(n) && _read(k)) {
		for (int i = 0; i < n; ++i) {
			_read(a[i]);
		}
		for (int i = 0; i < n; ++i) {
			s[i+1] = a[i] + s[i];
		}
		m = 0;
		double ans = 0;
		for (int i = 0; i < k; ++i) res[i] = 0;
		for (int i = k; i <= n; ++i) {
			while (m >= 2 && 
				ccw(i-k - stck[m-2], s[i-k] - s[stck[m-2]], stck[m-1] - stck[m-2], s[stck[m-1]] - s[stck[m-2]]) >= 0) {
					m--;
				}
			stck[m++] = i-k;
			res[i] = min(res[i-1], m - 1);
			while (res[i] + 1 < m && 
				ccw(i-stck[res[i]], s[i]-s[stck[res[i]]], i-stck[res[i]+1], s[i] - s[stck[res[i]+1]]) >= 0) {
					res[i]++;
				}
			ans = max(ans, (s[i] - s[stck[res[i]]]) * 1.0d / (i - stck[res[i]]));
		}
		printf("%.2lf\n", ans);
	}
	return 0;
}