#include <cstddef>
#include <cstdlib>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  long long beautifulSubarrays(std::vector<int>& nums) {
    // In one operation:
    // 1. Choose two different indices i, j
    // 2. Choose a non-negative integer k such that the kth bit of both
    //    nums[i] and nums[j] is '1'.
    // 3. Subtract 2^k from nums[i] and nums[j].
    //
    // A subarray is beautiful if it's possible to make all of its elements
    // equal to 0 after performing the above operations any number of times.
    //
    // hmmm. What does subtracting 2^k do? in terms of binary representation.
    // It clears the '1' bit at that position.
    // count the number of bits at each position. They must be even.
    // TO BE CLEARER: XOR. If the XOR sum is 0, then it is considered beautiful.
    //
    // BUT, we need to count subarrays. Can we use sliding window? What would
    // be our window expansion/shrink condition?
    // Perhaps its not sliding window?
    // We want something like a range query.
    //
    // OHHHHH. Since we want XOR sum to be zero, what if we count the prefixXOR?
    // Or maintain the prefixXOR index.
    // Then whenever we find the XOR-complement, we can figure out how many
    // subarrays contributes towards the count.
    std::unordered_map<int, long long> prefixXORs;
    prefixXORs[0] = 1;  // handle the case where XOR(nums[0..i]) is beautiful

    long long count = 0;
    int sum = 0;
    for (int i = 0; i < nums.size(); ++i) {
      sum ^= nums[i];

      // check if the current sum's XOR-complement exists.
      // i.e., check for same sum
      count += prefixXORs[sum]++;
    }

    return count;
  }
};
