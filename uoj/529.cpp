/**
 * @idea: 
 *      - De derecha a izquierda, cada 4 esta
 *      ligado a cada 1 disponible.
 * 
 *      - el ultimo 4 puede estar ligado al 
 *      ultimo 1:
 * 
 *          * ......15144 [ejemplo]
 * 
 *      - los siguientes 4s toman los 1s a 
 *      su izquierda que no han sido tomados.
 * 
 *          * 1 1 5 1 4 5 1 4 4
 *              (   ( )   ( ) )  [bad]
 *            x x o o x x x o x  [ok]  
 * 
 *      - de izquierda a derecha, los 14 antes del
 *      5 se usan primero mientras se pueda.  
 * 
 * 
 *          *  1 1 4 1 5 1 4 5 [ejemplo]
 * 
**/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 6e5 + 10;
char s[maxn];
int res[maxn / 6][6];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", s);
        int n = strlen(s);
        queue<int> p;
        vector<int> par(n);
        for (int i=n-1; i>=0; --i) {
            if (s[i] == '4') p.push(i);
            else if (s[i] == '1' && !p.empty()) par[i] = p.front(), p.pop(); 
        }
        int idx[4] = {0};
        for (int i=0; i<n; ++i) {
            if (s[i] == '1') {
                if (par[i]) {
                    if (idx[0] == idx[1]) {
                        res[idx[3]][4] = i; 
                        res[idx[3]++][5] = par[i];
                    } else {
                        res[idx[1]][1] = i;
                        res[idx[1]++][2] = par[i];
                    }
                } else {
                    res[idx[0]++][0] = i;
                }
            } else if (s[i] == '5') {
                res[idx[2]++][3] = i;
            }
        }
        for (int i=0; 6*i<n; ++i) {
            for (int j=0; j<6; ++j) {
                printf("%d%c", res[i][j] + 1, j==5?'\n':' ');
            }
        }
    }
    return 0;
}