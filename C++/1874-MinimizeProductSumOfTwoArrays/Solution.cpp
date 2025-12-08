#include <algorithm>
#include <array>
#include <vector>

constexpr auto MAX_VAL = 100;
class Solution {
 public:
  int minProductSum(std::vector<int>& nums1, std::vector<int>& nums2) {
    // product sum is equal to a[i]*b[i] for all 0<=i<a.length
    // Return the minimum product sum by rearranging the elements in nums1.
    //
    // Pair min with max.
    // Sort both and multiply.
    // std::ranges::sort(nums1);
    // std::ranges::sort(nums2, std::greater<>{});
    //
    // return std::transform_reduce(std::execution::par, nums2.begin(),
    //                              nums2.end(), nums1.begin(), 0,
    //                              std::plus<>{}, std::multiplies<>{});
    std::array<int, MAX_VAL + 1> freq1{};
    std::array<int, MAX_VAL + 1> freq2{};

    for (auto x : nums1) {
      ++freq1[x];
    }
    for (auto x : nums2) {
      ++freq2[x];
    }

    int result = 0;
    int i = 1;
    int j = MAX_VAL;
    while (i <= MAX_VAL && j >= 0) {
      while (i <= MAX_VAL && freq1[i] == 0) {
        ++i;
      }
      while (j >= 0 && freq2[j] == 0) {
        --j;
      }

      if (i <= MAX_VAL && j >= 0) {
        auto count = std::min(freq1[i], freq2[j]);
        result += count * (i * j);

        freq1[i] -= count;
        freq2[j] -= count;
      }
    }
    return result;
  }
};
