    #include <iostream>
    #include <cstdio>
    #include <cstdlib>
    #include <cmath>
    #include <climits>
    #include <cstring>
    #include <string>
    #include <vector>
    #include <list>
    #include <queue>
    #include <stack>
    #include <map>
    #include <set>
    #include <bitset>
    #include <algorithm>
    #include <functional>
    #include <iomanip>
    #include <unordered_set>
    #include <unordered_map>
    using namespace std;
    #define LL long long
    int T, n, num, Xor, u, v;
    int main() {
        #ifdef LOCAL
            freopen("test.txt", "r", stdin);
    //    freopen("out.txt", "w", stdout);
        #endif // LOCAL
        ios::sync_with_stdio(true);
        scanf("%d", &T);
        while(T--) {
            Xor = 0;
            scanf("%d", &n);
            for(int i = 0; i < n; ++i) {
                scanf("%d", &num);
                Xor ^= num;
            }
            for(int i = 1; i < n; ++i) {
                scanf("%d%d", &u, &v);
            }
            if(Xor == 0) {
                printf("D\n");
            } else {
                printf("Q\n");
            }
        }
        return 0;
    }