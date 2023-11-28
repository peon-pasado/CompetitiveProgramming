/**
 * @idea
 *
 *  - si n tiene multiplos de 2 o de 5, entonces
 *  tiene a lo mas 7 0s finales.
 * 
 *  - luego si phi(n) es pequeño, entonces
 *  entonces podemos encontrar -1 (mod n) y 
 *  le colocamos un 1 al final. 
 * 
 *  - en otro caso, cada 10^1, ..., 10^k son 
 *  todos distintos. Se cree que no hacen falta
 *  muchos.
**/

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