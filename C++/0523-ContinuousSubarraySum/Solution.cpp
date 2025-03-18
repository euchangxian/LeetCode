#include <unordered_map>
#include <vector>

class Solution {
 public:
  bool checkSubarraySum(std::vector<int>& nums, int k) {
    if (nums.size() < 2) {
      return false;
    }

    int n = nums.size();

    // Modulo property:
    // 1. (a + b) % k = ((a % k) + (b % k)) % k
    // 2. if a = b % k, then (a + c) % k = (b + c) % k for any c.
    //
    // sum(nums[i:j]) = prefixSum(nums[:j]) - prefixSum(nums[:i]))
    // goal: sum(nums[i:j]) % k == 0
    //
    // (prefixSum(nums[:j]) % k - prefixSum(nums[:i]) % k) % k == 0
    // prefixSum(nums[:j]) % k == prefixSum(nums[:i]) % k
    int prefixSum = 0;
    std::unordered_map<int, int> prefixMods = {{0, -1}};

    for (int i = 0; i < n; ++i) {
      prefixSum += nums[i];
      int prefixMod = prefixSum % k;

      if (prefixMods.count(prefixMod) && i - prefixMods[prefixMod] >= 2) {
        return true;
      }

      if (!prefixMods.count(prefixMod)) {
        prefixMods[prefixMod] = i;
      }
    }
    return false;
  }
};
