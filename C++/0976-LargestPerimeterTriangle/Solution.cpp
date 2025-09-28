#include <algorithm>
#include <vector>

constexpr auto feasible = [](int a, int b, int c) { return (a + b > c); };

class Solution {
 public:
  int largestPerimeter(std::vector<int>& nums) {
    const auto n = static_cast<int>(nums.size());
    std::ranges::sort(nums);
    for (int k = n - 1; k >= 2; --k) {
      if (feasible(nums[k - 2], nums[k - 1], nums[k])) {
        return nums[k - 2] + nums[k - 1] + nums[k];
      }
    }
    return 0;
  }

  int largestPerimeterNaive(std::vector<int>& nums) {
    // nums[i] represent possible sides of a triangle.
    // Return the largest perimeter of a triangle formed from three indices
    // i, j, k.
    // Return 0 if not possible.
    //
    // Triangle Inequality: a + b > c, if a <= b <= c
    const auto n = static_cast<int>(nums.size());

    std::ranges::sort(nums);
    int result = 0;
    for (int k = n - 1; k >= 2; --k) {
      int i = 0;
      int j = k - 1;
      while (i < j) {
        if (feasible(nums[i], nums[j], nums[k])) {
          result = std::max(result, nums[i] + nums[j] + nums[k]);
        }
        ++i;
      }
    }
    return result;
  }
};
