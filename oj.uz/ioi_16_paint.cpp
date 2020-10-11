/**
 *  @author Miguel Mini
 *  @tag dp
 *  @idea:
 *
 *    - we build preffix and suffix dp for all k.
 *
 *    - check if a point can be black and white, white
 *    is easy, for black can use accumulate sums.
 *
**/

#include <bits/stdc++.h>
#include "paint.h"
using namespace std;

const int maxn = 2e5 + 5;
const int maxk = 102;

bool memoL[maxn][maxk][2], memoR[maxn][maxk][2];
int sum[maxn][2];
char s[maxn];
int c[maxk];
char result[maxn];
int cnt[maxn];


string solve_puzzle(string s, vector<int> c) {
    int n = s.size();
    int k = c.size();
    for (int i = 1; i <= n; ++i) {
        sum[i][0] = sum[i-1][0] + (s[i-1] == '_');
        sum[i][1] = sum[i-1][1] + (s[i-1] == 'X');
    }
    memoL[0][0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        memoL[i][0][0] = memoL[i-1][0][0] && (s[i-1] != 'X');
    }
    for (int j=1; j<=k; ++j) {
        for (int i = 1; i <= n; ++i) {
            if (i >= c[j-1]) {
                memoL[i][j][1] = memoL[i-c[j-1]][j-1][0] && (sum[i][0] - sum[i-c[j-1]][0] == 0);
            }
            memoL[i][j][0] = (memoL[i-1][j][0] || memoL[i-1][j][1]) && (s[i-1] != 'X');
        }
    }
    memoR[n+1][0][0] = 1;
    for (int i = n; i >= 1; --i) {
        memoR[i][0][0] = memoR[i+1][0][0] && (s[i-1] != 'X');
    }
    for (int j = 1; j <= k; ++j) {
        for (int i = n; i >= 1; --i) {
            if (i + c[k-j] - 1 <= n) {
                memoR[i][j][1] = memoR[i+c[k-j]][j-1][0] && (sum[i+c[k-j]-1][0] - sum[i-1][0] == 0);
            }
            memoR[i][j][0] = (memoR[i+1][j][0] || memoR[i+1][j][1]) && (s[i-1] != 'X');
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            if (memoL[i][j][1] && memoR[i+1][k-j][0]) {
                cnt[i+1] -= 1;
                cnt[i-c[j-1]+1] += 1;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        cnt[i] += cnt[i-1];
    }
    string result = "";
    for (int i = 1; i <= n; ++i) {
        if (cnt[i] > 0) {
            bool white = false;
            for (int j = 0; j <= k; ++j) {
                if (memoL[i][j][0] && memoR[i][k-j][0]) {
                    white = true;
                    break;
                }
            }
            if (white) result += '?';
            else result += 'X';
        } else {
            result += '_';
        } 
    }
    return result;
}
