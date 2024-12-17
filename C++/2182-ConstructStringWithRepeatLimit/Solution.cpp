#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <queue>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

class Solution {
 public:
  std::string repeatLimitedString(std::string_view s, int repeatLimit) {
    // Seems like greedy works?
    // Construct frequency array. Pick each character k times.
    // Hm. Lexicographically largest seems to be a problem though.
    // E.g., consider {a: 3, b: 6}, repeatLimit = 3
    // Greedy: bbbaaabbb
    // Optimal: bbbabbbaa
    // What about a maxHeap?
    std::array<int, 26> counts{};
    for (char c : s) {
      ++counts[c - 'a'];
    }
    std::priority_queue<std::pair<char, int>, std::vector<std::pair<char, int>>,
                        std::less<>>
        maxHeap;
    for (int i = 0; i < 26; ++i) {
      if (counts[i] > 0) {
        maxHeap.emplace(i + 'a', counts[i]);
      }
    }

    std::string ns;
    ns.reserve(s.size());

    while (!maxHeap.empty()) {
      auto [c, freq] = maxHeap.top();
      maxHeap.pop();

      // handle the case where the previous element is used once already.
      int repeats = !ns.empty() && ns.back() == c
                        ? std::min(repeatLimit - 1, freq)
                        : std::min(repeatLimit, freq);
      ns.append(repeats, c);

      if (maxHeap.empty()) {
        break;
      }

      // append 1 of the next char
      auto [next, nextFreq] = maxHeap.top();
      maxHeap.pop();
      ns.append(1, next);

      if (freq - repeats > 0) {
        maxHeap.emplace(c, freq - repeats);
      }

      if (nextFreq - 1 > 0) {
        maxHeap.emplace(next, nextFreq - 1);
      }
    }
    return ns;
  }
};
