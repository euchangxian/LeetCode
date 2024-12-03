#include <cstddef>
#include <cstdlib>
#include <string>
#include <string_view>
#include <vector>

class Solution {
 public:
  std::string addSpaces(std::string_view sv, std::vector<int>& spaces) {
    // Two pointer.
    std::string s;
    s.reserve(sv.size() + spaces.size());

    auto begin = sv.begin();
    for (const int space : spaces) {
      std::string_view sub = std::string_view{begin, sv.begin() + space};

      s.append(sub);
      s.push_back(' ');

      begin = sv.begin() + space;
    }

    if (begin != sv.end()) {
      s.append(begin, sv.end());
    }

    return s;
  }
};
