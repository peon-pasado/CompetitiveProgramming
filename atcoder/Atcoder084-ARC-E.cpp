/**
 * @author Miguel Mini
 * @tag multicase, greedy
 * @idea
 *      - if k is even 
 *      answer is:
 * 
 *          k/2 k ...(n-3)k... k 
 * 
 *      - if k is odd we can use 
 *      answer:
 * 
 *          (k+1)/2 + ... + (k+1)/2
 * 
 *      but there is a gap by empty
 *      elements: 
 *  
 *          by odd elements: 
 * 
 *              (k^i - 1) / (k - 1) is odd
 * 
 *          then we must consider a previous
 *          element instead.
 *             
 *      if k == 1:
 *          we must erase n/2 ones.
 *      else:
 *          we can see that number of modified
 *          elements is at most logk(n) x n
 *          amortized to n + logk(n).
 * 
 * @complexity O(n + logk(n))
 */ 

#include <bits/stdc++.h>
using namespace std;

int main() {
    int k, n;
    cin >> k >> n;
    if (k%2 == 0) {
        cout << k/2;
        for (int i = 2; i <= n; ++i) {
            cout << " " << k;
        }
        cout << endl;
    } else {
        vector<int> d;
        for (int i = 1; i <= n; ++i) {
            d.push_back(k/2 + 1);
        }
        int delta = n / 2;
        while (delta--) {
            if (d.back() > 1) {
                d.back()--;
                while (d.size() < n) d.push_back(k);
            } else d.pop_back();
        }
        for (int v : d) {
            cout << v << " ";
        }
        cout << endl;
    }
    return 0;
}