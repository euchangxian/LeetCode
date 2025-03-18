#include <array>
#include <cstddef>
#include <string>
#include <vector>

class Solution {
 public:
  bool makeEqual(std::vector<std::string>& words) {
    // Since there is no need to optimize the operations, rather than focusing
    // on the operations, focus on the property necessary to make all strings
    // equal. Simply count the number of characters. They must appear
    // words.size() * k, k >= 0 times.
    const std::size_t n = words.size();

    std::array<int, 26> occurence{};
    for (const std::string& word : words) {
      for (const char c : word) {
        ++occurence[c - 'a'];
      }
    }

    for (const int count : occurence) {
      if (count % n != 0) {
        return false;
      }
    }
    return true;
  }
};
