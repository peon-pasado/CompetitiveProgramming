#include <bits/stdc++.h>
using namespace std;

int main() {

	int t;
	scanf ("%d\n", &t);
	while (t--) {
		int n = 0;
		int c;
		while ((c = getchar()) != '\n' and c != EOF) n++;
		printf("%d\n", n);
	}

	return 0;
}