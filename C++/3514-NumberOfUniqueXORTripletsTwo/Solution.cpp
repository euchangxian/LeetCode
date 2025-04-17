#include <bitset>
#include <vector>

constexpr int MAX_N = 1500;
constexpr int MAX_XOR = 2048;
class Solution {
 public:
  int uniqueXorTriplets(std::vector<int>& nums) {
    // An XOR triplet is defined as nums[i]^nums[j]^nums[k], i<=j<=k
    // Essentially unique XOR sums from a combination of 3 indices.
    //
    // Notice that the MAX_XOR for nums[i] <= 1500 is 2048.
    // That means we can brute force.
    std::bitset<MAX_XOR + 1> seen{};

    for (int num1 : nums) {
      for (int num2 : nums) {
        seen.set(num1 ^ num2);
      }
    }

    std::bitset<MAX_XOR + 1> unique{};
    for (int num : nums) {
      for (int i = 0; i <= MAX_XOR; ++i) {
        if (seen[i]) {
          unique.set(i ^ num);
        }
      }
    }
    return unique.count();
  }
};
