#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  std::vector<bool> isArraySpecial(std::vector<int>& nums,
                                   std::vector<std::vector<int>>& queries) {
    // An array is considered special if every pair of its adjacent elements
    // contain two numbers of different parity. Hm, i.e., even-odd or odd-even.
    // Naively, can iterate through every subarray. But can we do better?
    // prefix sums? Counting is one part, but the order can not be determined
    // from the sums.
    // Feels like DP. i.e., if prefix[i] is special, then subarray[i..j] may
    // be special depending on the length and the values of nums[i] and nums[j].
    // Nah....
    // Ah... What about finding indices that violate the special array property?
    // i.e., if nums[i] % 2 == nums[i-1] % 2, i.e., same parity, then index i
    // is a violation.
    std::vector<int> prefixViolations(nums.size(), 0);
    int prefix = 0;
    for (int i = 1; i < nums.size(); ++i) {
      if ((nums[i] & 1) == (nums[i - 1] & 1)) {
        ++prefix;
      }
      prefixViolations[i] = prefix;
    }

    std::vector<bool> answer;
    answer.reserve(queries.size());
    for (const auto& query : queries) {
      int start = query[0];
      int end = query[1];

      answer.push_back(prefixViolations[end] - prefixViolations[start] == 0);
    }

    return answer;
  }
};
