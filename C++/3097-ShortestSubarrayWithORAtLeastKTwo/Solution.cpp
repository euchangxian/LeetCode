#include <algorithm>
#include <array>
#include <climits>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <vector>

class Solution {
 private:
  void updateTable(std::array<int, 32>& table,
                   int num,
                   std::function<int(int, int)> op) {
    int i = 0;
    while (num > 0) {
      table[i] = op(table[i], (num & 1));
      num >>= 1;
      ++i;
    }
  }

  int fromTable(std::array<int, 32>& table) {
    int sum = 0;
    for (int i = 0; i < table.size(); ++i) {
      if (table[i]) {
        sum |= (1 << i);
      }
    }
    return sum;
  }

 public:
  int minimumSubarrayLength(std::vector<int>& nums, int k) {
    // Find the length of the shortest special subarray of nums.
    // A subarray is special if the bitwise OR of all of its elements is at
    // least k.
    // Sliding window? Since bitwise OR will always at least equal or increase
    // the sum. How to clear the OR-ed number though? Might accidently clear
    // other bits. Could have a bit-frequency table.
    // Can we do better?
    // What about prefixOR? We want at least k, and not equal to k. May be
    // difficult to do that with prefixORs.
    //
    // What about precomputing the prefixORs for sliding window? Allows us to
    // forgo the bit-frequency table.

    // Technically, nums[i] <= 10^9 require 30 bits.
    std::array<int, 32> freq{};

    int minLen = INT_MAX;
    int l = 0;
    for (int r = 0; r < nums.size(); ++r) {
      updateTable(freq, nums[r], std::plus<>{});

      // While the window contains at least 1 element, and the sum is at least
      // k:
      while (l <= r && fromTable(freq) >= k) {
        // Found a valid window, update minLen
        minLen = std::min(minLen, r - l + 1);

        // inverse the bit operation for the left-most of the window.
        updateTable(freq, nums[l], std::minus<>{});
        ++l;
      }
    }
    return minLen == INT_MAX ? -1 : minLen;
  }
};
