#include <vector>

class Solution {
 public:
  // Reversing a subarray of size two is equivalent to swapping adjacent
  // elements. Since there can be any number of steps, the array can be made
  // equal to the target if they have the same elements.
  bool canBeEqual(std::vector<int>& target, std::vector<int>& arr) {
    std::vector<int> freq(1001, 0);

    for (int num : target) {
      ++freq[num];
    }

    int count = target.size();
    for (int num : arr) {
      if (freq[num]) {
        --freq[num];
        --count;
      }
    }
    return count == 0;
  }
};
