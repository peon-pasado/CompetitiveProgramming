/**
 * @author Miguel Mini
 * @tag interactive
 * @idea
 *    - we can compute value
 *    of arr_1 with: 
 *    
 *      (query(1, 2) + query(1, 3) - query(2, 3)) / 2 
 *      
 *    - and obatain other elements with:
 *      
 *       query(1, i) - arr_1.
 * 
 * @complexity O(n)
 */ 
#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> sum(n + 1);
  for (int i = 2; i <= n; ++i) {
    cout << "? 1 " << i << endl;
    cin >> sum[i];
  }
  cout << "? 2 3" << endl;
  int x;
  cin >> x;
  sum[1] = (sum[2] + sum[3] - x) / 2;
  for (int i = 2; i <= n; ++i) {
    sum[i] -= sum[1];
  }
  cout << "!";
  for (int i = 1; i <= n; ++i) {
    cout << " " << sum[i];
  }
  cout << endl;
  return 0;
}