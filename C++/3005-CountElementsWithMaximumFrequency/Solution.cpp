#include <array>
#include <vector>

constexpr int MAX_VAL = 100;

class Solution {
 public:
  int maxFrequencyElements(std::vector<int>& nums) {
    // Given positive integers, return the total frequencies of elements in nums
    // such that all those elements all have the same maximum frequency.
    //
    // This is a trivial 2-pass, and a possible 1-pass.
    // 2-pass:
    // - determine the maximum frequency, while building up a frequency table.
    // - then count all elements with that frequency using the table.
    //
    // 1-pass:
    // - while building up the frequency table, maintain two running variables:
    //   - maxFreq and count.
    // - upon encountering each element, if its updated frequency is equal to
    //   the maxFreq, then increment count.
    //   if less, continue
    //   if greater, update maxFreq, reset count to 1.

    std::array<int, MAX_VAL + 1> freq{};
    int maxFreq = 0;
    int count = 0;
    for (auto x : nums) {
      auto f = ++freq[x];
      if (f == maxFreq) {
        ++count;
      } else if (f > maxFreq) {
        maxFreq = f;
        count = 1;
      }
    }

    return count * maxFreq;
  }
};
