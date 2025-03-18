#include <algorithm>
#include <vector>

class Solution {
 public:
  std::vector<int> frequencySort(std::vector<int>& nums) {
    std::vector<int> frequencies(201, 0);
    for (int num : nums) {
      ++frequencies[num + 100];
    }
    std::sort(nums.rbegin(), nums.rend());

    std::stable_sort(nums.begin(), nums.end(),
                     [&frequencies](int num1, int num2) {
                       return frequencies[num1 + 100] < frequencies[num2 + 100];
                     });

    return nums;
  }
};
