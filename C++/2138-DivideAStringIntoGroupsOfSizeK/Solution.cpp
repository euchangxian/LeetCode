#include <string>
#include <string_view>
#include <utility>
#include <vector>

class Solution {
 public:
  std::vector<std::string> divideString(std::string_view s, int k, char fill) {
    // Partition string s into groups of size k using the procedure:
    // - First group consists of the first k characters, second group contains
    //   the next k, and so on.
    // - Character fill is used to fill the last partition.
    auto n = static_cast<int>(s.size());
    auto groups = (n + k - 1) / k;
    std::vector<std::string> result;
    result.reserve(groups);

    for (int i = 0; i < groups; ++i) {
      std::string part;
      part.reserve(k);
      part += s.substr(i * k, k);
      if (i == groups - 1 && k - part.size() > 0) {
        part += std::string(k - part.size(), fill);
      }
      result.emplace_back(std::move(part));
    }
    return result;
  }
};
