#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
 public:
  int longestConsecutive(vector<int>& nums) {
    unordered_set<int> present;
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
      result = max(result, currentCount);
    }
    return result;
  }
};
