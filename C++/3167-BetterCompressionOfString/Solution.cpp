#include <array>
#include <cstddef>
#include <cstdlib>
#include <string>
#include <string_view>

class Solution {
 public:
  std::string betterCompression(std::string_view compressed) {
    std::array<int, 26> frequency{};
    char c = compressed[0];
    int freq = 0;
    for (int i = 1; i < compressed.size(); ++i) {
      if (std::isdigit(compressed[i])) {
        freq = freq * 10 + (compressed[i] - '0');
      } else {
        frequency[c - 'a'] += freq;
        freq = 0;
        c = compressed[i];
      }
    }
    frequency[c - 'a'] += freq;

    std::string result;
    result.reserve(10000);
    for (int i = 0; i < 26; ++i) {
      if (frequency[i]) {
        result += (i + 'a');
        result += std::to_string(frequency[i]);
      }
    }
    return result;
  }
};
