#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e4 + 10;
int a[maxn];
int n, m;

int main() {
  while (cin >> n) {
    for (int i = 0; i < n; ++i) {
      scanf("%d", a+i);
    }
    sort(a, a+n);
    scanf("%d", &m);
    int x, y;
    for (int i = 0; i + 1 < n; ++i) {
      int lo = i+1, hi = n-1;
      while (lo < hi) {
        int mid = lo + (hi - lo + 1) / 2;
        if (a[i] + a[mid] <= m) lo = mid;
        else hi = mid-1;
      }
      if (a[i] + a[lo] == m) {
        x = a[i];
        y = a[lo];
      }
    }
    cout << "Peter should buy books whose prices are "<<x<<" and "<<y<<".\n" << endl;
  }
  return 0;
}