#include <bitset>
#include <string_view>

class Solution {
 public:
  int shortestWay(std::string_view source, std::string_view target) {
    // Return the minimum number of subseqeuences of source such that
    // their concantenation equals target, or impossible.
    // Simulate LCS repeatedly at different starting points of target.
    std::bitset<256> inSrc{};
    int uniq = 0;
    for (char c : source) {
      inSrc[c] = 1;
    }

    for (char c : target) {
      if (!inSrc[c]) {
        return -1;
      }
    }

    int result = 0;
    int i = 0;
    int j = 0;
    while (j < target.size()) {
      if (i == 0) {
        ++result;
      }

      if (source[i] == target[j]) {
        ++j;
      }
      i = (i + 1) % source.size();
    }
    return result;
  }
};
