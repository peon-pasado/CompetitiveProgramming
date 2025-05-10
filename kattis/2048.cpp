#include <bits/stdc++.h>
using namespace std;

int answer[5][5];
int a[5][5];

void Left() {
	memset(answer, 0, sizeof answer);
	for (int i = 0; i < 4; ++i) {
		int pos = 0;
		for (int j = 0; j < 4; ++j) {
			if (a[i][j] == 0) continue;
			else {
				if (answer[i][pos] == 0) answer[i][pos] = a[i][j];
				else if (answer[i][pos] == a[i][j]) answer[i][pos] <<= 1, pos += 1;
				else answer[i][pos+1] = a[i][j], pos += 1;
			}
		}
	}

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			a[i][j] = answer[i][j];
		}
	}
}

void rotate() {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			answer[3-j][i] = a[i][j];
		}
	}

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			a[i][j] = answer[i][j];
		}
	}
}

void print() {	
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) 
			cout << a[i][j] << " ";
		cout << endl;
	}
}


int main() {

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			cin >> a[i][j];
		}
	}

	int x;
	cin >> x;
	for (int i = 1; i <= x; ++i) rotate();

	Left();

	for (int i = 1; i <= 4-x; ++i) rotate();

	print();

	return 0;
}