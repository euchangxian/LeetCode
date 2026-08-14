#include <algorithm>
#include <array>
#include <cstdint>
#include <string_view>

class Solution {
 public:
  int maximumLengthSubstring(std::string_view s) {
    // return maximum length substring that contains at most two occurences of
    // each character.
    const auto n = static_cast<int>(s.size());
    std::array<std::uint8_t, 256> freq{};

    auto result = 0;
    auto curr = 0;
    for (int l = 0, r = 0; r < n; ++r) {
      ++freq[s[r]];
      ++curr;
      while (freq[s[r]] > 2) {
        --freq[s[l++]];
        --curr;
      }
      result = std::max(result, curr);
    }
    return result;
  }
};
