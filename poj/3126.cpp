#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int maxn = 1e4;
bool comp[maxn];
vector<int> prime;
void sieve() {
    for (int i=2; i<maxn; ++i) {
        if (!comp[i]) {
            prime.push_back(i);
        }
        for (int j=0; j<(int)prime.size(); ++j) {
            int p = prime[j];
            if (p * i >= maxn) break;
            comp[p * i] = 1;
            if (i % p == 0) break;
        }
    }
}

int dist[maxn];
const int ten[] = {1, 10, 100, 1000};
void dfs(int s, int t, int depth, int extra) {
    dist[s] = depth;
    if (s == t) return;
    if (dist[s] + extra >= dist[t]) return;
    for (int i=0; i<4; ++i) {
        int d = (s / ten[i]) % 10;
        int e = (t / ten[i]) % 10;
        for (int j=(i==3); j<10; ++j) if (j != d) {
            int next_p = s + (j - d) * ten[i];
            if (comp[next_p]) continue;
            if (dist[next_p] <= depth + 1) continue;
            dfs(next_p, t, depth + 1, extra + ((d==e) ? 1 : -(j==e)));
        }
    }
} 


int main() {
    sieve();
    int t;
    cin>>t;
    while (t--) {
        int s, t;
        cin>>s>>t;
        memset(dist, 1, sizeof dist);
        int sum = 0;
        for (int i=0; i<4; ++i) {
            if ((s / ten[i]) % 10 != (t / ten[i]) % 10) {
                sum++;
            }
        }
        dfs(s, t, 0, sum);
        if (dist[t] > 10000) cout << "Impossible" << '\n';
        else cout << dist[t] << '\n';
    }
    return 0;
}