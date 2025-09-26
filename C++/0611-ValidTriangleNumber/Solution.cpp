#include <algorithm>
#include <iterator>
#include <vector>

class Solution {
 public:
  int triangleNumber(std::vector<int>& nums) {
    const auto n = static_cast<int>(nums.size());
    std::ranges::sort(nums);

    auto feasible = [](int a, int b, int c) {
      return (a + b > c) && (a + c > b) && (b + c > a);
    };

    int result = 0;

    // fix c in the equation.
    for (int k = n - 1; k >= 2; --k) {
      int left = 0;
      int right = k - 1;

      while (left < right) {
        if (feasible(nums[left], nums[right], nums[k])) {
          // if a+b works, then any number between a and b will also work.
          result += right - left;
          --right;
        } else {
          ++left;
        }
      }
    }
    return result;
  }
  int triangleNumberBinarySearch(std::vector<int>& nums) {
    // Return the number of triplets chosen from the array that can make
    // triangles if we take them as the sides.
    //
    // Triangle Rule: Sum of the length of two sides must be GTE the
    // third side, i.e.,
    // a + b >= c && a + c >= b && b + c >= a
    //
    // I suppose triplets are unordered.
    // Naive brute force is O(N^3), too slow, given n<=1000.
    // A more sophisticated approach is needed.
    // Sorting seems plausible. For each fixed point a, find b and c.
    // Not easy to do that. Fix two points? 1E4=>O(N^2), 1E3=>O(N^2logN)
    // Given a and b, find c such that a <= b <= c, and that fulfils the
    // triangle equation.
    // Is there a monotonic property in c? Naively, seems like if the triangle
    // equation is not valid => c is too big, shift left.
    const auto n = static_cast<int>(nums.size());
    std::ranges::sort(nums);

    auto feasible = [](int a, int b, int c) {
      return (a + b > c) && (a + c > b) && (b + c > a);
    };

    int result = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        auto start = nums.begin() + j + 1;
        auto it = std::lower_bound(start, nums.end(), nums[i] + nums[j]);
        result += std::distance(start, it);
      }
    }
    return result;
  }
};
