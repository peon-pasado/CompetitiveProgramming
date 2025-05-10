#include <iostream>
#include <map>
using namespace std;

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; ++i) {
		int n;
		cin >> n;
		cin.get();
		map<int, string> id;
		for (int j = 0; j < n; ++j) {
			string name;
			getline(cin, name);
			int year = atoi(name.substr(name.size() - 4, 4).c_str());
			id[-year] = name.substr(0, name.size()-5);
		}
		//for (pair<int, string> yn : id)
		for (map<int, string>::iterator yn = id.begin(); yn != id.end(); ++yn) {
			cout << yn->second << '\n';
		}
	}
	
	return 0;
}