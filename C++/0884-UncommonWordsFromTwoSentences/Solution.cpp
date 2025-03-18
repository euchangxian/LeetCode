#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  std::vector<std::string> uncommonFromSentences(std::string s1,
                                                 std::string s2) {
    std::unordered_map<std::string, int> frequency;
    splitAndCount(s1, ' ', frequency);
    splitAndCount(s2, ' ', frequency);

    std::vector<std::string> result;
    result.reserve(frequency.size());
    for (const auto& [word, freq] : frequency) {
      if (freq == 1) {
        result.push_back(word);
      }
    }
    return result;
  }

 private:
  void splitAndCount(const std::string& s,
                     const char delimiter,
                     std::unordered_map<std::string, int>& frequency) {
    std::stringstream ss(s);

    std::string token;
    while (std::getline(ss, token, delimiter)) {
      ++frequency[token];
    }
  }
};
