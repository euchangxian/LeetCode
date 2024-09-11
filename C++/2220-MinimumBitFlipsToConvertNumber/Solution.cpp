#include <algorithm>
#include <array>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
public:
  int minBitFlips(int start, int goal) {
    // 0 <= start, goal <= 10e9
    int requiredFlips = start ^ goal;

    // Count bits
    // int count = 0;
    // while (requiredFlips) {
    //  count += requiredFlips & 1;
    //  requiredFlips >>= 1;
    //}

    int count = __builtin_popcount(requiredFlips);
    return count;
  }
};
