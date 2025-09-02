#include <algorithm>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

class Solution {
 public:
  std::vector<std::string> topKFrequent(std::vector<std::string>& words,
                                        int k) {
    // Return the k most frequent strings, sorted by frequency from
    // highest to lowest, tie-broken by lexicographical order.
    //
    // O(nlogn) is trivial - sort the frequency array
    // O(N + K) quickselect
    const auto n = static_cast<int>(words.size());

    std::unordered_map<std::string_view, int> freqMap;
    freqMap.reserve(n);
    for (std::string_view word : words) {
      ++freqMap[word];
    }

    std::vector<std::pair<int, std::string_view>> frequency;
    for (const auto [word, freq] : freqMap) {
      frequency.emplace_back(-freq, word);
    }

    // NOTE: O(nlogk)
    // The STL implementation is typically heap sort.
    std::partial_sort(frequency.begin(), frequency.begin() + k, frequency.end(),
                      [](const auto& p1, const auto& p2) {
                        if (p1.first == p2.first) {
                          return p1.second < p2.second;
                        }
                        return p1.first < p2.first;
                      });

    std::vector<std::string> result;
    for (int i = 0; i < k; ++i) {
      result.emplace_back(frequency[i].second.data());
    }
    return result;
  }
};
