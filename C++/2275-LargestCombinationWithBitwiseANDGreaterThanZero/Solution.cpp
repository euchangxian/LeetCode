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
  int largestCombination(vector<int> &candidates) {
    // Consider two 1-bit numbers a and b. For the bitwise AND of the two to be
    // zero, i.e., a & b = 0, either a or b must be 0.
    // Therefore, for n k-bits (32 for int) numbers, the combined bitwise AND
    // of a subset will be 0 iff all the 1 bits are not common.
    // E.g. [16,17,71,62,12,24,14]
    // 16 = 0 0 1 0 0 0 0
    // 17 = 0 0 1 0 0 0 1
    // 71 = 1 0 0 0 1 1 1
    // 62 = 0 1 1 1 1 1 0
    // 12 = 0 0 0 1 1 0 0
    // 24 = 0 0 1 1 0 0 0
    // 14 = 0 0 0 1 1 1 0
    //
    // It is easy to see that the largest combination can be obtained from
    // comparing the i-th bit of each number and taking the position with the
    // most number of common bits; That combination will not be 0.
    int result = 0;
    for (int pos = 0; pos < 32; ++pos) {
      int count = 0;
      for (int const &num : candidates) {
        count += (num >> pos) & 1;
      }

      result = max(result, count);
    }
    return result;
  }
};
