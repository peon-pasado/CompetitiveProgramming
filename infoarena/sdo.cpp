/**
 * @author Miguel Mini
 * @tag order_statistic
 * @idea
 *      - use nth_element algorithm.
 */ 

#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e6 + 10;
int arr[maxn];

ifstream fin("sdo.in");
ofstream fout("sdo.out");

int main() {
  int n, k;
  fin >> n >> k;
  for (int i = 0; i < n; ++i) fin >> arr[i];
  nth_element(arr, arr+k-1, arr+n);
  fout << arr[k-1] << '\n';
  return 0;
}