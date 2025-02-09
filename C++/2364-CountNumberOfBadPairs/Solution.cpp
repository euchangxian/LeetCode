#include <cstddef>
#include <cstdlib>
#include <unordered_map>
#include <vector>

using i64 = long long;
class Solution {
 public:
  i64 countBadPairs(std::vector<int>& nums) {
    // A pair of indices (i, j) is bad if
    // - i < j
    // - j - i  !=  nums[j] - nums[i].
    //
    // Rewriting, a good pair is:
    // j - i = nums[j] - nums[i]
    // nums[i] - i = nums[j] - j
    // Thus, count good pairs, then minus from total pairs.
    const int n = nums.size();
    const i64 total = static_cast<i64>(n) * (n - 1) / 2;

    i64 goodPairs = 0LL;
    std::unordered_map<i64, i64> seen;
    seen.reserve(nums.size());
    for (int i = 0; i < nums.size(); ++i) {
      i64 target = nums[i] - i;
      goodPairs += seen[target]++;
    }
    return total - goodPairs;
  }
};
