#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> x(n); //declarar n elementos
	for (int i = 0; i < n; ++i) cin >> x[i]; //leer n elementos
	sort(x.begin(), x.end()); //ordenar todo el vector
	int mini = 0;
	int last = -1e9;
	for (int i = 0; i < n; ++i) { 
		if (last + 1 >= x[i]) continue;
		last = x[i] + 1; //pasar con el mas a la derecha posible
		mini += 1;
	}
	int maxi = 0;
	last = -1e9;
	vector<int> pos(n+2);
	for (int i = 0; i < n; ++i) {
		last = min(max(x[i] - 1, last + 1), x[i] + 1); //pasar con el mas a la izquierda posible
		pos[last] = 1;
	}
	for (int i = 0; i <= n + 1; ++i) maxi += pos[i];
	
	cout << mini << " " << maxi << endl;
	return 0;
}