#include <bits/stdc++.h>
using namespace std;

int main() {
map<char, string> Map;

	Map['a'] = "@";
	Map['n'] = "[]\\[]";
	Map['b'] = "8";
	Map['o'] = "0";
	Map['c'] = "(";

Map['p'] = "|D";
Map['d'] = "|)";

Map['q'] = "(,)";

Map['e'] = "3";

Map['r'] = "|Z";

Map['f'] = "#";

Map['s'] = "$";

Map['g'] = "6";

Map['t'] = "\'][\'";

Map['h'] = "[-]";

Map['u'] = "|_|";

Map['i'] = "|";

Map['v'] = "\\/";

Map['j'] = "_|";

Map['w'] = "\\/\\/";

Map['k'] = "|<";

Map['x'] = "}{";

Map['l'] = "1";

Map['y'] = "`/";

Map['m'] = "[]\\/[]";

Map['z'] = "2";

int c;

while ((c = getchar()) != EOF) {
	if (isalpha(c)) printf("%s", Map[tolower(c)].c_str());
	else putchar(c);
}

	return 0;
}