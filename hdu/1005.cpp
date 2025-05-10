#include <iostream>
using namespace std;

int main() {
	int a, b, n;
	while (cin >> a >> b >> n, a+b+n) {
		n -= 1;
		a %= 7; b %= 7;
		typedef pair<int, int> pii;
		pii x0 = {1, 1};
		auto f = [&](pii x) {return pii(x.second, (b * x.first + a * x.second) % 7);};

		pii tortoise = f(x0);
		pii hare = f(f(x0));

		while (tortoise != hare) {
			tortoise = f(tortoise);
			hare = f(f(hare));
		}
		
    	int mu = 0;
    	tortoise = x0;
    	while (tortoise != hare) {
        	tortoise = f(tortoise);
        	hare = f(hare);
        	mu += 1;
    	}
 
    	int lam = 1;
    	hare = f(tortoise);
    	while (tortoise != hare) {
        	hare = f(hare);
        	lam += 1;
    	}
	
		pii ans = x0;
		if (n > mu) n = (n - mu) % lam + mu;
		for (int i = 0; i < n; ++i) ans = f(ans);
		cout << ans.first << endl;
	} 
	return 0;
}