#include <cstddef>
#include <cstdlib>
#include <vector>

class Solution {
 public:
  std::vector<int> getMaximumXor(std::vector<int>& nums, int maximumBit) {
    // Find non-negative integer k < 2^maxBit, i.e., k is maximumBit long.
    // Find k such that prefixXOR(nums[0..i]) ^ k is maximised
    // To maximise XOR, simply place '1' bits where the prefixXOR has '0' bits,
    // and vice versa. Using logical NOT would work, then mask the extra bits
    // in front to keep to k < 2^maxBit, i.e., define mask = 2^maxBit - 1
    unsigned int mask = (1U << maximumBit) - 1;

    // Can possibly do with constance space, i.e., first replace the last
    // element with k, then at the end, reverse the array.
    // Since we want the ith query to take prefixXOR(nums[0..i]), then remove
    // the ith element, i.e., the last element, at the last query, i.e., (n-1)th
    // query, prefixXOR(nums[0]) will be considered.
    // This allows us to start from the last query and work to the first query,
    // maintaining a prefixXOR.
    std::vector<int> answer(nums.size());

    unsigned int prefixXOR = 0;
    for (int i = 0; i < nums.size(); ++i) {
      // cast to unsigned to avoid inverting the sign bit, though i guess this
      // would be handled by the mask. Just for clarity!
      prefixXOR ^= static_cast<unsigned int>(nums[i]);
      answer[nums.size() - 1 - i] = ~prefixXOR & mask;
    }

    return answer;
  }
};
