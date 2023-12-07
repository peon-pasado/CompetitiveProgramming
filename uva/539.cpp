/**
 * @idea backtracking
 * 
 * - simule every "path", dont need optimization.
 * 
**/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <climits>
#include <vector>
#define N 30

using namespace::std;
typedef vector<int> vi;

int n, m, maximum;
vi graph[N];
bool visit_edge[N][N];

void dfs(int source, int suma) { 
    maximum = max(maximum, suma);
    for (int i = 0; i < int(graph[source].size()); ++i) {
        int q = graph[source][i];
        if(!visit_edge[source][q]){
            visit_edge[q][source] = visit_edge[source][q] = 1;
            dfs(q, suma + 1);
            visit_edge[q][source] = visit_edge[source][q] = 0;
        }
    }
}

int main(){
    while(scanf("%d %d", &n, &m), n + m){
        for(int i = 0; i < m; ++i){
            int a, b;
            scanf("%d %d", &a, &b);
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        maximum = INT_MIN;
        for(int i = 0; i < n; ++i) dfs(i, 0);
        printf("%d\n", maximum);
        for(int i = 0; i < n; ++i) graph[i].clear();
    }
    return 0;
}
