#include <algorithm>
#include <array>
#include <string_view>

class Solution {
 public:
  int maxDifference(std::string_view s) {
    const int n = s.size();
    std::array<int, 26> freq{};
    for (char c : s) {
      ++freq[c - 'a'];
    }

    // a1 is odd, a2 is even
    int a1 = 0;
    int a2 = n;
    for (int cnt : freq) {
      if (cnt % 2) {
        a1 = std::max(a1, cnt);
      } else if (cnt) {
        a2 = std::min(a2, cnt);
      }
    }
    return a1 - a2;
  }
};
