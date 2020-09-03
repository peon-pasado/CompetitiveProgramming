/**
 * @name Miguel Mini
 * @tag BIT, permutation
 * @idea
 *      - we can see revert prefix x + revert prefix (x-1)
 *      as cyclic shift of the first x elements.
 * 
 *      - we can see that a cyclic shift is the same as 
 *      removing the first element and putting it in an 
 *      arbitrary position
 *      
 *      - we can take the first item and greedily put it 
 *      at the bottom of the list considering how many 
 *      larger numbers have not come up.
**/
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 10;
int ft[maxn];

void upd(int pos) {
	while (pos < maxn) {
		ft[pos]++;
		pos += pos&-pos;
	}
}

int qry(int pos) {
	int ans = 0;
	while (pos > 0) {
		ans += ft[pos];
		pos -= pos&-pos;
	}
	return ans;
}

int main() {
    freopen("permsort2.in", "r", stdin);
    freopen("permsort2.out", "w", stdout);
	int n;
	scanf("%d", &n);
	printf("%d\n", 2*n);
	for (int i = 1; i <= n; ++i) {
		int x;
		scanf("%d", &x);
		int t = qry(x) - i + 1 + n;
		printf("P %d\n", t);
		printf("P %d\n", max(1, t-1));
		upd(x);
	}
	return 0;
}
