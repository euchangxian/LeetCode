#include <string>
#include <string_view>
#include <vector>

class Solution {
 public:
  std::vector<int> findWordsContaining(std::vector<std::string>& words,
                                       char x) {
    const int n = words.size();
    std::vector<int> result;
    result.reserve(n);
    for (int i = 0; i < n; ++i) {
      std::string_view s{words[i]};

      if (s.contains(x)) {
        result.push_back(i);
      }
    }
    return result;
  }
};
