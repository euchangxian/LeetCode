#include <algorithm>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  int longestConsecutive(std::vector<int>& nums) {
    // Unsorted array of numbers, return length of longest consecutive elements
    // sequence in O(N) time.
    //
    // If the number is the start of a sequence, i.e., no smaller number than
    // it exists, then start counting.
    std::unordered_set<int> present;
    present.reserve(nums.size());
    for (int num : nums) {
      present.insert(num);
    }

    int result = 0;
    for (auto num : present) {
      if (!present.contains(num - 1)) {
        auto currLen = 1;
        while (present.contains(++num)) {
          ++currLen;
        }
        result = std::max(result, currLen);
      }
    }
    return result;
  }
};
