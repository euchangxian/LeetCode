#include <algorithm>
#include <vector>

class Solution {
 public:
  bool isMajorityElement(std::vector<int>& nums, int target) {
    // Given that we can get the majority element of an unsorted array in
    // O(N) time using boyer moores voting algorithm, can we do better in
    // a sorted array?
    // We do know that an element must appear > n/2 times in the array.
    // i.e., at least floor(n/2) + 1
    // Therefore, we look floor(n/2) distance ahead from the first occurence.
    const auto n = static_cast<int>(nums.size());
    const auto k = n / 2;
    auto firstOcc = std::ranges::lower_bound(nums, target);
    return (firstOcc + k < nums.end()) && *(firstOcc + k) == target;
  }
};
