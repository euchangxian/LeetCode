#include <array>
#include <cstddef>
#include <vector>

using namespace std;
class Solution {
 public:
  int largestUniqueNumber(vector<int>& nums) {
    // 1 <= nums.length <= 2000
    // 0 <= nums[i] <= 1000
    // With this constraint, we can simply use a std::array to maintain the
    // frequency of occurences of elements.
    // Then iterate from the back/largest element. If the frequency is 1, then
    // that will be our answer.
    // O(n). Can we do better?
    std::array<int, 2001> count{};
    for (int num : nums) {
      ++count[num];
    }

    for (int num = 2000; num >= 0; --num) {
      if (count[num] == 1) {
        return num;
      }
    }
    // if we reach here, that means no valid nums exists.
    return -1;
  }
};
