/**
 * @idea solve with backtracking for every
 *      swimming. dp is slow for memory.
**/

#include <cstdio>
#include <cstdlib>
#include <cctype>
using namespace std;

const int maxN = 101;
const int maxM = 1001;
bool mn[maxN][maxM];
int t[maxN][maxM];
int n, m, K;
int res[maxM];

inline char readchar() {
    char c = getchar();
    while (c != 'v' && c != '$') 
        c = getchar();
    return c;
}

inline int readint() {
    int n = 0, s = 1;
    char c = getchar();
    while (!isdigit(c) && c != '-') 
        c = getchar();
    if (c == '-') {
        s = -1;
        c = getchar();
    }
    while (isdigit(c)) {
        n = (n<<3) + (n<<1) + c - '0';
        c = getchar();
    }
    return s * n;
}

int bt(int k, int px, int py, int v) {
    if (py>=n) py=n-1; 
    if (py<0) py=0;
    if (!py && k != K) return res[px];
    if (!k || px == m-1) return -1e9;
    int ans = -1e9;
    int delta = 0;
    if (mn[py][px]) delta += t[py][px]; 
    else if (py > 0) v += t[py][px];
    for (int d=-1; d<=1; ++d) {
        int temp = bt(k-1, px+1, py+v+d, v+d) + delta;
        if (temp > ans) ans = temp;
    }
    return ans;
}

int main() {
    while (n=readint(), m=readint(), K=readint(), n+m+K > 0) {
        for (int i=0; i<n; ++i)
            for (int j=0; j<m; ++j) {
                mn[i][j] = (readchar() == '$');
                t[i][j] = readint();
            }
        res[m-1] = mn[0][m-1] ? t[0][m-1] : 0;
        for (int i=m-2; i>=0; --i)
            res[i] = bt(K, i, 0, 0);
        printf("%d\n", res[0]);
    }
    return 0;
}