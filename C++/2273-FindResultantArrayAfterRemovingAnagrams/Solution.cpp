#include <algorithm>
#include <array>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

class Solution {
 public:
  std::vector<std::string> removeAnagrams(std::vector<std::string>& words) {
    // words[i] consists of lower-cased english letters.
    // Pick index i such that words[i-1] and words[i] are anagrams, delete
    // words[i].
    // Repeat until no longer possible.
    //
    // Anagrams are transitive => remove until left with 1.
    constexpr auto areAnagrams = [](std::string_view a, std::string_view b) {
      if (a.size() != b.size()) {
        return false;
      }

      std::array<int, 26> freq{};
      for (char c : a) {
        ++freq[c - 'a'];
      }

      for (char c : b) {
        --freq[c - 'a'];
      }

      return std::ranges::all_of(freq, [](int x) { return x == 0; });
    };

    std::vector<std::string> result;
    result.emplace_back(std::move(words[0]));
    for (int i = 1; i < words.size(); ++i) {
      if (areAnagrams(words[i], result.back())) {
        continue;
      }
      result.emplace_back(std::move(words[i]));
    }
    return result;
  }
};
