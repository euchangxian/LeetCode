#include <climits>
#include <string>
#include <vector>

class Solution {
 public:
  std::vector<std::string> commonChars(std::vector<std::string>& words) {
    std::vector<std::vector<int>> present =
        std::vector<std::vector<int>>(26, std::vector<int>(words.size(), 0));
    for (int i = 0; i < words.size(); ++i) {
      for (char c : words[i]) {
        ++present[c - 'a'][i];
      }
    }

    std::vector<std::string> result;
    for (int i = 0; i < present.size(); ++i) {
      int occurences = INT_MAX;
      for (int freq : present[i]) {
        occurences = std::min(occurences, freq);
      }
      // Not really convention to use _
      for (int _ = 0; _ < occurences; ++_) {
        // C++ char to string conversion is more cumbersome than expected...
        result.push_back(std::string(1, i + 'a'));
      }
    }
    return result;
  }
};
