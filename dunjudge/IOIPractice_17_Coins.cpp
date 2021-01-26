/**
 *  @author Miguel Mini
 *  @tag xor
 *  @idea
 *      - we can encode the answer 
 *      in the xor over all element.
 *
**/


#include "coins.h"
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
vi coin_flips(vi b, int c) {
    int r = c;
    for (int i = 0; i < 64; ++i) {
        if (b[i]) r ^= i;
    }
    return {r};
}

int find_coin(vi b) {
    int r = 0;
    for (int i = 0; i < 64; ++i) {
        if (b[i]) r ^= i;
    }
    return r;
}
