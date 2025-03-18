#include <algorithm>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  int minSubarray(std::vector<int>& nums, int p) {
    // The sum of the subarrays to be removed is a multiple of the remainder,
    // sum = k * r, where k >= 0
    // In other words, find subarrays that are divisible by R. i.e. reducible
    // to a similar problem we have seen before!
    // 974.Subarray Sums Divisble by K requires counting the number of subarray
    // with sums divisible by K. sum{nums[i:j]} % k = 0
    // Here, we only want the smallest subarray.
    // Similarly, we can use the property of modulo;
    // ((prefixSum{nums[:j]} % k) - (prefixSum{nums[:i]} % k)) % k = 0
    // prefixSum{nums[:j]} % k = prefix{nums[:i]} % k
    int remainder = 0;
    for (const int num : nums) {
      remainder = (remainder + num) % p;
    }
    if (remainder == 0) {
      return 0;
    }

    // Using a vector will result in OOM, since we are storing prefix mod p
    std::unordered_map<int, int> mods;
    mods[0] = -1;
    int currSum = 0;
    int minLen = nums.size();

    for (int i = 0; i < nums.size(); ++i) {
      // Calculate the prefix sum mod p
      currSum = (currSum + nums[i]) % p;

      // From this prefix sum, get the value that needs to be removed
      int target = (currSum - remainder + p) % p;

      if (mods.count(target)) {
        minLen = std::min(minLen, i - mods[target]);
      }
      mods[currSum] = i;
    }

    return minLen == nums.size() ? -1 : minLen;
  }
};
