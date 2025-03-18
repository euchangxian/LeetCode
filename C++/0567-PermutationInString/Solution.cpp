#include <array>
#include <cstddef>
#include <string>

class Solution {
 public:
  bool checkInclusion(std::string s1, std::string s2) {
    if (s1.length() > s2.length()) {
      return false;
    }

    // Fixed-size sliding window problem
    std::array<int, 26> freq1{};
    std::array<int, 26> freq2{};

    for (std::size_t i = 0; i < s1.length(); ++i) {
      ++freq1[s1[i] - 'a'];
      ++freq2[s2[i] - 'a'];
    }

    if (freq1 == freq2) {
      return true;
    }

    for (std::size_t r = s1.length(); r < s2.length(); ++r) {
      // Update the left and right side of the fixed-size sliding window
      --freq2[s2[r - s1.length()] - 'a'];
      ++freq2[s2[r] - 'a'];

      if (freq1 == freq2) {
        return true;
      }
    }
    return false;
  }
};
