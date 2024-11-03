#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
class Solution {
 public:
  vector<string> buildArray(vector<int>& target, int n) {
    // two Operations: "Push", "Pop"
    // incoming data stream from [1..n]
    // Return operations to build the target.
    // All elements must be read in, unless the target is already built.
    // For every element that is IN the target, one operation "PUSH" is needed.
    // For every element that is NOT in the target, and is BEFORE the last
    // element, one "PUSH" and one "POP" is needed.
    // Maintain the idx

    // 1 op for each element in target, 2 ops for everything else
    std::vector<std::string> operations;
    operations.reserve(target.size() + 2 * (n - target.size()));

    int tIdx = 0;
    for (int i = 1; i <= n; ++i) {
      if (tIdx >= target.size()) {
        // ignore
        continue;
      }
      if (i == target[tIdx]) {
        operations.emplace_back("Push");
        ++tIdx;
        continue;
      }
      operations.emplace_back("Push");
      operations.emplace_back("Pop");
    }
    return operations;
  }
};
