#include <algorithm>
#include <unordered_set>
#include <vector>

class Solution {
 public:
  int longestConsecutive(std::vector<int>& nums) {
    std::unordered_set<int> present;
    for (int num : nums) {
      present.insert(num);
    }

    int result = 0;
    for (int num : nums) {
      if (!present.count(num)) {
        continue;
      }

      int currentCount = 0;
      // find smallest number
      while (present.count(num)) {
        --num;
      }

      ++num;  // compensate for extra minus
      while (present.count(num)) {
        present.erase(num);
        ++num;
        ++currentCount;
      }
      result = std::max(result, currentCount);
    }
    return result;
  }
};
