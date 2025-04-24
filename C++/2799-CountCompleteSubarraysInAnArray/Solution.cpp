#include <array>
#include <bitset>
#include <vector>

constexpr int MAX_N = 1000;
constexpr int MAX_VAL = 2000;

class Solution {
 public:
  int countCompleteSubarrays(std::vector<int>& nums) {
    // A subarray is complete if:
    // - the number of distinct elements in the subarray is equal to the
    //   number of distinct elements in the entire array.
    //
    // Sliding Window.
    // One pass to count distinct. Let this be D
    // Second pass sliding window. Let k be the number of distinct elements
    // in the window.
    // - Extend right while k < D
    // - Shrink left while k >= D. The number of subarrays can be counted at
    //   each iteration where k>=0, where if nums[l..r] is valid, then
    //   nums[0..r] must be valid too, i.e., subarrays ending at nums[r]
    //
    // NOTE: sliding window also handles the case where the last occurence of
    // an element is removed (when shrinking), resulting in subsequent subarrays
    // considered being no long complete.
    // In that case, `l` will not be incremented anymore past the last
    // occurence, and will still be correctly added to the result as the number
    // of prefixes ending at nums[r].
    const int n = nums.size();
    int unique = [&]() {
      std::bitset<MAX_VAL + 1> seen{};
      for (int x : nums) {
        seen[x] = 1;
      }
      return seen.count();
    }();

    int result = 0;
    std::array<int, MAX_VAL + 1> freq{};
    for (int l = 0, r = 0; r < n; ++r) {
      if (freq[nums[r]]++ == 0) {
        --unique;
      }

      while (unique == 0) {  // nums[l..r] is complete
        if (--freq[nums[l++]] == 0) {
          ++unique;
        }
      }
      result += l;
    }
    return result;
  }
};
