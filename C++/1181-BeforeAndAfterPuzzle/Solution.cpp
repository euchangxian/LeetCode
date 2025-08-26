#include <algorithm>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

class Solution {
 public:
  std::vector<std::string> beforeAndAfterPuzzles(
      std::vector<std::string>& phrases) {
    // Merge two phrases where the last word of the first phrase is the same as
    // the first word of the second phrase.
    // Return in lexicographically sorted order.
    // Seems like map.
    const auto n = static_cast<int>(phrases.size());
    std::unordered_map<std::string_view, std::vector<int>> lastWords;
    for (int i = 0; i < n; ++i) {
      auto phrase = std::string_view{phrases[i]};
      auto idx = phrase.rfind(' ');
      auto lastWord =
          idx == std::string::npos ? phrase : phrase.substr(idx + 1);
      ;

      lastWords[lastWord].push_back(i);
    }

    std::unordered_set<std::string> resultSet;
    resultSet.reserve(n * n);
    for (int i = 0; i < n; ++i) {
      auto phrase = std::string_view{phrases[i]};
      auto idx = phrase.find(' ');
      auto firstWord =
          idx == std::string::npos ? phrase : phrase.substr(0, idx);

      if (auto it = lastWords.find(firstWord); it != lastWords.end()) {
        for (auto j : it->second) {
          if (i != j) {
            auto merged = phrases[j];
            if (idx != std::string::npos) {
              merged += phrases[i].substr(idx);
            }
            resultSet.emplace(std::move(merged));
          }
        }
      }
    }

    auto result = std::vector<std::string>{resultSet.begin(), resultSet.end()};
    std::sort(result.begin(), result.end());
    return result;
  }
};
