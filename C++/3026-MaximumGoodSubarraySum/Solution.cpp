#include <algorithm>
#include <climits>
#include <cstddef>
#include <cstdlib>
#include <unordered_map>
#include <utility>
#include <vector>

using i64 = long long;
class Solution {
 public:
  long long maximumSubarraySum(std::vector<int>& nums, int k) {
    // Looked like a prefix sums question.
    // Got too fixated on storing the sums as key, and wondered how to find the
    // differences, if the sums would not inform of the abs diff between the
    // first and last element.
    //
    // Lol. Store the elements as the key, and the prefix sums excluding
    // the element as the value.
    // Allows quick lookup for x +- k.
    std::unordered_map<int, i64> prefixes;

    i64 prefix = 0;
    i64 maxSum = LLONG_MIN;
    for (i64 num : nums) {
      prefix += num;

      auto minusK = prefixes.find(num - k);
      auto plusK = prefixes.find(num + k);
      if (minusK != prefixes.end()) {
        maxSum = std::max(maxSum, prefix - minusK->second);
      }

      if (plusK != prefixes.end()) {
        maxSum = std::max(maxSum, prefix - plusK->second);
      }

      // NOTE: insert prefix up to, excluding the current element.
      // This allows us to perform the above operation prefix[i] - prefix[j],
      // since we want inclusive start and end.
      auto existing = prefixes.find(num);
      if (existing == prefixes.end() || existing->second >= prefix - num) {
        // only override if the existing prefix has a greater value, i.e.,
        // when minusing, will result in a smaller prefix than the current one.
        prefixes[num] = prefix - num;
      }
    }

    return maxSum == LLONG_MIN ? 0 : maxSum;
  }
};
