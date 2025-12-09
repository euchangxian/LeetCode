#include <array>
#include <vector>

constexpr int MOD = 1E9 + 7;
constexpr int MAX_VAL = 1E5;
class Solution {
 public:
  int specialTriplets(std::vector<int>& nums) {
    // A special triplet (i,j,k) is such that:
    // - 0<=i<j<k<n
    // - nums[i] == nums[j]*2
    // - nums[j] == nums[k]*2
    // Return the number of special triplets modulo 1E9+7.
    //
    // Transitivity.
    // Feels like counting values, where we can have groupings.
    // Elements in the same group can form triplets with consecutive elements.
    // i.e., group size = 4 => (1, 2, 3), (2, 3, 4) => k-3+1 groups.
    //
    // Felt like UF.
    // Nope.
    //
    // We need to count based off ordered indices.
    const auto n = static_cast<int>(nums.size());

    long long result = 0;

    // Number of times nums[i] == x has occured
    std::array<int, MAX_VAL + 1> len1{};

    // Number of 2-length chains (i, j) ending at nums[j] == x
    std::array<int, MAX_VAL + 1> len2{};

    for (auto x : nums) {
      if (x % 2 == 0) {
        result = (result + len2[x / 2]) % MOD;
      }

      // Can form len1[x*2] (i, j) chains with nums[i] == x, nums[j] == x*2
      if (x * 2 <= MAX_VAL) {
        len2[x] = (len2[x] + len1[x * 2]) % MOD;
      }
      ++len1[x];
    }
    return result;
  }
};
