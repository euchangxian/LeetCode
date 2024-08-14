#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
class Solution {
public:
  int subarraysDivByK(vector<int> &nums, int k) {
    // Very similar to 523: Continuous Subarray Sum
    // The goal is to find the number of subarrays that have sum divisible by k
    // That means: sum(nums[i:j]) / k == 0
    //
    // By definition of modulo:
    // if a mod b == r, then a = mb + r, m is an arbitrary integer
    //
    // Therefore, if the remainder is zero, for some arbitrary m,
    // sum(nums[i:j]) % k == 0
    //
    // Representing sum(nums[i:j]) with prefixSums:
    // sum(nums[i:j]) == prefixSum(nums[:j]) - prefixSum(nums[:i])
    // ((prefix(nums[:j]) % k) - (prefix(nums[:i]) % k)) % k == 0
    //
    // Re-arranging:
    // prefix(nums[:j]) % k == prefix(nums[:i]) % k
    //
    // Therefore, a map containing the modulo of the prefix sum can be used.
    int n = nums.size();
    int prefixSum = 0;

    vector<int> prefixModFreq(k);

    // Account for the case where the entire array is divisible by k
    prefixModFreq[0] = 1;

    int result = 0;
    for (int const &num : nums) {
      prefixSum += num;

      // Add k to bring the result into the positive range
      // Then, to compensate for overadjustments, mod by k again
      // This is because in C++, modulo with negative can produce negative
      // remainders, e.g. -7 % 5 == -2, where the intended result for this
      // is -7 % 5 == 3
      int mod = ((prefixSum % k) + k) % k;

      result += prefixModFreq[mod];
      ++prefixModFreq[mod];
    }
    return result;
  }
};
