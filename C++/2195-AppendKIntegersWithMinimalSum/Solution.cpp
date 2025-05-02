#include <algorithm>
#include <vector>

using i64 = long long;
class Solution {
 public:
  i64 minimalKSum(std::vector<int>& nums, int k) {
    // Append k positive integers to nums such that the resultant array consist
    // of only unique integers, and the sum is minimised.
    // Wouldnt a std::set work? Iterating over "holes". Implementation is
    // "tricky" though.
    std::ranges::sort(nums);
    auto arithmeticSum = [](int n) { return n * (n + 1LL) / 2LL; };

    // sum of the k integers to be appended.
    i64 sum = 0LL;

    int prev = 0;
    for (int x : nums) {
      if (k <= 0) {
        break;
      }

      // (prev..x) inclusive start, exclusive end can be appended.
      if (int n = x - prev - 1; n > 0) {
        int take = std::min(n, k);
        sum += arithmeticSum(prev + take) - arithmeticSum(prev);
        k -= take;
      }

      prev = x;
    }

    if (k > 0) {
      sum += arithmeticSum(prev + k) - arithmeticSum(prev);
    }
    return sum;
  }
};
