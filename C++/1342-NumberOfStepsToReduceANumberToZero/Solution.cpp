#include <algorithm>
#include <array>
#include <bitset>
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
  int numberOfSteps(int num) {
    // If num is even, divide by 2. Otherwise subtract 1.
    // Return the number of steps to reduce num to zero.
    // Naively, simulation works. O(logn)
    // Can we do better? Sounds like a bit counting question
    // num = 14 = 0000 1110 : even, divide by 2 i.e. right shift
    // num = 7 =  0000 0111 : odd, minus 1
    // num = 6 =  0000 0110 : even, divide by 2 i.e. right shift
    // num = 3 =  0000 0011 : odd, minus 1
    // num = 2 =  0000 0010 : even, divide by 2
    // num = 1 =  0000 0001 : odd, minus 1
    // num = 0 =  0000 0000
    // Therefore, suppose k is the number of '1' bits. Then there must be
    // k 'minus 1' operations at least.
    // The number of right shifts will be the furthest '1' bit i.e. the
    // most-significant '1' bit.

    int dist = 0;
    int count = 0;
    for (int i = 0; i < 32; ++i) {
      bool digit = (num >> i) & 1;
      count += digit;

      if (digit) {
        dist = i;
      }
    }

    return count + dist;
  }
};
