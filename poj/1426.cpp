#include <iostream>
using namespace std;

bool found;
int depth;
char s[101];
int n;
void dfs(int d, int sum) {
    if (found) return;
    if (d == depth) {
        if (sum == 0) {
            found = 1;
            s[depth] = 0;
            cout << s << '\n';
        }
        return;
    }
    for (int i=d==0; i<2; ++i) {
        s[d] = i + '0';
        dfs(d+1, (10 * sum + i) % n);
    }
}

int main() {
    while (cin>>n, n) {
        depth = 0;
        found = 0;
        while (!found) {
            depth++;
            dfs(0, 0);
        }
    }
    return 0;
}