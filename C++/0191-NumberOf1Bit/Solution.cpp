#include <algorithm>
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
  int hammingWeight(int n) {
    int count = 0;
    while (n > 0) {
      count += n & 1;

      n >>= 1;
    }

    return count;
  }
};
