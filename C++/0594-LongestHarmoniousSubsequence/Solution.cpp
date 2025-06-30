#include <algorithm>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  int findLHS(std::vector<int>& nums) {
    // A harmonious array is an array where the difference between its
    // max and min value is exactly 1.
    // Find the length of the longest harmonious subsequence.
    //
    // Only two numbers can be in the subsequence. And these two numbers x, y
    // | x - y | == 1.
    // Given n <= 2*10^4, we can do an O(N^2) solution where we enumerate
    // all pairs of values x, y.
    auto n = static_cast<int>(nums.size());
    std::unordered_map<int, int> freq;
    freq.reserve(n);
    for (int x : nums) {
      ++freq[x];
    }

    int result = 0;
    for (auto [x, count] : freq) {
      if (auto it = freq.find(x - 1); it != freq.end()) {
        result = std::max(result, count + it->second);
      }
    }
    return result;
  }
};
