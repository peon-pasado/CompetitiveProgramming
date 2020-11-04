/**
 *  @author Miguel Mini
 *  @tag constructive, greedy, tree, dp, brute_force
 *  @idea
 *      - use backward construction
 *  
 *      - in each step solve the "brute force problem"
 *      without the new member.
 *
 *      - for 1, we can add the nwe member confidence to the 
 *      host confidence
 *
 *      - for 2, we can maximize the confidence of the host
 *      with the new member confidence
 *
 *      - for 0, we can add confidence of the new member
 *      to the answer and subtract of the host confidence
 *
 *  @complexity O(n)
**/

#include <bits/stdc++.h>
#include "friend.h"
using namespace std;
 
int findSample(int n, int confidence[], int host[], int protocol[]) {
    int extra = 0;
    for (int i = n-1; i > 0; --i) {
        if (protocol[i] == 1) {
            confidence[host[i]] += confidence[i];                
        } else if (protocol[i] == 2) {
            confidence[host[i]] = max(confidence[host[i]], confidence[i]);
        } else {
            extra += confidence[i];
            confidence[host[i]] = max(0, confidence[host[i]] - confidence[i]);
        }
    }
    return confidence[0] + extra;
}
