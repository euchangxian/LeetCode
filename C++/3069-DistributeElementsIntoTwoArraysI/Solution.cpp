#include <algorithm>
#include <vector>

class Solution {
 public:
  std::vector<int> resultArray(std::vector<int>& nums) {
    // distribute 1-indexed nums between arr1 and arr2 using n operations.
    // In the 1st op: append nums[1] to arr1.
    // In the 2nd op: append nums[2] to arr2.
    // In the ith op: if arr1.back() > arr2.back(),
    // - append nums[i] to arr1, else
    // - append to arr2
    // result is formed by concatenating arr1 and arr2.
    const auto n = static_cast<int>(nums.size());
    std::vector<int> arr2;
    arr2.reserve(n / 2 + 1);
    arr2.emplace_back(nums[1]);
    auto idx1 = 0;  // back of arr1
    for (auto i = 2; i < n; ++i) {
      if (nums[idx1] > arr2.back()) {
        nums[++idx1] = nums[i];
      } else {
        arr2.emplace_back(nums[i]);
      }
    }
    std::copy(arr2.begin(), arr2.end(), nums.begin() + idx1 + 1);
    return nums;
  }
};
